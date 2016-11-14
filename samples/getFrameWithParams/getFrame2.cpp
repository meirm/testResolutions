#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream> // std::cout
#include <boost/program_options.hpp>
#include <string.h>
/*
g++ -DCAMEDEV=0 capth.cpp `pkg-config --libs --cflags opencv` -lFPS -std=gnu++11  -pthread  -lboost_program_options -o capth

or

g++ getFrame2.cpp  -I/usr/local/opencv-3.1.0/include/ -L/usr/local/opencv-3.1.0/lib/  -lopencv_core -lopencv_video  -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs -std=gnu++11  -lboost_program_options -o getFrame2



*/

using namespace std;
using namespace cv;
namespace po = boost::program_options;

int videoport =0;
int x=800;
int y=600;
string imagefile="evidence.jpg";



Mat CameraFrame[2];
Mat *currentFrame;
int framePointer=1;
int run = 1;

void CaptureFrames() {
  VideoCapture capture(videoport);
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

void init_prog(int ac, char * av[] ){
try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("video", po::value<int>(), "set video device <N>")
            ("filename", po::value<string>(), "set (output) image filename")
            ("xres", po::value<int>(), "x resolution")
            ("yres", po::value<int>(), "y resolution")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            exit(0);
	}
        if (vm.count("video")) {
            cout << "video set to "
                 << vm["video"].as<int>() << ".\n";
		videoport=vm["video"].as<int>();
        } else {
            cout << "video was not set. Using default\n";
        }
       
	if (vm.count("filename")) {
            cout << "filename set to "
                 << vm["filename"].as<string>() << ".\n";
		imagefile=vm["filename"].as<string>();
        } else {
            cout << "image was not set. Using default\n";
	}
	if (vm.count("xres")) {
            cout << "xres set to "
                 << vm["xres"].as<int>() << ".\n";
		x=vm["xres"].as<int>();
        } else {
            cout << "xres was not set. Using default\n";
        }
        
        if (vm.count("yres")) {
            cout << "yres set to "
                 << vm["yres"].as<int>() << ".\n";
		y=vm["yres"].as<int>();
        } else {
            cout << "yres was not set. Using default\n";
	}
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        exit(1);
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }
}

int main(int argc, char** argv) {
  init_prog(argc, argv);
  currentFrame = &CameraFrame[0];
  CaptureFrames();
  return (0);
}
