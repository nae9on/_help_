/*
 * parallel_image_manip.cpp
 *
 *  Created on: 10 Apr 2020
 *      Author: ahkad
 *
 * Ref: https://docs.opencv.org/master/d7/dff/tutorial_how_to_use_OpenCV_parallel_for_.html
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// get pixel values i and j
uchar mandelbrot(int i, int j, Mat &img)
{
	// Rescale pixel values to Mandelbrot domain
    float x1 = -2.1f, x2 = 0.6f;
    float y1 = -1.2f, y2 = 1.2f;
    float scaleX = img.cols / (x2 - x1);
    float scaleY = img.rows / (y2 - y1);

    // Convert the pixel index coordinate to a 2D [row, col] coordinate
    float x0 = j / scaleX + x1;
    float y0 = i / scaleY + y1;

    complex<float> z0(x0, y0);
    complex<float> z{z0};

    const int maxIter{500};  int value{maxIter};

    for (int t=0; t<maxIter; ++t)
    {
        if (z.real()*z.real() + z.imag()*z.imag() > 4.0f) {value = t; break;}
        z = z*z + z0;
    }

    if(value==maxIter)
	{
		return 0;
	}

    return cvRound(sqrt(value/(float) maxIter)*255);
}

void sequentialLoop(Mat &img)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            uchar value = mandelbrot(i,j,img);
            img.ptr<uchar>(i)[j] = value;
        }
    }
}

class functorClass : public ParallelLoopBody
{
public:
    functorClass (Mat &img): m_img(img){}

    // The range in the operator () represents the subset of pixels that will be
    // treated by an individual thread.
    // This splitting is done automatically to distribute equally the computation load.
    // Range represents the total number of operations to be executed, so the
    // total number of pixels in the image
    virtual void operator()(const Range& range) const CV_OVERRIDE
    {
        for (int r = range.start; r < range.end; r++)
        {
            int i = r / m_img.cols;
            int j = r % m_img.cols;
            uchar value = mandelbrot(i,j,m_img);
            m_img.ptr<uchar>(i)[j] = value;
        }
    }

private:
    Mat &m_img;
};

void parallel_image_manip(){

	Mat input(4800, 5400, CV_8UC1);
	Mat input_seq = input.clone();
	constexpr int numThreads{6};

	double tic1 = (double)cv::getTickCount();

	#ifdef CV_CXX11
	cv::setNumThreads(numThreads);
	parallel_for_(Range(0, input.rows*input.cols), [&](const Range& range){
		for (int r = range.start; r < range.end; r++)
		{
			int i = r / input.cols;
			int j = r % input.cols;
			uchar value = mandelbrot(i,j,input);
			input.ptr<uchar>(i)[j] = value;
		}
	});
	#else
	functorClass obj(input);
	cv::setNumThreads(numThreads);
	parallel_for_(Range(0, input.rows*input.cols), obj);
	#endif

    double toc1 = (double)cv::getTickCount();
    double dt1 = (toc1 - tic1)/cv::getTickFrequency();
    std::cout<<"Time passed in seconds (parallel code): "<<dt1<<endl;

	double tic2 = (double)cv::getTickCount();
	sequentialLoop(input_seq);
    double toc2 = (double)cv::getTickCount();
    double dt2 = (toc2 - tic2)/cv::getTickFrequency();
    std::cout<<"Time passed in seconds (sequential code): "<<dt2<<endl;
    cout<<"numThreads = "<<numThreads<<", Speedup = "<<dt2/dt1<<endl;

    imwrite("./images/Mandelbrot_parallel.png", input);
    imwrite("./images/Mandelbrot_sequential.png", input_seq);

    waitKey(0);

}
