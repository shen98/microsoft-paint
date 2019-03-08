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

    void changeThickness(cv::Mat& m);

private:
    Shapes* shape;
};

#endif