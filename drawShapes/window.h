#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <tchar.h>
#include <codecvt>
#include <opencv2/highgui/highgui_c.h>

#include "menu.h"
#include "shapes.h"
#include "history.h"

const double initialImageSize = 100.0;

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
    bool loadImage(wstring fileName, cv::Mat& m);
    void reScale(cv::Mat& img, bool fixedRatio, double width = initialImageSize, double height = initialImageSize);
    void addToHistory(cv::Mat m);
private:
    int g_Width;
    int g_Height;
    cv::Point startPos, endPos, initPos;
    cv::Mat windowMat, temp;

    Menu* menu;
    Shapes* shapes;
    History* history;
};

#endif