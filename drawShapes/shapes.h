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

    void drawBox(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawCircle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawRegularTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawRightTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawLine(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawPolygon(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawEllipse(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawRoundedRectangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void drawDottedLine(cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
    void changeColor(cv::Scalar color);
private:
};

#endif;
