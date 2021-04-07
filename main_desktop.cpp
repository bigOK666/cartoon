/*
* decolor.cpp
*
* Author:
* Siddharth Kherada <siddharthkherada27[at]gmail[dot]com>
*
* This tutorial demonstrates how to use OpenCV Decolorization Module.
*
* Input:
* Color Image
*
* Output:
* 1) Grayscale image
* 2) Color boost image
*
*/

//#include "opencv2/photo.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
#include"opencv2/videoio.hpp"
#include "opencv2/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    int cameraNumber = 0;

    if(argc >1){
        cameraNumber = atoi(argv[1]);

    }

    //get access to the camera
    cv::VideoCapture camera;
    camera.open(cameraNumber);

    if (!camera.isOpened()) {
        std::cerr << "Error: could not access the camera or video" << std::endl;
        exit(1);
    }

    //try to set the camera resolution
    camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
}
