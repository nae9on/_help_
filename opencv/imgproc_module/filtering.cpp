/*
 * filtering.cpp
 *
 *  Created on: 12 Apr 2020
 *      Author: ahkad
 *
 * A low-pass filter attenuates noise which typically occurs as uncorrelated
 * high frequency signal thereby rendering a smoothing effect to the image.
 *
 * Ref: https://docs.opencv.org/master/dc/dd3/tutorial_gausian_median_blur_bilateral_filter.html
 * http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/MANDUCHI1/Bilateral_Filtering.html
 */

#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

void filtering(){

    Mat src = imread("./images/cheetah.jpg", IMREAD_GRAYSCALE);

    Mat dst = Mat::zeros(src.size(), src.type());

    // kernel width and height
    int kw{5}, kh{5};

    // Homogeneous Blur using the normalized box filter
    //blur(src, dst, Size(kw, kh), Point(-1,-1));

    // Note kernel width and height must be odd
    //GaussianBlur(src, dst, Size(kw, kh), 0, 0);

    // A square kernel is used with odd kernel size
    //medianBlur( src, dst, kw);

    // bilateralFilter can reduce unwanted noise very well while keeping edges
    // fairly sharp. However, it is very slow compared to most filters.
    const int diameter{10}; // Large filters (d >= 5) are very slow
    // When it is -ve, the diameter is determined by sigma values

    // When sigma is small (<=10), the filter will not have much effect
    // When sigma is large (>= 150), they will have a very strong effect
    double sigmaColor{diameter}, sigmaSpace{diameter};
    bilateralFilter(src, dst, diameter, sigmaColor, sigmaSpace, BORDER_DEFAULT);

    // To suppress unused variable warnings
    (void)kw;
    (void)kh;

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", src);
    namedWindow("New Image", WINDOW_AUTOSIZE);
    imshow("New Image", dst);
    waitKey(0);
}
