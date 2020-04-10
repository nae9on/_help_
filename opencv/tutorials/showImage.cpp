/*
 * showImage.cpp
 *
 *  Created on: 07 Apr 2020
 *      Author: ahkad
 *
 *  Ref: https://docs.opencv.org/master/db/deb/tutorial_display_image.html
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void showImage(void)
{
	string imageName("./images/belgium.jpg");

    Mat orig_image, gray_image; // creates the header part only

    if(orig_image.data==nullptr) cout<<"No data allocated yet"<<endl;

    /*
     * Format of the file is determined by its content (first few bytes).
     * When a color image is read, #channels is automatically set to 3
     * When a grayscale image is read, #channels is automatically set to 1
     *
     */
    orig_image = imread(imageName, IMREAD_UNCHANGED); // allocates memory
    //image = imread(imageName, IMREAD_GRAYSCALE);
    //image = imread(imageName, IMREAD_COLOR); // default

    if (orig_image.data==nullptr)
    {
        printf("No image data \n");
        terminate();
    }

    cvtColor(orig_image, gray_image, COLOR_BGR2GRAY);

    imwrite("./images/gray_belgium.jpg", gray_image); // write image

    // Creates window. It takes two parameters: name of the window
    // and how it should handle the change of the image it contains (from a size point of view)
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Grayscale Image", WINDOW_AUTOSIZE);

    // Attach an image to the OpenCV window
    imshow("Original Image", orig_image);
    imshow("Grayscale Image", gray_image);

    // To display the window until the user presses a key
    waitKey(0); // 0 means wait forever (until a key is pressed)

}
