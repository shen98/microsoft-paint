#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum Buttons
{
    rectangle, circle, triangle,
    polygon, import, c, d, e, f, cancel
};


class Menu
{
public:
    Menu();
    ~Menu();

    bool initialize(cv::Mat& m, int width);

    void initialMenu(cv::Mat& m, int width);
    int getMouseClick(int mousePosX);

    void changeState(int num);

    bool startDrawing();
    void changeDrawingState(bool state);

    bool getSelectedFirst();
    void changeSelectState(bool state);
    int getMenuHeight();

    vector<bool> getButtonState();

private:
    const int g_MenuHeight = 50;
    const int g_MenuOffset = 5;
    const int g_ButtonSize = 40;
    const int g_ButtonNum = 10;
    bool g_startDrawing = false;
    bool g_drawShape = false;
    bool selectedFirst = false;

    vector<bool> g_buttonState;
    vector<string> g_buttonName = { "square", "circle", "triangle", "polygon","import","c","d","e","f","cancel" };

};

#endif