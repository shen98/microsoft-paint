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

    bool initializeBrush(cv::Mat& m);

    void drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness = 1);

    void selectBrush(cv::Mat& m, int mousePosX, int mousePosY);

    void selectBrushType(cv::Mat& m, int mousePosX, int mousePosY);
    int changeBrushType(int mousePosX, int mousePosY);
private:
    Shapes* shapes;
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

    std::vector<std::string> brushName = { "Normal", "Square" };
    const int brushPopUpHeight = brushName.size() * brushRectHeight;
    const int brushPopUpWidth = 50;

    cv::Scalar popUpEdgeColor = CV_RGB(135, 206, 235);
};

#endif // !_BRUSH_H_
