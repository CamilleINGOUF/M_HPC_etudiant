// image transposition
// http://docs.opencv.org/modules/core/doc/basic_structures.html

#define __CL_ENABLE_EXCEPTIONS

#include "opencHelp.hpp"

#include <opencv2/opencv.hpp>

int main(int argc, char ** argv)
{

	// print OpenCL platforms and devices
	opencHelp::printPlatformsAndDevices();

	// check command line arguments
	if (argc < 4 or argc > 5)
	{
		std::cout << "Usage: " << argv[0] << " <iPlatform> <iDevice> <inputImage> [outputFile]" << std::endl;
		exit(-1);
	}
	//unsigned iPlatform = std::stoi(argv[1]);
	//unsigned iDevice = std::stoi(argv[2]);
	const char * inputFilename = argv[3];
	const char * outputFilename = argc == 5 ? argv[4] : nullptr;

	// read input image
	cv::Mat inputImageRgb = cv::imread(inputFilename, CV_LOAD_IMAGE_COLOR); 
	cv::Mat inputImage;
	cv::cvtColor(inputImageRgb, inputImage, CV_BGR2BGRA );
	if (inputImage.type() != CV_8UC4)
	{
		std::cout << "Error: unsupported image format" << std::endl;
		exit(-1);
	}
	int inWidth = inputImage.cols;
	int inHeight = inputImage.rows;
	int outWidth = inHeight;
	int outHeight = inWidth;
	//int dataFullSize = inWidth * inHeight * 4;
	cv::Mat outputImage (outHeight, outWidth, CV_8UC4);

	opencHelp::Chrono chrono;

	// compute
	outputImage = inputImage.t(); 

	double time = chrono.elapsed();
	std::cout << "Time: " << time << " s" << std::endl;

	// write output image
	if (outputFilename)
	{
		cv::imwrite(outputFilename, outputImage);
	}

	return 0;

}

