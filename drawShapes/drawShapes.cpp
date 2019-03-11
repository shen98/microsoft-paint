// drawShapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "window.h"

const int g_Width = 1200;
const int g_Height = 600;

int main(int argc, char** argv)
{
    Window* window = new Window();
    if (!window)
    {
        cout << "Could not create window object." << endl;
        return false;
    }

    bool result = window->initialize(g_Height, g_Width);
    if (!result)
    {
        cout << "Could not initialize window." << endl;
        return false;
    }

    return 0;
}