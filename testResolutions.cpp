/*
***********************************
*
* Program name: testResolutions
*
*
* Version: 0.1
*
* Author: Meir Michanie <meirm@riunx.com>
*
* latest version of this file can be obtained at 
* http://www.riunx.com/public/testResolutions-latest.zip
*
* to compile run:
* 
* g++ -o testResolutions -I /home/ubuntu/opencv-3.1.0/include -O2 -g -Wall testResolutions.cpp -L /home/ubuntu/opencv-3.1.0/lib -lopencv_core  -lopencv_videoio  -std=gnu++11
*
* compiled using opencv 3.1.0 from http://stackoverflow.com/questions/4951952/integer-arguments-for-c
*
* export LD_LIBRARY_PATH=/home/ubuntu/opencv-3.1.0/lib:$LD_LIBRARY_PATH
* ./testResolutions
* 
*
***********************************
*/

#include <iostream>
#include "opencv2/opencv.hpp"
#include "testResolutions.hpp"

using namespace cv;
using namespace std;

int x=640;
int y=480;

Mat frame[3];
Mat *currentFrame;
int current=0;
int videoport=0;
VideoCapture *cap;
void setXY(int xres, int yres){
    cap->set(CV_CAP_PROP_FRAME_WIDTH,xres);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT,yres);
	int rx=cap->get(CV_CAP_PROP_FRAME_WIDTH);
	int ry=cap->get(CV_CAP_PROP_FRAME_HEIGHT);
	if( xres == rx && yres == ry){
		cout << "(" << xres << "," << yres << ")" << endl;
	}
}


void CaptureFrames(){
	  cap= new VideoCapture(videoport);
    if(!cap->isOpened()){
	cout << "Couldn't open device" << endl;
	return ;
	}
	cout << "Capturing" << endl;
	int rows =  sizeof resArray / sizeof resArray[0];
	for(int i=0; i< rows; i++){
		setXY(resArray[i][0],resArray[i][1]);
	}
}
void usage(int ec){
	cout << "Usage: testResolutions <n>" << endl;
	cout << "i.e. " <<endl;
	cout << "testResolutions 1 # /dev/video1" << endl;
}
int main(int argc, char * argv[] ){
	if ( argc != 2 ) usage(1);
	videoport=atoi(argv[1]);
	CaptureFrames();
	return(0);
}
