#include <opencv2/opencv.hpp>
#include "utils.hpp"

const double COEF = 0.5;

int main(int argc, char ** argv) 
{ 
    if (argc != 2) 
    {
        std::cerr << "usage: " << argv[0] << " <filename> \n";
        exit(-1);
    }
    const char * filename = argv[1];
    std::string basename, extension;
    getBasenameAndExtension(filename, basename, extension);

    // load input image
    cv::Mat imgInput = cv::imread(filename);
    if (imgInput.channels()!=3 or imgInput.depth()!=CV_8U)
    {
        std::cerr << "error: only 3-channel 8-bits images are supported\n";
        exit(-1);
    }

    // operator*=
    timePoint_t tpMul0 = now();
    cv::Mat imgMul = imgInput.clone();
    imgMul *= COEF;
    timePoint_t tpMul1 = now();

    // foreach loop
    timePoint_t tpEach0 = now();
    cv::Mat imgEach = imgInput.clone();
    auto imgCoef = [](cv::Vec3b &p, const int * position) -> void{p*=COEF;};
    imgEach.forEach<cv::Vec3b>(imgCoef);
    timePoint_t tpEach1 = now();

    // 2D loop
    timePoint_t tp2D0 = now();
    cv::Mat img2D = imgInput.clone();
    for(int i = 0; i < img2D.rows; i++)
      {
	for(int j = 0; j < img2D.cols; j++)
	  {
	    img2D.at<cv::Vec3b>(i,j) *= COEF;
	  }
      }
    timePoint_t tp2D1 = now();

    // print computation times
    std::cout << "imgMul: " << duration(tpMul0, tpMul1) << " s\n";
    std::cout << "Img2D: " << duration(tp2D0, tp2D1) << " s\n";
    std::cout << "ImgEach : " << duration(tpEach0, tpEach1) << " s\n";
    // TODO

    // write image files
    imwrite(basename + "_imgMul" + extension, imgMul);
    imwrite(basename + "_img2D" + extension, img2D);
    imwrite(basename + "_imgEach" + extension, imgEach);
    // TODO

    // display images
    cv::imshow("imgInput", imgInput);
    cv::imshow("imgMul", imgMul);
    cv::imshow("img2D", img2D);
    cv::imshow("imgEach", imgEach);
    // TODO

    // wait for "esc"
    while (true)
    {
        int k = cv::waitKey(100) % 0x100;
        if (k == 27)
            break;
    }

    return 0;
}


