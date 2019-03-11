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

    return true;
}

void Select::initialSelect(cv::Mat& m)
{
    int startX = selectStartX + g_MenuOffsetWidth + selectBoxOffsetWidth, startY = iconHeight + g_MenuOffsetHeight + selectBoxOffsetHeight;
    shape->drawDottedRectangle(m, cv::Point(startX, startY), cv::Point(startX + selectBoxWidth, startY + selectBoxHeight), black);
    
}

void Select::selectSelectBox(cv::Mat& m, int mousePosX, int mousePosY)
{
    //if(mousePosX < Section::image || mousePosX > Section::tool || mousePosY < )
}
