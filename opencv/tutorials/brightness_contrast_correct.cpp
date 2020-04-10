/*
 * brightness_contrast_correct.cpp
 *
 *  Created on: 09 Apr 2020
 *      Author: ahkad
 *
 * How to treat an underexposed image?
 *
 * Ref: https://docs.opencv.org/master/d3/dc1/tutorial_basic_linear_transform.html
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void brightness_contrast_correct(){

	Mat orig_image = imread("./images/train.jpg", IMREAD_UNCHANGED);

	Mat_<Vec3b> new_image = orig_image.clone();

	bool alphaBetaCorrect{false}, gammaCorrect{true};

	if (alphaBetaCorrect) {

		double alpha{1.3}, beta{40};

		/*for(auto& elem:new_image){
			for(int i=0; i<new_image.channels(); ++i)
				elem[i] = saturate_cast<uchar>(alpha*elem[i]+beta);
		}*/

		// Alternative for above for-loop
		new_image.convertTo(new_image, -1, alpha, beta);
	}

	// Gamma correction
	if (gammaCorrect) {
		double gamma{0.4};
		uchar table[256];
		for (int i = 0; i < 256; ++i){
			table[i] = saturate_cast<uchar>(pow(i/255.0, gamma) * 255.0);
		}

		for(auto& elem : new_image) {
			for(int i=0; i<new_image.channels(); ++i)
				elem[i] = table[elem[i]];
		}
	}

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", orig_image);
    namedWindow("Corrected Image", WINDOW_AUTOSIZE);
    imshow("Corrected Image", new_image);

    waitKey(0);

}
