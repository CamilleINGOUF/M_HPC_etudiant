#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main() 
{
  //const std::string inputName = "bmx.avi";
  const std::string outputName = "bmx_edges.avi";

    timePoint_t tp0 = now();

    //cv::VideoCapture bmx(inputName);
    /*
    int width = bmx.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = bmx.get(CV_CAP_PROP_FRAME_HEIGHT);
    int fps = bmx.get(CV_CAP_PROP_FPS);*/

    // video writer
    // TODO : fourcc=MJPG
    //cv::VideoWriter video(outputName, CV_FOURCC('M','J','P','G'), fps, cv::Size(width, height));

    // process video
    cv::Mat inputFrame, edgeFrame;
    std::string basename, extension;
    getBasenameAndExtension("kermorvan.png", basename, extension);
    
    inputFrame = cv::imread("kermorvan.png");
    //while (true)
    {
        // get frame
      //bmx >> inputFrame;

        // detect edges 
        // TODO : gray, gaussian blur, canny, rgb
      cvtColor(inputFrame, edgeFrame, cv::COLOR_RGB2GRAY);
      blur(edgeFrame,edgeFrame,cv::Size(56,789));
      Canny(edgeFrame,edgeFrame,0,0,3);

        // write edges 
      //video.write(edgeFrame);
      imwrite(basename + "_imgEdge" + extension, edgeFrame);
    }

    timePoint_t tp1 = now();
    std::cout << duration(tp0, tp1) << " s\n";

    return 0;
}

