#include "stdafx.h"
#include "thickness.h"

Thickness::Thickness()
{
    
}

Thickness::~Thickness()
{

}

bool Thickness::initialize()
{
    shape = new Shapes();
    if (!shape)
    {
        return false;
    }
}

void Thickness::initialThickness(cv::Mat& m)
{
    int height = 0;
    for (int i = 0; i < 5; ++i)
    {
        shape->drawBox(m, cv::Point(600 + g_MenuOffsetWidth, iconHeight + g_MenuOffsetHeight + shapeOffsetHeight * i + (i + 1) * 1 + height),
            cv::Point(660 - g_MenuOffsetWidth, iconHeight + g_MenuOffsetHeight + shapeOffsetHeight * i + (2 * i + 2) * 1 + height), CV_RGB(0, 0, 0), -1);
        height += i + 1;
    }
}

void Thickness::changeThickness(cv::Mat& m)
{
    //cv::rectangle(m, cv::Point(6)
}