#pragma once

#ifndef _COLOR_H_
#define _COLOR_H_

#include "data.h"
#include "shapes.h"
#include <vector>

class Color
{
public:
    Color();
    ~Color();

    bool initialize();

    void initializeColor(cv::Mat& m);
    void initialDisplayColor(cv::Mat& m);

    void selectColor(cv::Mat& m, int mousePosX, int mousePosY);

    void selectDisplayColor(cv::Mat& m, int mousePosX, int mousePosY);
    cv::Scalar selectedDisplayColor(cv::Mat& m);

    bool changeDisplayColorNum(int mousePosX, int mousePosY);               //select color one or color two

    cv::Scalar changeDrawingColor(int mousePosX, int mousePosY);           //change drawing color

    void changeDisplayColor(cv::Mat& m, cv::Scalar color);
private:
    const int colorOffset = 2;
    const int firstColorOffsetWidth = 5;
    const int firstColorOffsetHeight = 3;
    const int secondColorOffsetWidth = 10;
    const int secondColorOffsetHeight = 6;
    const int firstColorWidth = 30;
    const int firstColorHeight = 30;
    const int ColorDisplayHeight = 80;
    const int secondColorWidth = 20;
    const int secondColorHeight = 20;
    const int numOfColorRow = 3;
    const int numOfColorCol = 10;
    const int colorBlockSize = 18;
    const int colorBlockOffset = 4;
    const int colorStartX = 660;
    const int initStartX = colorStartX + g_MenuOffsetWidth;
    const int initStartY = iconHeight + g_MenuOffsetHeight;

    vector<cv::Scalar> colorBlockColor = { CV_RGB(0,0,0), CV_RGB(128,128,128), CV_RGB(139,0,0),
        CV_RGB(255,0,0), CV_RGB(255,69,0), CV_RGB(255,255,0), CV_RGB(0,128,0), CV_RGB(173,216,230), CV_RGB(30,144,255) };

    int selectedColorNum = 1;

    cv::Scalar black = CV_RGB(0, 0, 0);
    cv::Scalar white = CV_RGB(255,255,255);
    cv::Scalar colorOne, colorTwo;
};

#endif // !_COLOR_H_
