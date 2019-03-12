#include "stdafx.h"
#include "brush.h"

Brush::Brush()
{

}

Brush::~Brush()
{

}

bool Brush::initialize(cv::Mat& m)
{
    shapes = new Shapes();
    if (!shapes)
    {
        return false;
    }

    return true;
}

void Brush::drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness)
{
    startPos = cv::Point(startPos.x - windowOffsetWidth, startPos.y - g_MenuHeight - windowOffsetHeight);
    endPos = cv::Point(endPos.x - windowOffsetWidth, endPos.y - g_MenuHeight - windowOffsetHeight);
    
    shapes->drawLine(m, startPos, endPos, color, thickness);
}
