#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "shapes.h"
using namespace std;

enum Buttons
{
    rectangle, line, ellipse, roundedRectangle, triangle,
    polygon, import, undo, redo, choose, f, cancel
};

enum Section
{
    clipboard = 0,
    image = 100,
    tool = 250,
    brush = 320,
    shape = 380
};

class Menu
{
public:
    Menu();
    ~Menu();

    bool initialize(cv::Mat& m, int width);

    void initialMenu(cv::Mat& m, int width);
    int getMouseClick(int mousePosX, int mousePosY);

    void initialShapes(cv::Mat& m);
    void selectShape(cv::Mat& m, int mousePosX, int mousePosY);

    void changeState(int num);

    bool startDrawing();
    void changeDrawingState(bool state);

    bool getSelectedFirst();
    void changeSelectState(bool state);
    int getMenuHeight();

    vector<bool> getButtonState();

private:
    const int g_MenuHeight = 130;
    const int g_MenuOffset = 5;
    const int g_ButtonSize = 40;
    const int g_ButtonNum = 10;
    const int iconHeight = 20;
    const int textSize = 10;
    const int shapeButtonWidth = 20;
    const int shapeButtonHeight = 16;
    const int shapeOffsetWidth = 2;
    const int shapeOffsetHeight = 3;
    bool g_startDrawing = false;
    bool g_drawShape = false;
    bool selectedFirst = false;

    vector<bool> g_buttonState;
    //vector<string> g_buttonName = { "square", "circle", "triangle", "polygon", "import", "undo", "redo", "choose", "f", "cancel" };

    Shapes* shape;
    cv::Scalar defaultShapeColor = CV_RGB(30, 144, 255);
};

#endif