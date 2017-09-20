
// matrix-vector multiplication

#define __CL_ENABLE_EXCEPTIONS

#include "opencHelp.hpp"

int main(int argc, char ** argv)
{

    // print OpenCL platforms and devices
    opencHelp::printPlatformsAndDevices();

    // check command line arguments
    if (argc < 5 or argc > 6)
    {
        std::cout << "Usage: " << argv[0] << " <iPlatform> <iDevice> <width> <height> [outputFile]" << std::endl;
        exit(-1);
    }
    //unsigned iPlatform = std::stoi(argv[1]);
    //unsigned iDevice = std::stoi(argv[2]);
    int width = std::stoi(argv[3]);
    int height = std::stoi(argv[4]);
    const char * outputFilename = argc == 6 ? argv[5] : nullptr;

    // generate random data
    std::vector<float> inputMatrix(width*height);
    std::vector<float> inputVector(width);
    std::vector<float> outputVector(height);
    opencHelp::Random rng;
    for (int k=0; k<width*height; k++)
        inputMatrix[k] = rng.rand();
    for (int j=0; j<width; j++)
        inputVector[j] = rng.rand();

    opencHelp::Chrono chrono;

    // compute
#pragma omp parallel for
    for (int i=0; i<height; i++)
    {
        float r = 0.f;
        for (int j=0; j<width; j++)
            r += inputMatrix[i*width+j] * inputVector[j];
        outputVector[i] = r;
    }

    double time = chrono.elapsed();
    std::cout << "Time: " << time << " s" << std::endl;

    // check results
    std::vector<float> expectedVector(height);
    for (int i=0; i<height; i++)
    {
        float expected = 0.f;
        for (int j=0; j<width; j++)
            expected += inputMatrix[i*width + j] * inputVector[j];
        expectedVector[i] = expected;
    }
    bool resultOk = opencHelp::validateResult(outputVector, expectedVector, 1e-4);
    std::cout << "Results: " << (resultOk ? "passed" : "failed") << std::endl;

    // output results
    if (outputFilename)
    {
        std::ofstream fs(outputFilename);
	fs << std::endl << "M =" << std::endl;
        for (int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
                fs << inputMatrix[i*width+j] << ' ';
            fs << std::endl;
        }
        fs << std::endl << "V1 =" << std::endl;
        for (int i=0; i<width; i++)
            fs << inputVector[i] << std::endl;
        fs << std::endl << "resulting V2 =" << std::endl;
        for (int i=0; i<height; i++)
            fs << outputVector[i] << std::endl;
        fs << std::endl << "expected V2 =" << std::endl;
        for (int i=0; i<height; i++)
            fs << expectedVector[i] << std::endl;
    }

    return 0;

}

