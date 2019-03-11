#pragma once
#ifndef _PAINT_H_
#define _PAINT_H_

#include "data.h"
#include <algorithm>

class Paint
{
public:
    Paint();
    ~Paint();

    bool initialize(cv::Mat& m, int width, int height);

    void resize(cv::Mat& m, cv::Point startPos, cv::Point endPos, int thickLevel);
private:

};

#endif // !_PAINT_H_
