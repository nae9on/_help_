/*
 * main.cpp
 *
 *  Created on: 24 Apr 2020
 *      Author: ahkad
 *
 *  References:
 *  https://docs.opencv.org/master/d5/dc4/tutorial_video_input_psnr_ssim.html
 *  https://docs.opencv.org/master/d7/d9e/tutorial_video_write.html
 */

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
    auto inFilename = "/home/akadar/Desktop/_help_/opencv/videoio_module/data/in.avi"; // pass 0 for webcam input

    // Video input
    VideoCapture inVid; // Main class for video manipulation
    inVid.open(inFilename);
    if (!inVid.isOpened())
    {
        cout<<"Video capture could not be initialized for file: "<<inFilename<<endl;
        return -1;
    }

    // Get width and height from the meta information attached to the video
    // Note the get function is a general function and always returns a double
    Size inSize = Size(static_cast<int>(inVid.get(CAP_PROP_FRAME_WIDTH)),
                       static_cast<int>(inVid.get(CAP_PROP_FRAME_HEIGHT)));

    cout<<"Video frame: Width="<<inSize.width<<"  Height="<<inSize.height
         <<" and #Frames="<<inVid.get(CAP_PROP_FRAME_COUNT)<<endl;

    // Get Codec Type
    int codec_type = static_cast<int>(inVid.get(CAP_PROP_FOURCC));

    // Print codec type in human-readable form
    union {int i; char c[5];} u_codec_type ;
    u_codec_type.i = codec_type; // From Int to char via union
    u_codec_type.c[4]='\0';
    cout<<"Input codec type: "<<u_codec_type.c<<" "<<codec_type<<endl;

    // Video output
    std::string outFilename{"/home/akadar/Desktop/_help_/opencv/videoio_module/data/out.avi"}; // only avi format is supported
    VideoWriter outVid;
    // for grayscale video, last argument should be false
    outVid.open(outFilename, codec_type, inVid.get(CAP_PROP_FPS), inSize, false);
    if (!outVid.isOpened())
    {
        cout<<"Video writer could not be initialized for file: "<<outFilename<<endl;
        return -1;
    }

    std::string winname{"Test video"};
    namedWindow(winname, WINDOW_AUTOSIZE);

    Mat_<Vec3b> frame;
    Mat_<Vec<uchar, 1>> gray_frame;

    int delay{33}; // corresponds to ~30 FPS

    // set properties if needed
    inVid.set(CAP_PROP_POS_MSEC, 1);  // go to the 1 second in the video
    //inVid.set(CAP_PROP_POS_FRAMES, 100); // go to the 100th frame of the video

    int frameNum{-1}; // Frame counter

    for(;;) // read until end of video is reached
    {
        // A read method is made of a frame grab and a decoding applied on that.
        inVid >> frame; // or inVid.read(frame);

        if (frame.empty()){break;} // check if end of video is reached

        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

        ++frameNum;

        if(frameNum%10==0) cout<<"Frame: " <<frameNum<<endl;

        imshow(winname, gray_frame);

        outVid << gray_frame; // or outVid.write(gray_frame);

        waitKey(delay);
    }

    // optional as video will be automatically released when object is destroyed
    inVid.release();
    outVid.release();

    return 0;
}
