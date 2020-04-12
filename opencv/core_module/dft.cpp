/*
 * dft.cpp
 *
 *  Created on: 09 Apr 2020
 *      Author: ahkad
 *
 *  Ref: https://docs.opencv.org/master/d8/d01/tutorial_discrete_fourier_transform.html
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void dft(){

	Mat orig_image = imread("./images/imageTextNRotated.png", IMREAD_GRAYSCALE);

	// pad image boundaries with 0's to make image size a multiple of 2, 3 and 5.
	// Note: data is copied here
	// Note: It is  possible to make border w/o copying the middle part of the image (refer doc)
    Mat padded;
    int m {getOptimalDFTSize(orig_image.rows)};
    int n {getOptimalDFTSize(orig_image.cols)};
    copyMakeBorder(orig_image, padded,
    		0, m - orig_image.rows,
			0, n - orig_image.cols,
			BORDER_CONSTANT, Scalar::all(0));

    // Convert input image to float (since DFT returns float/double)
    // and add extra channel for the complex part
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI; // merge the real and complex parts into a new image with 2 channels
    merge(planes, 2, complexI);

    // perform in-place DFT of the now complex image
    dft(complexI, complexI);

    // Calculate magnitude of DFT
    split(complexI, planes); // reverse of merge
    magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
    Mat magI = planes[0];

    // Transform magnitude of DFT to log scale
    magI += Scalar::all(1); // avoid log of zero
    log(magI, magI); // switch to logarithmic scale

    // Crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    // Rearrange the quadrants of Fourier image so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;
    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
    Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);                     // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // Transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).
    normalize(magI, magI, 0, 1, NORM_MINMAX);

    namedWindow("DFT Image", WINDOW_AUTOSIZE);
    imshow("DFT Image", magI);

    waitKey(0);
}
