#pragma once
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "data.h"
#include "shapes.h"

#define RECTANGLE 0
#define LINE 1
#define CIRCLE 2

struct MyShape
{
    vector<cv::Point> corners;

    int type;
    int thickness;
    cv::Scalar color;
    bool finished = false;

    MyShape(cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4, int type, cv::Scalar color, int thickness, bool finished = false, cv::Point p5 = cv::Point(-1, -1))
        : type(type), thickness(thickness), color(color), finished(finished)
    {
        vector<cv::Point> vec{ p1, p2, p3, p4 };
        if (p5 != cv::Point(-1, -1)) vec.push_back(p5);
        corners = vec;
    }
};

class Shape
{
public:
    Shape();
    ~Shape();

    bool initialShape(cv::Mat& m);

    void selectShape(cv::Mat& m, int mousePosX, int mousePosY);

    void selectedShape(cv::Mat& m, int index);

    void drawTempRect(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished = false);
    void drawTempLine(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished = false);
    void drawTempCircle(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished = false);
    void drawTempTriangle(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished = false);

    cv::Point checkMousePosOnCorner(cv::Mat& m, int mousePosX, int mousePosY);

    void selectedCorner(cv::Mat& m, int mousePosX, int mousePosY);

    void drawAllShapes(cv::Mat& m);
    void changeShapeCorner(int indexOfShape, int mousePosX, int mousePosY);
    void changeShapeStatus(int indexOfShape, bool finished);
    int getSelectedShapeIndex(cv::Point p);
private:
    void changeCorner(int indexOfShape, int corner, int mousePosX, int mousePosY);
private:
    vector<MyShape> myShapes;

    cv::Scalar defaultShapeColor = CV_RGB(30, 144, 255);
    bool g_selectedShape = false;
    int g_selectedCorner = -1;

    const int unselectedCornerSize = 2;
    const int selectedCornerSize = 3;

    Shapes* shapes;
};

#endif