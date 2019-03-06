// drawShapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "window.h"

const int g_Width = 500;
const int g_Height = 500;

int main(int argc, char** argv)
{
    Window* w = new Window(g_Width, g_Height);

    w->initialize();

    return 0;
}