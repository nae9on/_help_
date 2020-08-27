/*
 * main.cpp
 *
 *  Created on: 17 Aug 2020
 *      Author:
 *
 *  References:
 *  https://docs.opencv.org/master/d1/dc5/tutorial_background_subtraction.html
 */

#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

int main(/*int argc, char* argv[]*/)
{
    auto InputFilename = "/home/akadar/Desktop/_help_/opencv/videoanalysis_module/videoData/in.mp4";

    // Create Background Subtractor objects
    Ptr<BackgroundSubtractor> PtrBackSub;
    std::string BS_Algorithm{"MOG2"};
    if (BS_Algorithm == "MOG2")
    {
        PtrBackSub = createBackgroundSubtractorMOG2();
    }
    else if (BS_Algorithm == "KNN")
    {
        PtrBackSub = createBackgroundSubtractorKNN();
    }
    else
    {
        cout<<"Unknown background subtraction algorithm "<<BS_Algorithm<<std::endl;
        return -1;
    }

    // Video input
    VideoCapture InputVideo;
    InputVideo.open(InputFilename);
    if (!InputVideo.isOpened())
    {
        cout<<"Video capture could not be initialized for file: "<<InputFilename<<endl;
        return -1;
    }

    // Get width and height from the meta information attached to the video
    // Note the get function is a general function and always returns a double
    Size FrameSize = Size(static_cast<int>(InputVideo.get(CAP_PROP_FRAME_WIDTH)),
                       static_cast<int>(InputVideo.get(CAP_PROP_FRAME_HEIGHT)));

    cout<<"Video frame: Width="<<FrameSize.width<<"  Height="<<FrameSize.height
         <<" and #Frames="<<InputVideo.get(CAP_PROP_FRAME_COUNT)<<endl;

    // Get Codec Type
    int CodecType = static_cast<int>(InputVideo.get(CAP_PROP_FOURCC));

    // Print codec type in human-readable form
    union {int i; char c[5];} Union_CodecType ;
    Union_CodecType.i = CodecType; // From Int to char via union
    Union_CodecType.c[4]='\0';
    cout<<"Input codec type: "<<Union_CodecType.c<<" "<<CodecType<<endl;

    // Video output
    std::string outFilename{"/home/akadar/Desktop/_help_/opencv/videoanalysis_module/videoData/out.mp4"}; // only avi format is supported
    VideoWriter OutputVideo;
    // for grayscale video, last argument should be false
    OutputVideo.open(outFilename, CodecType, InputVideo.get(CAP_PROP_FPS), FrameSize, true);
    if (!OutputVideo.isOpened())
    {
        cout<<"Video writer could not be initialized for file: "<<outFilename<<endl;
        return -1;
    }

    int FrameCounter{-1}; // Frame counter

    Mat InputFrame, ForegroundMask;
    Mat BackgroundFrame;

    InputVideo.set(CAP_PROP_POS_FRAMES, 1);  // go to the 1st frame in the video

    while (true)
    {
        InputVideo >> InputFrame;

        ++FrameCounter;

        if (InputFrame.empty())
        {
            break;
        }

        // Update the background model
        PtrBackSub->apply(InputFrame, ForegroundMask);
        PtrBackSub->getBackgroundImage(BackgroundFrame);

        // Get the frame number and write it on the current frame
        rectangle(InputFrame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        stringstream ss;
        ss << InputVideo.get(CAP_PROP_POS_FRAMES);
        string FrameCounterberString = ss.str();
        putText(InputFrame, FrameCounterberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

        imshow("Frame", InputFrame);
        imshow("FG Mask", ForegroundMask);
        imshow("Background Image", BackgroundFrame);

        OutputVideo << BackgroundFrame;

        // Get the input from the keyboard
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
        {
            break;
        }
    }

    InputVideo.release();
    OutputVideo.release();

    return 0;
}
