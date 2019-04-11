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
	return true;
}	

void Thickness::initialThickness(cv::Mat& m)
{
    int height = 0;
    for (int i = 0; i < 5; ++i)
    {
        drawBox(m, cv::Point(600 + g_MenuOffsetWidth, iconHeight + g_MenuOffsetHeight + shapeOffsetHeight * i + (i + 1) * 1 + height),
            cv::Point(660 - g_MenuOffsetWidth, iconHeight + g_MenuOffsetHeight + shapeOffsetHeight * i + (2 * i + 2) * 1 + height), CV_RGB(0, 0, 0), -1);
        height += i + 1;
    }
}

void Thickness::selectThickness(cv::Mat& m, int mousePosX, int mousePosY, int selected)
{
    int startX = Section::thick + g_MenuOffsetWidth, startY = iconHeight + g_MenuOffsetHeight + thicknessHeight;
    drawBox(m, cv::Point(startX, startY), cv::Point(startX + popUpWidth, startY + popUpHeight), CV_RGB(255,255,255), -1);
    drawBox(m, cv::Point(startX, startY), cv::Point(startX + popUpWidth, startY + popUpHeight), popUpEdgeColor);

    for (int i = 0; i < 4; ++i)
    {
        drawBox(m, cv::Point(startX + g_MenuOffsetWidth, startY + i * 50 + (25 - (i + 1))), cv::Point(startX + popUpWidth - g_MenuOffsetWidth, startY + i * 50 + 25 + i - 1), CV_RGB(0, 0, 0), -1);
    }

    if (selected != -1)
    {
        cv::Mat temp;
        m.copyTo(temp);

        cv::rectangle(temp, cv::Rect(cv::Point(startX + popUpOffsetWidth, startY + popUpOffsetHeight + selected * 50),
            cv::Point(startX + popUpWidth - popUpOffsetWidth, startY + (selected + 1) * 50 - popUpOffsetHeight)), CV_RGB(0, 191, 255), -1);

        double alpha = 0.3;
        cv::addWeighted(temp, alpha, m, 1.0 - alpha, 0.0, m);
    }

    if (mousePosX < startX || mousePosX > startX + popUpWidth || mousePosY < startY || mousePosY > startY + popUpHeight) return;

    int index = (mousePosY - startY) / 50;
    drawBox(m, cv::Point(startX + popUpOffsetWidth, startY + index * 50 + popUpOffsetHeight),
        cv::Point(startX + popUpWidth - popUpOffsetWidth, startY + (index + 1) * 50 - popUpOffsetHeight), popUpEdgeColor);
}

int Thickness::changeThickness(int mousePosX, int mousePosY)
{
    int startX = Section::thick + g_MenuOffsetWidth, startY = iconHeight + g_MenuOffsetHeight + thicknessHeight;
    if (mousePosX < startX || mousePosX > startX + popUpWidth || mousePosY < startY || mousePosY > startY + popUpHeight) return - 1;
    cout << (mousePosY - startY) / 50;

    return (mousePosY - startY) / 50;
}
