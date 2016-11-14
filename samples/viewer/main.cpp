#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <thread>         // std::thread
#include <iostream> // std::cout
#include <FPS.hpp>
/*
g++  capth.cpp `pkg-config --libs --cflags opencv` -lFPS -std=gnu++11  -pthread -o capth

or


g++ main.cpp  -I/home/ubuntu/opencv-3.1.0/include/ -L/home/ubuntu/opencv-3.1.0/lib/ -lopencv_core  -lopencv_highgui -lopencv_video  -lopencv_videoio -lFPS -std=gnu++11  -pthread -o viewer

*/

using namespace std;
using namespace cv;
Mat CameraFrame[2];
Mat *currentFrame;
int framePointer=1;
int run = 1;
int camdev=0;

void CaptureFrames() {
  VideoCapture capture(camdev);
  if (!capture.isOpened()) {
      cout << "cannot open camera" << endl;
      return;
  }
  capture.set(3,atoi(getenv("XRES")));
  capture.set(4,atoi(getenv("YRES")));
  printf("Resolution (%0.0fx%0.0f)\n",capture.get(3),capture.get(4));
  FPS fps;
  fps.start();
   while (run == 1) {
        capture >> CameraFrame[1 - framePointer];
        framePointer = 1 - framePointer;
        currentFrame = &CameraFrame[framePointer];
        fps.update();
    }
    fps.stop();
    cout << "Total time elapsed: " << fps.elapsed() << endl;
    cout << "FPS: " << fps.fps() << endl;
    waitKey(1000);
}

void ProcessFrames() {
	  while (true) {
	    if (!currentFrame->empty()) {
		imshow("FPS", *currentFrame);
	   }
	   if (waitKey(1) >= 0 ){
		run =0;
		break;
	   }
	}
	waitKey(1000);
}

int main(int argc, char** argv) {
  camdev=atoi(argv[0]);
  currentFrame = &CameraFrame[0];
  thread t1(CaptureFrames);
  ProcessFrames();
  t1.join();
  return (0);
}
