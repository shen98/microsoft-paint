#pragma once

#ifndef _COLOR_H_
#define _COLOR_H_

#include "data.h"
#include "shapes.h"
class Color
{
public:
    Color();
    ~Color();

    bool initialize();

    void initializeColor(cv::Mat& m);

private:
    const int colorOffset = 2;
    const int firstColorOffsetWidth = 5;
    const int firstColorOffsetHeight = 3;
    const int secondColorOffsetWidth = 10;
    const int secondColorOffsetHeight = 6;
    const int firstColorWidth = 30;
    const int firstColorHeight = 30;
    const int secondColorWidth = 20;
    const int secondColorHeight = 20;

    cv::Scalar black = CV_RGB(0, 0, 0);
    Shapes* shape;
};

#endif // !_COLOR_H_
