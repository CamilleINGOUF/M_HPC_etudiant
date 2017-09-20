
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
	int width = inputImage.cols;
	int height = inputImage.rows;
	//int dataFullSize = width * height * 4;
	cv::Mat outputImage(height, width, CV_8UC4);

	opencHelp::Chrono chrono;

	// compute
	cv::Mat blur1, blur2;
	cv::blur(inputImage, blur1, cv::Size(5, 5));
	cv::blur(inputImage, blur2, cv::Size(9, 9));
	cv::multiply(inputImage - cv::Scalar(30,30,0), cv::Scalar(255) - (blur2 - blur1), outputImage, 1/200.0);

	double time = chrono.elapsed();
	std::cout << "Time: " << time << " s" << std::endl;

	// write output image
	if (outputFilename)
	{
		cv::imwrite(outputFilename, outputImage);
	}

	return 0;

}



