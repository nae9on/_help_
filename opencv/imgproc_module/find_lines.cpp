/*
 * find_lines.cpp
 *
 *  Created on: 14 Apr 2020
 *      Author: ahkad
 *
 * Ref: https://docs.opencv.org/master/dd/dd7/tutorial_morph_lines_detection.html
 */

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void show_wait_destroy(const char* winname, cv::Mat img) {
    imshow(winname, img);
    moveWindow(winname, 500, 0);
    waitKey(0);
    destroyWindow(winname);
}

void find_lines()
{
    Mat src = imread("./images/music2.jpg", IMREAD_COLOR);

    // Show source image
    imshow("source", src);

    // Transform source image to gray if it is not already
    Mat gray;
    if (src.channels()==3) cvtColor(src, gray, COLOR_BGR2GRAY);
    else gray = src;

    // Show gray image
    show_wait_destroy("gray", gray);

    // Apply adaptiveThreshold to the bitwise_not of gray (notice the ~ symbol)
    // ADAPTIVE_THRESH_MEAN_C = the threshold value T(x,y) is a mean of the
    // blockSize×blockSize neighborhood of (x,y) minus C
    Mat bw;
    //cout<<~gray<<endl<<endl;
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    //cout<<bw<<endl<<endl;
    // Show binary image
    show_wait_destroy("binary", bw);

    // Create the images that will be used to extract the horizontal and vertical lines
    Mat horizontal = bw.clone();
    Mat vertical = bw.clone();

    // Specify size on horizontal axis
    int horizontal_size = horizontal.cols / 2;
    // Create structure element for extracting horizontal lines through morphology operations
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));
    // Apply morphology operations
    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    // Show extracted horizontal lines
    show_wait_destroy("horizontal", horizontal);

    // Specify size on vertical axis
    int vertical_size = vertical.rows / 100;
    // Create structure element for extracting vertical lines through morphology operations
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));
    // Apply morphology operations
    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
    // Show extracted vertical lines
    show_wait_destroy("vertical", vertical);

    // Inverse vertical image
    bitwise_not(vertical, vertical);
    show_wait_destroy("vertical_bit", vertical);

    // Extract edges and smooth image according to the logic
    // 1. extract edges
    // 2. dilate(edges)
    // 3. src.copyTo(smooth)
    // 4. blur smooth img
    // 5. smooth.copyTo(src, edges)
    // Step 1
    Mat edges;
    adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
    show_wait_destroy("edges", edges);
    // Step 2
    Mat kernel = Mat::ones(2, 2, CV_8UC1);
    dilate(edges, edges, kernel);
    show_wait_destroy("dilate", edges);
    // Step 3
    Mat smooth;
    vertical.copyTo(smooth);
    // Step 4
    blur(smooth, smooth, Size(2, 2));
    // Step 5
    smooth.copyTo(vertical, edges);
    // Show final result
    show_wait_destroy("smooth - final", vertical);
}
