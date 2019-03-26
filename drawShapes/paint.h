#pragma once
#ifndef _PAINT_H_
#define _PAINT_H_

#include "draw.h"
#include "shape.h"
#include "brush.h"
#include <algorithm>

class Paint
{
public:
    Paint();
    ~Paint();

    bool initialize(cv::Mat& m, int width, int height);

    void resize(cv::Mat& m, cv::Point startPos, cv::Point endPos, int thickLevel);

    void paint(cv::Mat& m);

    void drawTempShape(int index, cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness, bool finished = false);
    cv::Point checkMousePosOnCorner(cv::Mat& m, int mousePosX, int mousePosY);
    void changeShapeCorner(int indexOfShape, int mousePosX, int mousePosY);
    void changeShapeStatus(int indexOfShape, bool finished);
    int getSelectedShapeIndex(cv::Point p);
    void finishDrawingShape(int indexOfShape, bool status = false);
    void selectShape(cv::Mat& m, int mousePosX, int mousePosY);
    void selectedShape(cv::Mat& m, int index);
    void changeSelectedShapeColor(int indexOfShape, cv::Scalar color);

    void drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness = 1);

private:
    Draw* draw;
    Shape* shape;
    Brush* brush;
};

#endif // !_PAINT_H_
