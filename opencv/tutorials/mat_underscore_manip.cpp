/*
 * mat_underscore_manip.cpp
 *
 *  Created on: 07 Apr 2020
 *      Author: ahkad
 *
 * Ref: https://itom.bitbucket.io/latest/docs/07_plugins/development/openCVMat.html
 *
 * The class `Mat_<_Tp>` is a *thin* template wrapper on top of the Mat class.
 * While Mat is sufficient in most cases, Mat_ can be more convenient when knowing
 * the matrix type at the compilation time.
 *
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void mat_underscore_manip(){

	Mat orig_image = imread("./images/belgium.jpg", IMREAD_UNCHANGED);

	Mat copied_original = orig_image.clone(); // deep copy

	//To use Mat_ for multi-channel images/matrices, pass Vec as a Mat_ parameter:
	Mat_<Vec3b> new_image(copied_original); // shallow copy

	// Test
    //randu(new_image, Scalar::all(0), Scalar::all(255));

    uchar table[256];
    int divideWidth{10};
    for (int i = 0; i < 256; ++i){
    	table[i] = static_cast<uchar>(divideWidth * (i/divideWidth));
    }

    // Mat_ is fully compatible with C++11 range-based for loop. For example such loop
    // can be used to safely apply look-up table:
    // Mat_ provides begin and end iterators which are smart enough to skip gaps in the
    // end of rows
	for(auto& elem : new_image) {
		for(int i=0; i<new_image.channels(); ++i)
			elem[i] = table[elem[i]];
    }

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", orig_image);
    namedWindow("New Image", WINDOW_AUTOSIZE);
    imshow("New Image", new_image);

    waitKey(0);
}
