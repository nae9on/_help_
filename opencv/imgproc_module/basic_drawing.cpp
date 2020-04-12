/*
 * basic_drawing.cpp
 *
 *  Created on: 11 Apr 2020
 *      Author: ahkad
 *
 * Ref: https://docs.opencv.org/master/d3/d96/tutorial_basic_geometric_drawing.html
 */

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define w 400

using namespace cv;

static Scalar randomColor(RNG& rng)
{
  return Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
}

void MyEllipse(Mat img, double angle, RNG& rng)
{
  int thickness = 2;
  int lineType = LINE_8;

  ellipse(img,
       Point(w/2, w/2),
       Size(w/4, w/16),
       angle,
       0,
       360,
       randomColor(rng),//Scalar(255, 0, 0),
       thickness,
       lineType);
}

void MyFilledCircle(Mat img, Point center, RNG& rng)
{
  circle(img,
      center,
      w/32,
      randomColor(rng),//Scalar(0, 0, 255),
      FILLED,
      LINE_8);
}

void MyLine( Mat img, Point start, Point end, RNG& rng)
{
  int thickness = 2;
  int lineType = LINE_8;

  line( img,
    start,
    end,
    randomColor(rng),//Scalar(0, 255, 0),
    thickness,
    lineType);
}

void basic_drawing(){

  String name("Basic drawing");

  uint64 state = static_cast<uint64>(time(0));
  RNG rng(state);

  Mat image = Mat::zeros(w, w, CV_8UC3);

  MyEllipse(image, 90, rng);

  MyFilledCircle(image, Point(w/2, w/2), rng);

  rectangle(image,
         Point(0, 0.9*w),
         Point(w, w),
         randomColor(rng),//Scalar(0, 255, 255),
         FILLED,
         8);

  MyLine(image, Point(0, 0.8*w), Point(w, 0.8*w), rng);

  imshow(name, image );

  waitKey( 0 );
}
