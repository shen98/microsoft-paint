#pragma once
#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "data.h"
#include "shapes.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

const int NORMAL = 0;
const int SQUARE = 1;
const int SPILL = 2;

struct MyBrush
{
    int type;
    cv::Point startPos;
    cv::Point endPos;
    cv::Scalar color;
    int thickness = 1;

    MyBrush(cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness)
        : startPos(startPos), endPos(endPos), type(type), color(color), thickness(thickness)
    {}
};

class Brush
{
public:
    Brush();
    ~Brush();

    bool initialize(cv::Mat& m);

    bool initializeBrush(cv::Mat& m);

    void drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness = 1);

    void selectBrush(cv::Mat& m, int mousePosX, int mousePosY);

    void selectBrushType(cv::Mat& m, int mousePosX, int mousePosY);
    int changeBrushType(cv::Mat& m, int mousePosX, int mousePosY);

    vector<MyBrush> getBrushes();
private:
    void updateBrushType(cv::Mat& m, int type);

    vector<MyBrush> myBrushes;

    const int brushOffsetHeight = 8;
    const int brushOffsetWidth = 10;
    const int brushStartX = 250;
    const int brushStartY = iconHeight + brushOffsetHeight;

    const int brushTextHeight = 10;
    const int brushRectWidth = 50;
    const int brushRectHeight = 20;
    const int brushTextOffsetWidth = 5;
    const int brushTextOffsetHeight = 3;

    int brushType = 0;

    std::vector<std::string> brushName = { "Normal", "Square", "Spill" };
    const int brushPopUpHeight = (int)brushName.size() * brushRectHeight;
    const int brushPopUpWidth = 50;

    cv::Scalar popUpEdgeColor = CV_RGB(135, 206, 235);
};

#endif // !_BRUSH_H_
