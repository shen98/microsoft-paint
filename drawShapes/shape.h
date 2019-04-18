#pragma once
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "data.h"
#include "shapes.h"
#include "effect.h"

#define RECTANGLE 0
#define LINE 1
#define CIRCLE 2

enum ShapeCorners
{
    Left_Up_Corner,
    Right_Bottom_Corner,
    Left_Bottom_Corner,
    Right_Up_Corner,
    Rotate,
    Center
};

struct MyShape
{
    vector<cv::Point> corners;

    int type;
    int thickness;
    cv::Scalar color;
    bool finished = false;              //finished drawing and add to windowMat
    bool completed = false;   
    int distanceFromRotateToCenter;
	double k1, k2;						//k1 - gradient of left up - left bottom && right up - right bottom
										//k2 - gradient of left up - right up && left bottom - right bottom

    MyShape(cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4, cv::Point rotate, int type, cv::Scalar color, int thickness, double k1, double k2,
        bool finished = false, cv::Point p5 = cv::Point(-1, -1), int distanceFromRotateToCenter = -1, bool completed = false)
        : type(type), thickness(thickness), color(color), k1(k1), k2(k2), finished(finished), completed(completed), distanceFromRotateToCenter(distanceFromRotateToCenter)
    {
        vector<cv::Point> vec{ p1, p2, p3, p4, rotate };
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

    void changeShapeCorner(int indexOfShape, int mousePosX, int mousePosY);
    void changeShapeStatus(int indexOfShape, bool finished);
    int getSelectedShapeIndex(cv::Point p);
    void finishDrawingShape(int indexOfShape, bool status = true);
    void changeSelectedShapeColor(int indexOfShape, cv::Scalar color);

    vector<MyShape> getShapes();

    bool selectedRatote();
    void rotateShape(cv::Mat& m, int indexOfShape, int mousePosX, int mousePosY);
    
    void changeSelectedStatus(int status);

private:
    void changeCorner(int indexOfShape, int corner, int mousePosX, int mousePosY);

    double getDistance(cv::Point p1, cv::Point p2);

    void changeLeftUpCorner(int indexOfShape, int mousePosX, int mousePosY);
    void changeRightUpCorner(int indexOfShape, int mousePosX, int mousePosY);
    void changeLeftBottomCorner(int indexOfShape, int mousePosX, int mousePosY);
    void changeRightBottomCorner(int indexOfShape, int mousePosX, int mousePosY);

	void ReCenter(int indexOfShape);

private:
    vector<MyShape> myShapes;

    cv::Scalar defaultShapeColor = CV_RGB(30, 144, 255);
    bool g_selectedShape = false;
    int g_selectedCorner = -1;

    const int unselectedCornerSize = 2;
    const int selectedCornerSize = 3;
};

#endif