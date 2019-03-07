// drawShapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "window.h"

const int g_Width = 1200;
const int g_Height = 600;

int main(int argc, char** argv)
{
    Window* w = new Window(g_Height, g_Width);

    w->initialize();

    return 0;
}