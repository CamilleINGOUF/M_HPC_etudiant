#include <opencv2/opencv.hpp>
#include "utils.hpp"

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

    const double COEF = 0.5;

    // operator*=
    timePoint_t tpMul0 = now();
    cv::Mat imgMul = imgInput.clone();
    imgMul *= COEF;
    timePoint_t tpMul1 = now();

    // foreach loop
    // TODO

    // 2D loop
    // TODO

    // print computation times
    std::cout << "imgMul: " << duration(tpMul0, tpMul1) << " s\n";
    // TODO

    // write image files
    imwrite(basename + "_imgMul" + extension, imgMul);
    // TODO

    // display images
    cv::imshow("imgInput", imgInput);
    cv::imshow("imgMul", imgMul);
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


