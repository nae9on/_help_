/*
 * trackbar.cpp
 *
 *  Created on: 12 Apr 2020
 *      Author: ahkad
 */

#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

struct datastruct{

    Mat src;
    Mat_<Vec3b> target;
    string winName;
    datastruct(Mat m, string wN){
        src = m;
        winName = wN;
    }
    void src2target(){
        // the target matrix is reallocated when type or size is different than
        // the source image o.w. no reallocation (as in the present case)
        src.copyTo(target);
    }
};

void gamma_correct(int gamma_val, void* data)
{
    datastruct* ptr = static_cast<datastruct*>(data);

    uchar table[256];
    for (int i = 0; i < 256; ++i){
        table[i] = saturate_cast<uchar>(pow(i/255.0, gamma_val/10.0) * 255.0);
    }

    // initialize target
    ptr->src2target();

    for(auto& elem : ptr->target) {
        for(int i=0; i<ptr->target.channels(); ++i)
            elem[i] = table[elem[i]];
    }
    imshow(ptr->winName, ptr->target);
}

void trackbar()
{
    // create window
    string winName{"Corrected Image"};
    namedWindow(winName, WINDOW_AUTOSIZE);

    // allocate data struct (which encapsulates source and target images)
    datastruct data{imread("./images/train.jpg", IMREAD_UNCHANGED), winName};

    // create trackbar and attach it to the window
    string trackbarName{"10 X Gamma"};
    int gamma_init {10};
    int const max_gamma {10};
    // Note: The minimal position on the trackbar is always 0
    createTrackbar(trackbarName, winName, &gamma_init, max_gamma, &gamma_correct, &data);

    /* The second last argument is a pointer to the function to be called every time the
    * slider changes position. This function should be prototyped as void Foo(int,void*);
    * where the first parameter is the trackbar position and the second parameter is the
    * user data (provided as last argument).
    * */

    // Initialize the content of the image for the initial trackbar position
    gamma_correct(gamma_init, &data);

    waitKey(0);
}
