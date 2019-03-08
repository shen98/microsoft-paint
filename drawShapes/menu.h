#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "shapes.h"
#include "thickness.h"
#include "color.h"
using namespace std;

enum Buttons
{
    rectangle, line, ellipse, roundedRectangle, triangle,
    polygon, thickness, colorOne, colorTwo, import, undo, redo, choose, cancel
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
    void selectedShape(cv::Mat& m, int index);

    void selectThickness(cv::Mat& m, int mousePosX, int mousePosY, int selected);
    int changeThickness(int mousePosX, int mousePosY);

    void changeState(int num);

    bool startDrawing();
    void changeDrawingState(bool state);

    bool getSelectedFirst();
    void changeSelectState(bool state);

    bool getSelectThickness();
    void changeSelectThickness(bool state);
    int getMenuHeight();

    vector<bool> getButtonState();

private:
    bool g_startDrawing = false;
    bool g_drawShape = false;
    bool selectedFirst = false;
    bool g_selectedShape = false;
    bool g_selectThickness = false;

    int thickLevel = 1;

    vector<bool> g_buttonState;
    //vector<string> g_buttonName = { "square", "circle", "triangle", "polygon", "import" "undo", "redo", "choose", "f", "cancel" };

    Shapes* shape;
    cv::Scalar defaultShapeColor = CV_RGB(30, 144, 255);

    Thickness* thickness;
    Color* color;
};

#endif