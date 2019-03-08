#include "stdafx.h"
#include "color.h"

Color::Color()
{

}

Color::~Color()
{

}

bool Color::initialize()
{
    shape = new Shapes();
    if (!shape)
    {
        return false;
    }

    return true;
}

void Color::initializeColor(cv::Mat& m)
{
    int startX = 660 + firstColorOffsetWidth + g_MenuOffsetWidth;
    int startY = iconHeight + g_MenuOffsetHeight;
    shape->drawBox(m, cv::Point(startX, startY + firstColorOffsetHeight),
        cv::Point(startX + firstColorWidth, startY + firstColorOffsetHeight + firstColorHeight), black);

    startX += firstColorWidth + firstColorOffsetWidth + secondColorOffsetWidth;
    shape->drawBox(m, cv::Point(startX, startY + secondColorOffsetHeight),
        cv::Point(startX + secondColorWidth, startY + secondColorWidth + secondColorOffsetHeight), black);
}
