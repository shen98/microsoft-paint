#pragma once

#ifndef _THICKNESS_H_
#define _THICKNESS_H_

#include <opencv2/opencv.hpp>
#include "shapes.h"
#include "data.h"

class Thickness
{
public:
    Thickness();
    ~Thickness();

    bool initialize();

    void initialThickness(cv::Mat& m);

    void selectThickness(cv::Mat& m, int mousePosX, int mousePosY, int selected = -1);
    int changeThickness(int mousePosX, int mousePosY);
private:
    const int thicknessHeight = 60;
    const int popUpHeight = 200;
    const int popUpWidth = 200;
    const int popUpOffsetWidth = 2;
    const int popUpOffsetHeight = 3;
    cv::Scalar popUpEdgeColor = CV_RGB(135, 206, 235);
    cv::Scalar popUpFillColor = CV_RGB(230, 230, 255);

    Shapes* shape;
};

#endif