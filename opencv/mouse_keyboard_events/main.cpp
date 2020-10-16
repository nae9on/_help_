#include "MouseEvents.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    auto inFilename = "/home/akadar/Desktop/_help_/opencv/mouse_keyboard_events/video/in.mp4"; // pass 0 for webcam input

    MouseEvents::CMouseEvents MEvents{"Draw"};

    VideoCapture inVid;
    inVid.open(inFilename);
    if (!inVid.isOpened())
    {
        cout<<"Video capture could not be initialized for file: "<<inFilename<<endl;
        return -1;
    }

    Mat_<Vec3b> Frame;
    inVid >> Frame;

    while(1)
    {
        MEvents.Show(Frame);
        inVid >> Frame;
        if(Frame.empty())
        {
            inVid.set(CAP_PROP_POS_MSEC, 1);
            inVid >> Frame;
        }
    }

    return 0;
}
