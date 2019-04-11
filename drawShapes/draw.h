#pragma once
#ifndef _DRAW_H_
#define _DRAW_H_

#include "shape.h"
#include "shapes.h"
#include "brush.h"
class Draw
{
public:
    Draw();
    ~Draw();

    bool initialize();

    void draw(cv::Mat& m, vector<MyShape> myShapes, vector<MyBrush> myBrushes);

private:
    void drawShapes(cv::Mat& m, vector<MyShape> myShapes);
    void drawBrushes(cv::Mat& m, vector<MyBrush> myBrushes);
private:
    cv::Scalar defaultShapeColor = CV_RGB(30, 144, 255);

    const int unselectedCornerSize = 2;
    const int selectedCornerSize = 3;
};

#endif // !_DRAW_H_
