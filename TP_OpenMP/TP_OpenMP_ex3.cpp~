
#include <cmath>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include <omp.h>

unsigned char& ind(std::vector<unsigned char> & data, int w, int xx, int yy)
{
    return data[yy*w+xx]; 
}

// output data as a grayscale PNM image
void writePnm(std::ostream &os, int width, int height, 
        const std::vector<unsigned char> & data) 
{
    os << "P2" << std::endl;
    os << width << ' ' << height << std::endl;
    os << "255" << std::endl;
    for (unsigned char pixel : data) os << (unsigned)pixel << ' ';
}

std::vector<unsigned char> computeConvolutionSequential(
        std::vector<unsigned char> & data1, int width, int height)
{
    std::vector<unsigned char> data2(data1);
    // kernel 
    const int sk = 256;      // sum of all kernel coefs
    const int dk = 5;        // kernel size
    const int dk2 = dk/2;    // kernel half-size
    const int kernel[dk][dk] = 
    {
        { 1,  4,  6,  4,  1},
        { 4, 16, 24, 16,  4},
        { 6, 24, 36, 24,  6},
        { 4, 16, 24, 16,  4},
        { 1,  4,  6,  4,  1}
    };
    for (int x=dk2; x<width-dk2; x++)
    {
        for (int y=dk2; y<height-dk2; y++)
        {
            int p = 0;
            for (int k=0; k<dk; k++)
            {
                for (int l=0; l<dk; l++)
                {
                    p += kernel[k][l] * ind(data1, width, x-dk2+k, y-dk2+l);                   
                }
            }
            ind(data2, width, x, y) = p / sk;
        }
    }
    return data2;
}

std::vector<unsigned char> computeConvolutionParallel(
        std::vector<unsigned char> & data1, int /*width*/, int /*height*/)
{
    std::vector<unsigned char> data2(data1);
    // kernel 
    /*
    const int sk = 256;      // sum of all kernel coefs
    const int dk = 5;        // kernel size
    const int dk2 = dk/2;    // kernel half-size
    const int kernel[dk][dk] = 
    {
        { 1,  4,  6,  4,  1},
        { 4, 16, 24, 16,  4},
        { 6, 24, 36, 24,  6},
        { 4, 16, 24, 16,  4},
        { 1,  4,  6,  4,  1}
    };
    */

    // TODO
    return data2;
}

std::vector<unsigned char> computeConvolutionSeparate(
        std::vector<unsigned char> & data1, int /*width*/, int /*height*/)
{
    std::vector<unsigned char> data2(data1);
    // kernel 
    /*
    const int sk = 16;       // sum of all kernel coefs
    const int dk = 5;        // kernel size
    const int dk2 = dk/2;    // kernel half-size
    const int kernel[dk] = { 1,  4,  6,  4,  1 };
    */

    // TODO
    return data2;
}

int main(int argc, char ** argv)
{
    // check command line arguments
    if (argc!=4 and argc!=3)
    {
        std::cout << "usage; " << argv[0] 
            << " <width> <height> [PNM filename] \n";
        return -1;
    }

    // reserve image data
    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    std::vector<unsigned char> data1(width*height);
    int dx = 13;
    int dy = 37;

    // compute image data
#pragma omp parallel for 
    for (int x=0; x<width; x++)
    {
        for (int y=0; y<height; y++)
        {
            // compute checkerboard
            int qx = (x/dx)%2;
            int qy = (y/dy)%2;
            ind(data1, width, x, y) = qx == qy ? 255 : 0;
        }
    }

    // compute convolution (sequential)
    double startTimeSequential = omp_get_wtime();
    std::vector<unsigned char> data2Sequential 
        = computeConvolutionSequential(data1, width, height);
    double endTimeSequential = omp_get_wtime();
    double timeSequential = endTimeSequential - startTimeSequential;

    // compute convolution (parallel)
    double startTimeParallel = omp_get_wtime();
    std::vector<unsigned char> data2Parallel 
        = computeConvolutionParallel(data1, width, height);
    double endTimeParallel = omp_get_wtime();
    double timeParallel = endTimeParallel - startTimeParallel;

    // compute convolution (separate)
    double startTimeSeparate = omp_get_wtime();
    std::vector<unsigned char> data2Separate 
        = computeConvolutionSeparate(data1, width, height);
    double endTimeSeparate = omp_get_wtime();
    double timeSeparate = endTimeSeparate - startTimeSeparate;

    // output chrono
    std::cout << "width = " << argv[1] << std::endl;
    std::cout << "height = " << argv[2] << std::endl;
    std::cout << "nb proc = " << omp_get_max_threads() << std::endl;
    std::cout << "sequential convolution = " << timeSequential << std::endl;
    std::cout << "parallel convolution = " << timeParallel << std::endl;
    std::cout << "parallel speed-up = " << timeSequential / timeParallel 
        << std::endl;
    std::cout << "separate convolution = " << timeSeparate << std::endl;
    std::cout << "separate speed-up = " << timeSequential / timeSeparate 
        << std::endl;

    // write images 
    if (argc==4)
    {
        std::ofstream ofsSequential(std::string("sequential_") + argv[3]);
        writePnm(ofsSequential, width, height, data2Sequential);

        std::ofstream ofsParallel(std::string("parallel_") + argv[3]);
        writePnm(ofsParallel, width, height, data2Parallel);

        std::ofstream ofsSeparate(std::string("separate_") + argv[3]);
        writePnm(ofsSeparate, width, height, data2Separate);
    }

    return 0;
}

