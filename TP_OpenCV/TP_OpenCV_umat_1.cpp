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
    
    cv::Mat imgBlur;
    // blur image using cv::Mat
    for (int n=0; n<NB_REPEAT; ++n)
    {
        std::cout << "cv::Mat" << std::endl;
        timePoint_t tp0 = now();
	
	// load input image
	cv::Mat imgInput = cv::imread(filename);
	if (imgInput.channels()!=3 or imgInput.depth()!=CV_8U)
	  {
	    std::cerr << "error: only 3-channel 8-bits images are supported\n";
	    exit(-1);
	  }

	timePoint_t tp1 = now();
        // TODO compute gaussian blur
	
	cv::Size bSize(blurSize,blurSigma);
	cv::blur(imgInput, imgBlur, bSize);

	timePoint_t tp2 = now();
	
        // TODO write image
	imwrite(basename + "_imgBlur" + extension, imgBlur);

        timePoint_t tp3 = now();

	std::cout << "  imread: " << duration(tp0, tp1) << " s\n";
	std::cout << "  GaussianBlur: " << duration(tp1, tp2) << " s\n";
	std::cout << "  imwrite: " << duration(tp2, tp3) << " s\n";
        std::cout << "  total: " << duration(tp0, tp3) << " s\n";
    }

    for (int n=0; n<NB_REPEAT; ++n)
    {
        std::cout << "cv::UMat" << std::endl;
        timePoint_t tp0 = now();
	
	// load input image
	cv::Mat imgInput = cv::imread(filename);
	if (imgInput.channels()!=3 or imgInput.depth()!=CV_8U)
	  {
	    std::cerr << "error: only 3-channel 8-bits images are supported\n";
	    exit(-1);
	  }
	cv::UMat imgUMat;
	imgInput.copyTo(imgUMat);

	timePoint_t tp1 = now();
        // TODO compute gaussian blur
	
	cv::Size bSize(blurSize,blurSigma);
	cv::blur(imgUMat, imgBlur, bSize);

	timePoint_t tp2 = now();
	
        // TODO write image
	imwrite(basename + "_imgBlur" + extension, imgBlur);

        timePoint_t tp3 = now();

	std::cout << "  imread: " << duration(tp0, tp1) << " s\n";
	std::cout << "  GaussianBlur: " << duration(tp1, tp2) << " s\n";
	std::cout << "  imwrite: " << duration(tp2, tp3) << " s\n";
        std::cout << "  total: " << duration(tp0, tp3) << " s\n";
    }
    return 0;
}

