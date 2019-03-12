#pragma once
#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "data.h"
#include "shapes.h"
#include <algorithm>

class Brush
{
public:
    Brush();
    ~Brush();

    bool initialize(cv::Mat& m);

    void drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness = 1);

private:
    Shapes* shapes;
};

#endif // !_BRUSH_H_
