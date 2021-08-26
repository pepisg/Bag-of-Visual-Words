#include <place_recognition.hpp>

PlaceRecognizer::PlaceRecognizer(const std::string &dictionary_path,
                                 const std::string &bin_dataset_path) {

  // set de dictionary with the precomputed sifts
  dictionary_.set_vocabulary(dictionary_path);

  // Compute the histograms of all images
  std::vector<cv::Mat> sifts_dataset =
      ipb::serialization::sifts::LoadDataset(bin_dataset_path);
  histograms_.reserve(sifts_dataset.size());
  bin_frequency_.resize(dictionary_.size());
  for (auto &image : sifts_dataset) {
    histograms_.emplace_back(ipb::Histogram(image, dictionary_.vocabulary()));
    for (int i = 0; i < dictionary_.size(); i++) {
      // get the amount of images in which each word appears to TF-IDF
      if (histograms_.back()[i] > 0) {
        bin_frequency_[i]++;
      }
    }
  }
}
