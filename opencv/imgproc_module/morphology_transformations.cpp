/*
 * morphology_transformations.cpp
 *
 *  Created on: 12 Apr 2020
 *      Author: ahkad
 */

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct datastruct{

    Mat src, target;
    string winName;
    int erosion_elem;
    int erosion_size;
    datastruct(Mat m, string wN, int erosion_elem_, int erosion_size_){
        src = m;
        target.create(src.size(),src.type());
        winName = wN;
        erosion_elem = erosion_elem_;
        erosion_size = erosion_size_;
    }
};

void Erosion(int, void* data)
{
    datastruct* ptr = static_cast<datastruct*>(data);

    int erosion_type{0};

    switch(ptr->erosion_elem){
    case 0: erosion_type = MORPH_RECT; break;
    case 1: erosion_type = MORPH_CROSS; break;
    case 2: erosion_type = MORPH_ELLIPSE; break;
    default: std::terminate();
    }

    Mat element = getStructuringElement(erosion_type,
            Size(2*ptr->erosion_size+1, 2*ptr->erosion_size+1));

    erode(ptr->src, ptr->target, element);
    //dilate(ptr->src, ptr->target, element);

    imshow(ptr->winName, ptr->target);
}

void morphology_transformations()
{
    int erosion_elem{0}, erosion_size{0};
    int const max_elem{2}, max_kernel_size{10};

    string winName{"Corrected Image"};
    namedWindow(winName, WINDOW_AUTOSIZE);

    datastruct data{imread("./images/cheetah.jpg", IMREAD_UNCHANGED),
        winName, erosion_elem, erosion_size};

    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", winName,
          &(data.erosion_elem), max_elem, Erosion, &data);
    createTrackbar("Kernel size:\n 2n +1", winName,
          &(data.erosion_size), max_kernel_size, Erosion, &data);

    // Initialize
    Erosion(0, &data);

    waitKey(0);
}
