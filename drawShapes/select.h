#pragma once
#ifndef _SELECT_H_
#define _SELECT_H_

#include <opencv2/opencv.hpp>
#include "data.h"
#include "shapes.h"

class Select
{
public:
    Select();
    ~Select();

    bool initial();

    void initialSelect(cv::Mat& m);

    void selectSelectBox(cv::Mat& m, int mousePosX, int mousePosY);
private:
    const int selectStartX = 100;
    const int selectBoxWidth = 50;
    const int selectBoxHeight = 30;
    const int selectBoxOffsetWidth = 6;
    const int selectBoxOffsetHeight = 10;

    cv::Scalar black = CV_RGB(0, 0, 0);

    Shapes* shape;
};

#endif