// SAXPY example (Single-precision Alpha X Plus Y)

#define __CL_ENABLE_EXCEPTIONS

#include "opencHelp.hpp"

int main(int argc, char ** argv)
{

    // print OpenCL platforms and devices
    opencHelp::printPlatformsAndDevices();

    // check command line arguments
    if (argc < 4 or argc > 5)
    {
        std::cout << "Usage: " << argv[0] << " <iPlatform> <iDevice> <dataSize> [outputFile]" << std::endl;
        exit(-1);
    }
    //unsigned iPlatform = std::stoi(argv[1]);
    //unsigned iDevice = std::stoi(argv[2]);
    int dataSize = std::stoi(argv[3]);;
    const char * outputFilename = argc == 5 ? argv[4] : nullptr;

    // load data to host (CPU)
    opencHelp::Random rng;
    float dataAlpha = 42.f*rng.rand();
    std::vector<float> dataX(dataSize);
    std::vector<float> dataY(dataSize);
    for (int k=0; k<dataSize; k++)
    {
        dataX[k] = rng.rand();
        dataY[k] = rng.rand();
    }
    //int dataFullSize = dataSize * sizeof(float);
    std::vector<float> dataZ(dataSize);

    opencHelp::Chrono chrono;

    // compute
#pragma omp parallel for
    for (int i=0; i<dataSize; i++)
        dataZ[i] = dataAlpha * dataX[i] + dataY[i];

    double time = chrono.elapsed();
    std::cout << "Time: " << time << " s" << std::endl;

    // check results
    std::vector<float> expectedVector(dataSize);
    for (int i=0; i<dataSize; i++)
        expectedVector[i] = dataAlpha * dataX[i] + dataY[i];
    bool resultOk = opencHelp::validateResult(dataZ, expectedVector, 1e-6);
    std::cout << "Results: " << (resultOk ? "passed" : "failed") << std::endl;

    // output results
    if (outputFilename)
    {
        std::ofstream fs(outputFilename);
	fs << std::endl << "alpha =" << std::endl;
        fs << dataAlpha << std::endl;
        fs << std::endl << "X = " << std::endl;
        for (int i=0; i<dataSize; i++)
            fs << dataX[i] << std::endl;
        fs << std::endl << "Y = " << std::endl;
        for (int i=0; i<dataSize; i++)
            fs << dataY[i] << std::endl;
        fs << std::endl << "resulting Z = " << std::endl;
        for (int i=0; i<dataSize; i++)
            fs << dataZ[i] << std::endl;
        fs << std::endl << "expected Z = " << std::endl;
        for (int i=0; i<dataSize; i++)
            fs << expectedVector[i] << std::endl;
    }

    return 0;

}

