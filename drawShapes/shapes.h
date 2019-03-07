#pragma once
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;

class Shapes
{
public:
    Shapes();
    ~Shapes();

    bool initialShapes();

    void drawBox(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void drawCircle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void drawRegularTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void drawRightTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void drawLine(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void drawPolygon(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void drawEllipse(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void drawRoundedRectangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color);
    void changeColor(cv::Scalar color);
private:
    int thickness;
};

#endif;
