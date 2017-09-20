#include "image.hpp"

#include <chrono>

using namespace std;

int main(int argc, char ** argv)
{
    // get command line arguments
    if (argc!=2)
    {
        cout << "usage: " << argv[0] << " <radius> " << endl;
        return -1;
    }
    int radius = stoi(argv[1]);

    chrono::time_point<chrono::system_clock> t0 = chrono::system_clock::now();

    // read image
    image_t image1;
    int width, height;
    readPnm("backloop.pnm", width, height, image1);
    if (width <= 0 or height <= 0)
    {
        cout << "error: failed to read pnm file" << endl;
        exit(-1);
    }

    // compute blur
    //int x0 = 0, y0 = 0, x1 = width, y1 = height;  // the whole image
    int x0 = 400, y0 = 100, x1 = 1000, y1 = 400;    // only the guy doing backloop
    image_t image2 = blur(image1, width, height, radius, x0, y0, x1, y1);

    // write blurred image
    writePnm("output.pnm", x1-x0, y1-y0, image2);
    chrono::time_point<chrono::system_clock> t1 = chrono::system_clock::now();

    // display computation times
    chrono::duration<double> totalTime = t1 - t0;
    cout << "totalTime = " << totalTime.count() << endl;

    return 0;
}

