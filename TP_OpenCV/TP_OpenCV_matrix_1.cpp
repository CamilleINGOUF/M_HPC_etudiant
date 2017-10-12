#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main()
{

  cv::Mat M = (cv::Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
  std::cout << "---- M ----\n" << M << std::endl;

  cv::Mat I = cv::Mat::eye(3, 3, CV_64F);
  std::cout << "---- I ----\n" << I << std::endl;

  cv::Mat u = (cv::Mat_<float>(3,1) << 1, 2, 3);
  std::cout << "---- u ----\n" << u << std::endl;

  cv::Mat v = cv::Mat_<float>::ones(3,1);
  std::cout << "--- v ----\n" << v << std::endl;

  cv::Mat Mv = M * v;
  std::cout << "--- Mv ----\n" << Mv << std::endl;

  std::cout << "---- u.v ----\n" << u.dot(v) << std::endl;

  std::cout << "---- M01 ----\n" << M.at<float>(0,1) << std::endl;

  std::cout << "---- FMT_CSV ----\n" << cv::format(M, cv::Formatter::FMT_CSV)
	    << std::endl;

  cv::Mat P = cv::ml::TrainData::loadFromCSV("TP_OpenCV_matrix.csv", 0, -2, 0)->getSamples();
  std::cout << "---- loadCSV ----\n" << P << std::endl;

  return 0;
}

