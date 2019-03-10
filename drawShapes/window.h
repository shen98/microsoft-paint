#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <opencv2/highgui/highgui_c.h>

#include "menu.h"
#include "shapes.h"
#include "history.h"
#include "image.h"

class Window
{
public:
    Window(int width, int height);
    ~Window();

    bool initialize();

    void onMouse(int event, int x, int y, int flags, void* param);
    bool initialWindow();
    void initPoints();
    wstring selectFile();

    void addToHistory(cv::Mat m);

private:
    int g_Width;
    int g_Height;
    cv::Point startPos, endPos, initPos;
    cv::Mat windowMat, temp;
    int mouseX, mouseY;

    int g_prevSelectedShape = -1;

    cv::Scalar colorOne, colorTwo, drawingColor;

    int thichLevel = 1;

    Menu* menu;
    Shapes* shapes;
    History* history;
    Image* image;
};

#endif