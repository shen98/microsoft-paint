#pragma once
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "data.h"
#include "shapes.h"

class Shape
{
public:
    Shape();
    ~Shape();

    bool initialShape(cv::Mat& m);

    void selectShape(cv::Mat& m, int mousePosX, int mousePosY);

    void selectedShape(cv::Mat& m, int index);

private:
    cv::Scalar defaultShapeColor = CV_RGB(30, 144, 255);
    bool g_selectedShape = false;

    Shapes* shapes;

};

#endif