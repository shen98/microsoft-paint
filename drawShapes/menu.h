#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

#include "shapes.h"
#include "thickness.h"
#include "color.h"
#include "select.h"
#include "brush.h"
#include "shape.h"
using namespace std;

enum Buttons
{
    selectBox, selectBrush, normalBrush, rectangle, line, ellipse, roundedRectangle, triangle,
    polygon, thickness, colorOne, colorTwo, import, undo, redo, choose, cancel
};

class Menu
{
public:
    Menu();
    ~Menu();

    bool initialize(cv::Mat& m, int width);

    void initialMenu(cv::Mat& m, int width);                    //Initially draw the menu

    void drawShapes(cv::Mat& m);

    void drawTempShape(int index, cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness, bool finished = false);
    cv::Point checkMousePosOnCorner(cv::Mat& m, int mousePosX, int mousePosY);
    void changeShapeCorner(int indexOfShape, int mousePosX, int mousePosY);
    void changeShapeStatus(int indexOfShape, bool finished);
    int getSelectedShapeIndex(cv::Point p);

    int getMouseClick(int mousePosX, int mousePosY);

    void selectShape(cv::Mat& m, int mousePosX, int mousePosY);
    void selectedShape(cv::Mat& m, int index);

    void selectThickness(cv::Mat& m, int mousePosX, int mousePosY, int selected);
    int changeThickness(int mousePosX, int mousePosY);

    void selectColor(cv::Mat& m, int mousePosX, int mousePosY);
    cv::Scalar changeColor(cv::Mat& m, int mousePosX, int mousePosY);
    cv::Scalar changeDisplayColorNum(cv::Mat& m, int mousePosX, int mousePosY);

    void selectBrush(cv::Mat& m, int mousePosX, int mousePosY);
    int changeBrush(cv::Mat& m, int mousePosX, int mousePosY);

    void changeState(int num);

    bool startDrawing();
    void changeDrawingState(bool state);

    bool getSelectedFirst();
    void changeSelectState(bool state);

    void drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness = 1);

    bool getSelectThickness();
    void changeSelectThickness(bool state);

    bool getSelectBrush();
    void changeSelectBrush(bool state);

    int getMenuHeight();

    vector<bool> getButtonState();

private:
    bool g_startDrawing = false;
    bool g_drawShape = false;
    bool selectedFirst = false;
    bool g_selectThickness = false;
    bool g_selectBrush = false;

    int thickLevel = 1;

    vector<bool> g_buttonState;


    Shapes* shapes;
    Thickness* thickness;
    Color* color;
    Select* select;
    Brush* brush;
    Shape* shape;
};

#endif