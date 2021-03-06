#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <opencv2/highgui/highgui_c.h>

#include "menu.h"
#include "shapes.h"
#include "history.h"
#include "image.h"
#include "paint.h"

class Window
{
public:
    Window();
    ~Window();

    bool initialize(int height, int width);
    void onMouse(int event, int x, int y, int flags, void* param);

private:
    bool initialWindow();
    void initPoints();
	int wakeUpWindow(int key);
    wstring selectFile();

private:
    cv::Point startPos, endPos, initPos;
    cv::Mat windowMat, temp, menuMat, backgroundMat;
    int mouseX, mouseY;

    int g_prevSelectedShape = -1;
    cv::Scalar drawingColor;
    int thichLevel = 1;
    int brushType = -1;

    bool selectedSelectBox = false;
    bool drawWithBrush = false;
    bool startDrawWithBrush = false;
    bool selectedShapes = false;

	bool rightClicked = false;					//Display right click box
	bool firstTimeRightClicked = false;			//Position of right click box

	bool wakeUp = false;						//Check if there is event happened to wake up window

    bool changeShapeCorner = false;
    int changeShape = -1;

    Menu* menu;
    History* history;
    Image* image;
    Paint* paint;
};

#endif