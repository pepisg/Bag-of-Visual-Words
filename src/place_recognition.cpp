#include <place_recognition.hpp>

PlaceRecognizer::PlaceRecognizer(const std::string &dictionary_path,
                                 const std::string &bin_dataset_path,
                                 const std::string &raw_dataset_path) {

  // set de dictionary with the precomputed sifts
  dictionary_.set_vocabulary(dictionary_path);

  // get the path of all files inside the raw image dataset
  for (const auto &entry :
       std::filesystem::directory_iterator(raw_dataset_path)) {
    if (entry.path().extension() == ".png") {
      raw_images_.emplace_back(entry.path());
    }
  }

  // Compute the histograms of all images
  std::vector<std::pair<cv::Mat, std::filesystem::path>> sifts_dataset =
      ipb::serialization::sifts::LoadDataset(bin_dataset_path);
  histograms_.reserve(sifts_dataset.size());
  bin_frequency_.resize(dictionary_.size());
  int current_image = 0;
  for (auto &image : sifts_dataset) {
    histograms_.emplace_back(
        ipb::Histogram(image.first, dictionary_.vocabulary(), image.second));
    current_image++;
    for (int i = 0; i < dictionary_.size(); i++) {
      // get the amount of images in which each word appears to TF-IDF
      if (histograms_.back()[i] > 0) {
        bin_frequency_[i]++;
      }
    }
  }

  // Adjust histogram values with TF-IDF term
  for (int i = 0; i < histograms_.size(); i++) {
    int n_words =
        std::accumulate(histograms_[i].begin(), histograms_[i].end(), 0);
    for (int j = 0; j < histograms_[i].size(); j++) {
      if (bin_frequency_[j] > 0) {
        histograms_[i][j] =
            bin_frequency_.size() *
            (((float)histograms_[i][j] / (float)n_words) *
             std::log2(((float)histograms_.size() / (float)bin_frequency_[j])));
      }
    }
  }
}

float PlaceRecognizer::cosine_distance(ipb::Histogram h1, ipb::Histogram h2) {
  return 1.0f - std::inner_product(h1.begin(), h1.end(), h2.begin(), 0) /
                    (std::sqrt(std::inner_product(h1.begin(), h1.end(),
                                                  h1.begin(), 0)) *
                     std::sqrt(std::inner_product(h2.begin(), h2.end(),
                                                  h2.begin(), 0)));
}

void PlaceRecognizer::find_places(const std::string &image_path) {
  cv::Mat image = cv::imread(image_path);
  descriptors_ = cv::Mat();
  keypoints_.clear();
  detector_->clear();
  extractor_->clear();
  detector_->detect(image, keypoints_);
  extractor_->compute(image, keypoints_, descriptors_);
  ipb::Histogram query_histogram =
      ipb::Histogram(descriptors_, dictionary_.vocabulary());

  // Adjust histogram values with TF-IDF term
  int n_words =
      std::accumulate(query_histogram.begin(), query_histogram.end(), 0);
  for (int j = 0; j < query_histogram.size(); j++) {
    if (bin_frequency_[j] > 0) {
      query_histogram[j] = bin_frequency_.size() *
                           (((float)query_histogram[j] / (float)n_words) *
                            std::log2(((float)query_histogram.size() /
                                       (float)bin_frequency_[j])));
    }
  }

  std::vector<std::pair<float, const ipb::Histogram *>> closest_matches;
  int i = 0;
  for (const auto &histogram : histograms_) {
    closest_matches.emplace_back(std::make_pair(
        cosine_distance(histogram, query_histogram), &histogram));
    i++;
  }
  std::sort(closest_matches.begin(), closest_matches.end());
  std::vector<image_browser::ImageRow> browser_images;
  for (int j = 0; j < 3; j++) {
    image_browser::ImageRow image_row;
    for (int k = 0; k < 3; k++) {
      image_row[k] = image_browser::ScoredImage(std::make_tuple(
          "../dataset/raw_imgs/" +
              closest_matches[3 * j + k].second->filename().stem().string() +
              ".png",
          closest_matches[3 * j + k].first));
    }
    browser_images.emplace_back(image_row);
  }
  image_browser::CreateImageBrowser(
      "Similarities", "style.css", browser_images,
      std::filesystem::path(image_path).stem().string() + ".html");
}

int main() {
  PlaceRecognizer place_recognizer =
      PlaceRecognizer("../dataset/dictionary.bin", "../dataset/sifts_bin",
                      "../dataset/raw_imgs");

  for (const auto image_path :
       std::filesystem::directory_iterator("../dataset/raw_imgs")) {
    if (image_path.path().extension().string() == ".png") {
      place_recognizer.find_places(image_path.path().string());
    }
  }
}
