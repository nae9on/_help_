/*
 * roi.cpp
 *
 *  Created on: 09 Apr 2020
 *      Author: ahkad
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void roi(){

	Mat orig_image = imread("./images/cheetah.jpg", IMREAD_UNCHANGED);
	cout<<orig_image.size<<endl;

	int x = 0.5*orig_image.cols;
	int y = 0.5*orig_image.rows;
    int width {200}, height{200};
    int xc = x-width/2;
    int yc = y-height/2;
	Rect r(xc, yc, width, height);

    Mat region = orig_image(r); // data is not copied

    region = Scalar(0, 0, 0);

    namedWindow("New Image", WINDOW_AUTOSIZE);
    imshow("New Image", orig_image);

    waitKey(0);
}


