#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "shapes.h"
#include "thickness.h"
using namespace std;

enum Buttons
{
    rectangle, line, ellipse, roundedRectangle, triangle,
    polygon, thickness, import, undo, redo, choose, f, cancel
};

enum Section
{
    clipboard = 0,
    image = 100,
    tool = 250,
    brush = 320,
    shape = 380,
    thick = 600,
    colorOne = 660
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



    void initialColorOne(cv::Mat& m);

    void initialColorTwo(cv::Mat& m);

    void changeState(int num);

    bool startDrawing();
    void changeDrawingState(bool state);

    bool getSelectedFirst();
    void changeSelectState(bool state);
    void changeSelectThicknessState(bool state);
    int getMenuHeight();

    vector<bool> getButtonState();

private:
    bool g_startDrawing = false;
    bool g_drawShape = false;
    bool selectedFirst = false;
    bool g_selectedShape = false;
    bool g_selectThickness = false;

    vector<bool> g_buttonState;
    //vector<string> g_buttonName = { "square", "circle", "triangle", "polygon", "import" "undo", "redo", "choose", "f", "cancel" };

    Shapes* shape;
    Thickness* thickness;
    cv::Scalar defaultShapeColor = CV_RGB(30, 144, 255);
};

#endif