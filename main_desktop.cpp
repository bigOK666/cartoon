/*
Mastering OpenCV with Practical Computer Vision Projects Chapter1
cartoon filter
*
*/


//#include"opencv2/videoio.hpp"
//#include "opencv2/core.hpp"
#include"opencv2/opencv.hpp"
#include"cartoon.h"
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

    while (true) {
        //grab the next camera frame
        //cv::Mat is image container
        cv::Mat cameraFrame;
        //stream camera frame to cameraFrame
        camera >> cameraFrame;
        if (cameraFrame.empty()) {
            std::cerr << "Error: could not grab a camera frame" << std::endl;
            exit(1);
        }
        //create a blank output image, where we will draw
        cv::Mat displayedFrame(cameraFrame.size(), CV_8UC3);

        //run the cartoonifier filter on camera frame
        cartoonifyImage(cameraFrame, displayedFrame);
        //display the processed image onto the screen
        imshow("Cartoonifier", displayedFrame);

        //we need to wait at least 20ms so that the image can be displayed on the screen
        //also check if a key was pressed in the GUI window
        //the pressed key should be a char to support Linux
        char keypress = cv::waitKey(20);
        if (keypress == 27) {//Escape key
            break;

        }

    }//end while
}
