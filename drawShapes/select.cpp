#include "stdafx.h"
#include "select.h"

Select::Select()
{
}

Select::~Select()
{

}

bool Select::initial()
{
    return true;
}

void Select::initialSelect(cv::Mat& m)
{
    int startX = selectStartX + g_MenuOffsetWidth + selectBoxOffsetWidth, startY = iconHeight + g_MenuOffsetHeight + selectBoxOffsetHeight;
    drawDottedRectangle(m, cv::Point(startX, startY), cv::Point(startX + selectBoxWidth, startY + selectBoxHeight), black);
    
}

void Select::selectSelectBox(cv::Mat& m, int mousePosX, int mousePosY)
{
    //if(mousePosX < Section::image || mousePosX > Section::tool || mousePosY < )
}
