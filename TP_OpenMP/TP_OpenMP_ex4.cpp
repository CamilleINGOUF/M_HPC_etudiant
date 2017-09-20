
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include <omp.h>

// output data as a grayscale PNM image
void writePnm(std::ostream &os, int width, int height, 
        const std::vector<unsigned char> & data) 
{
    os << "P2" << std::endl;
    os << width << ' ' << height << std::endl;
    os << "255" << std::endl;
    for (unsigned char pixel : data) os << (unsigned)pixel << ' ';
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
    auto ind = [width]
        (std::vector<unsigned char>&data, int xx, int yy)->unsigned char & 
        { return data[yy*width+xx]; };

    // compute data1
    std::vector<unsigned char> data1(width*height);
    double startTime1 = omp_get_wtime();
    {
	    // compute image sequentially
	    std::mt19937 engine(0);
	    std::uniform_int_distribution<int> distribution(0, 255);
	    for (int x=0; x<width; x++)
		    for (int y=0; y<height; y++)
			    ind(data1,x,y) = distribution(engine);
    }
    double endTime1 = omp_get_wtime();
    double deltaTime1 = endTime1 - startTime1;

    // compute data2
    std::vector<unsigned char> data2(width*height);
    double startTime2 = omp_get_wtime();
    {
	    // compute image parallely
	    // shared RNG
	    // TODO
    }
    double endTime2 = omp_get_wtime();
    double deltaTime2 = endTime2 - startTime2;

    // compute data3
    std::vector<unsigned char> data3(width*height);
    double startTime3 = omp_get_wtime();
    {
	    // compute image parallely
	    // private RNG, same seed
	    // TODO
    }
    double endTime3 = omp_get_wtime();
    double deltaTime3 = endTime3 - startTime3;

    // compute data4
    std::vector<unsigned char> data4(width*height);
    double startTime4 = omp_get_wtime();
#pragma omp parallel
    {
	    // compute image parallely
	    // private RNG, different seed
	    // TODO
    }
    double endTime4 = omp_get_wtime();
    double deltaTime4 = endTime4 - startTime4;

    // output chrono
    std::cout << "width = " << argv[1] << std::endl;
    std::cout << "height = " << argv[2] << std::endl;
    std::cout << "nb proc = " << omp_get_max_threads() << std::endl;
    std::cout << "delta time 1 = " << deltaTime1 << std::endl;
    std::cout << "delta time 2 = " << deltaTime2 << std::endl;
    std::cout << "delta time 3 = " << deltaTime3 << std::endl;
    std::cout << "delta time 4 = " << deltaTime4 << std::endl;

    // write image in a file
    if (argc==4)
    {
        std::ofstream ofs1(std::string("random_1_") + argv[3]);
        writePnm(ofs1, width, height, data1);

        std::ofstream ofs2(std::string("random_2_") + argv[3]);
        writePnm(ofs2, width, height, data2);

        std::ofstream ofs3(std::string("random_3_") + argv[3]);
        writePnm(ofs3, width, height, data3);

        std::ofstream ofs4(std::string("random_4_") + argv[3]);
        writePnm(ofs4, width, height, data4);
    }

    return 0;
}

