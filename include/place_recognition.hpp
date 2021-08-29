#ifndef PLACE_RECOGNITION_HPP_
#define PLACE_RECOGNITION_HPP_

#include <bow_histogram/bow.hpp>
#include <imagebrowser/image_browser.hpp>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <serialization/convert_dataset.hpp>

class PlaceRecognizer {
public:
  PlaceRecognizer();
  explicit PlaceRecognizer(const std::string &dictionary_path,
                           const std::string &bin_dataset_path,
                           const std::string &raw_dataset_path);
  ~PlaceRecognizer(){};

  void find_places(const std::string &image_path);
  void find_places(cv::Mat image);

private:
  float cosine_distance(ipb::Histogram h1, ipb::Histogram h2);

  std::vector<std::filesystem::path> raw_images_;
  ipb::BowDictionary &dictionary_ = ipb::BowDictionary::GetInstance();
  cv::Ptr<cv::xfeatures2d::SiftFeatureDetector> detector_ =
      cv::xfeatures2d::SiftFeatureDetector::create();
  cv::Ptr<cv::xfeatures2d::SiftDescriptorExtractor> extractor_ =
      cv::xfeatures2d::SiftDescriptorExtractor::create();
  std::vector<ipb::Histogram> histograms_;
  std::vector<int> bin_frequency_;
  cv::Mat descriptors_;
  std::vector<cv::KeyPoint> keypoints_;
};

#endif