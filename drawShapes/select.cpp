#include "stdafx.h"
#include "select.h"

Select::Select()
{
    shape = NULL;
}

Select::~Select()
{

}

bool Select::initial()
{
    shape = new Shapes();
    if (!shape)
    {
        return false;
    }
}

void Select::initialSelect(cv::Mat& m)
{
    int startX = selectStartX + g_MenuOffsetWidth + selectBoxOffsetWidth, startY = iconHeight + g_MenuOffsetHeight + selectBoxOffsetHeight;
    shape->drawDottedLine(m, cv::Point(startX, startY), cv::Point(startX + selectBoxWidth, startY), black);
    shape->drawDottedLine(m, cv::Point(startX, startY), cv::Point(startX, startY + selectBoxHeight), black);
    shape->drawDottedLine(m, cv::Point(startX + selectBoxWidth, startY), cv::Point(startX + selectBoxWidth, startY + selectBoxHeight), black);
    shape->drawDottedLine(m, cv::Point(startX, startY + selectBoxHeight), cv::Point(startX + selectBoxWidth, startY + selectBoxHeight), black);
}
