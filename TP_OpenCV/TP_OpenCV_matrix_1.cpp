#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main()
{

    cv::Mat M = (cv::Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
    std::cout << "---- M ----\n" << M << std::endl;

    // TODO

	return 0;
}

