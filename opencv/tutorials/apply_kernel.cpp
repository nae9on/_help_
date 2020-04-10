/*
 * apply_kernel.cpp
 *
 *  Created on: 08 Apr 2020
 *      Author: ahkad
 *
 * Ref: https://docs.opencv.org/master/d7/d37/tutorial_mat_mask_operations.html
 * Ref: https://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void Sharpen(const Mat& myImage, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
    const int nChannels = myImage.channels();
    Result.create(myImage.size(),myImage.type());
    for(int j = 1 ; j < myImage.rows-1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);
        uchar* output = Result.ptr<uchar>(j);
        for(int i= nChannels;i < nChannels*(myImage.cols-1); ++i)
        {
            *output++ = saturate_cast<uchar>(5*current[i]
                         -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
    // set the boundaries to zero, where the mask runs outside image boundary
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
}

void apply_kernel(){

	Mat orig_image = imread("./images/sunnyday.jpg", IMREAD_UNCHANGED); // IMREAD_GRAYSCALE

	Mat new_image1, new_image2, threshold_image;

	threshold_image.create(orig_image.size(),orig_image.type());

	//Sharpen(orig_image, new_image);

	// define mask (a single-channel matrix) for the kernel
    Mat sharpening_kernel = (Mat_<char>(3,3) <<  0, -1,  0, -1,  5, -1, 0, -1,  0);
    Mat vert_edge_detect = (Mat_<char>(3,3) <<  1, 0, -1, 1,  0, -1, 1, 0, -1);
    Mat horiz_edge_detect = (Mat_<char>(3,3) <<  1, 1, 1, 0,  0, -0, -1, -1, -1);

    // Apply kernel (same kernel is applied to all the channels)
    // The function does actually compute correlation, not the convolution
    // Note orig_image.depth() and saturate_cast<uchar> in Sharpen!!
    // kernels are neighborhood operators
    filter2D(orig_image, new_image1, orig_image.depth(), vert_edge_detect);
    filter2D(orig_image, new_image2, orig_image.depth(), horiz_edge_detect);

    double thresh{100};
    double maxval{0}; // not used below
    threshold(max(new_image1,new_image2), threshold_image, thresh, maxval, THRESH_TOZERO);

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", orig_image);
    namedWindow("New Image", WINDOW_AUTOSIZE);
    imshow("New Image", threshold_image);

    waitKey(0);
}
