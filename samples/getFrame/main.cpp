#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream> // std::cout
/*
g++ -DCAMEDEV=0 capth.cpp `pkg-config --libs --cflags opencv` -lFPS -std=gnu++11  -pthread -o capth

or

g++ main.cpp  -I/home/ubuntu/opencv-3.1.0/include/ -L/home/ubuntu/opencv-3.1.0/lib/  -lopencv_core -lopencv_video  -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs -std=gnu++11  -o getFrame


*/

using namespace std;
using namespace cv;
Mat CameraFrame[2];
Mat *currentFrame;
int framePointer=1;
int run = 1;
int camdev=0;
int x=800;
int y=600;

void CaptureFrames() {
  VideoCapture capture(camdev);
  if (!capture.isOpened()) {
      cout << "cannot open camera" << endl;
      exit(1);
  }
  capture.set(3,x);
  capture.set(4,y);

  if (x != int(capture.get(3)) || y != int(capture.get(4)) ){
      exit(2);
  }
  printf("Resolution (%0.0fx%0.0f)\n",capture.get(3),capture.get(4));
  capture >> CameraFrame[1 - framePointer];
  framePointer = 1 - framePointer;
  currentFrame = &CameraFrame[framePointer];
  imwrite("frame.jpg",*currentFrame);
}

int main(int argc, char** argv) {
  if(const char* env_p = std::getenv("XRES")){
     x=atoi(env_p);
  }
  if(const char* env_p = std::getenv("YRES")){
     y=atoi(env_p);
  }

  camdev=atoi(argv[0]);
  currentFrame = &CameraFrame[0];
  CaptureFrames();
  return (0);
}
