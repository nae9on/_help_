/*
 * mat_manip.cpp
 *
 *  Created on: 07 Apr 2020
 *      Author: ahkad
 *
 * Ref: https://docs.opencv.org/master/d6/d6d/tutorial_mat_the_basic_image_container.html
 * Ref: https://docs.opencv.org/master/db/da5/tutorial_how_to_scan_images.html
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void print_head(const Mat& m){
	cout<<"Head info: rows = "<<m.rows<<", cols = "<<m.cols<<", channels = "<<m.channels()<<"\n"
	    <<"depth = "<<m.depth()
		<<", is continuous = "<<m.isContinuous()
		<<", size(H x W) = "<<m.size<<"\n";

	// depth of a matrix element is the type of each individual channel
    //0 - CV_8U - 8-bit unsigned integers ( 0..255 )
    //1 - CV_8S - 8-bit signed integers ( -128..127 )
    //2 - CV_16U - 16-bit unsigned integers ( 0..65535 )
    //3 - CV_16S - 16-bit signed integers ( -32768..32767 )
    //4 - CV_32S - 32-bit signed integers ( -2147483648..2147483647 )
    //5 - CV_32F - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )
    //6 - CV_64F - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )

	// isContinuous() = 1, when entire data is stored as one contiguous block in memory.
	// isContinuous() = 0, when data is non-contiguous in memory (each row is stored
	// as one contiguous memory block at some location in memory).
}

// Example illustrating how to loop over a Mat object
template<typename T>
void loop_over_mat(Mat& I){

    int nRows = I.rows;
    int nCols = I.cols * I.channels();
    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }
    int i,j;
    T* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<T>(i);
        for (j = 0; j < nCols; ++j)
        {
            // do something here
        	p[j] = p[j] + 1;
        }
        std::cout<<"\n";
    }
}

void mat_manip(){

	// rows = 2, columns = 3, channels = 4
	// Note: the type argument is a macro and is an int
    Mat M1(2, 3, CV_8UC(4), Scalar(0,100,200,255));
    print_head(M1);
    cout<<"M1 = \n"<<M1<<"\n\n";

    Mat M2(2, 1, CV_8UC(4), Scalar::all(255));
    cout<<"M2 = \n"<<M2<<"\n\n";

    // Matlab style (what if more than 1 channel is used?)
    Mat E = Mat::eye(4, 4, CV_8UC1);
    cout<<"E = \n"<<E<<"\n\n";

    Mat O = Mat::ones(2, 2, CV_8UC1);
    cout<<"O = \n"<<O<<"\n\n";

    Mat Z = Mat::zeros(3,3, CV_8UC1);
    cout<<"Z = \n"<<Z<<"\n\n";

    // Manually initialize small matrices using std::initializer_list
    // vector will also work
    initializer_list<int> ls{0, -1, 0, -1, 5, -1, 0, -1, 0, -1, 5, -1};
    Mat C = Mat(ls);
    print_head(C);
    cout<<"C = \n"<<C<<"\n\n";

    int cn{2}; // #channels
    int rows{3}; // #rows
    Mat C1 = C.reshape(cn,rows); // shallow copy with new head
    //Mat C1 = C.reshape(cn,rows).t(); // deep copy as it involves re-ordering in memory
    print_head(C1);
    //randu(C, Scalar::all(0), Scalar::all(255)); // test
    cout<<"C1 = \n"<<C1<<"\n\n";

    // Fill matrix with random values
    Mat R;
    R.create(C1.size(),C1.type());
    randu(R, Scalar::all(0), Scalar::all(255));
    cout<<"R = \n"<<R<<"\n\n";
}
