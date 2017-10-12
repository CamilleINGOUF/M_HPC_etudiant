#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main(int argc, char ** argv) 
{ 
    // check command line arguments
    if (argc != 4) 
    {
        std::cerr << "usage: " << argv[0] << " <filename> <blur size> <blur sigma>\n";
        exit(-1);
    }
    // filename 
    const char * filename = argv[1];
    std::string basename, extension;
    getBasenameAndExtension(filename, basename, extension);
    // blur size
    int blurSize = atoi(argv[2]);
    if (blurSize % 2 != 1) blurSize++;  // ensure blur size is odd
    // blur sigma
    double blurSigma = atof(argv[3]);

    const int NB_REPEAT = 3;

    // blur image using cv::Mat
    for (int n=0; n<NB_REPEAT; ++n)
    {
        std::cout << "cv::Mat" << std::endl;
        timePoint_t tp0 = now();

        // TODO read image

        // TODO compute gaussian blur

        // TODO write image

        timePoint_t tp3 = now();
        std::cout << "  total: " << duration(tp0, tp3) << " s\n";
    }

    return 0;
}

