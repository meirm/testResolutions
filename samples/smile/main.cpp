#include "opencv2/opencv.hpp"
// g++ -o smile -I /home/ubuntu/opencv-3.1.0/include -O2 -g -Wall main.cpp -L /home/ubuntu/opencv-3.1.0/lib -lopencv_core  -lopencv_highgui -lopencv_video  -lopencv_videoio  -std=gnu++11
using namespace cv;
int x,y;
int main(int argc, char** argv)
{
    x=atoi(argv[1]);
    y=atoi(argv[2]);
    VideoCapture cap(1);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.isOpened())
        return 1;
    cap.set(CV_CAP_PROP_FRAME_WIDTH,x);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,y);

    for(;;)
    {
          Mat frame;
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          imshow("this is you, smile! :)", frame);
          if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
   // cap.close();
    return 0;
}
