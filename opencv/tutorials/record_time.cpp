/*
 * record_time.cpp
 *
 *  Created on: 08 Apr 2020
 *      Author: ahkad
 */

#include <opencv2/opencv.hpp>

void record_time(){
    double tic = (double)cv::getTickCount();
    cv::Mat image = cv::imread("./images/belgium.jpg", cv::IMREAD_UNCHANGED);
    double toc = (double)cv::getTickCount();
    std::cout<<"Time passed in seconds: "<<(toc - tic)/cv::getTickFrequency()<<"\n";
}


