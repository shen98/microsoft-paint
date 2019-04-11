#include "stdafx.h"
#include "color.h"

Color::Color()
{
    colorOne = black;
    colorTwo = white;
}

Color::~Color()
{

}

bool Color::initialize()
{
    return true;
}

void Color::initializeColor(cv::Mat& m)
{
    initialDisplayColor(m);
    int startX = colorStartX + firstColorOffsetWidth + g_MenuOffsetWidth;
    int startY = iconHeight + g_MenuOffsetHeight;
   
    startX += firstColorWidth + firstColorOffsetWidth + secondColorOffsetWidth;
    startX += secondColorWidth + secondColorOffsetWidth + colorOffset;
    for (int i = 0; i < numOfColorRow; i++)
    {
        for (int j = 0; j < numOfColorCol; j++)
        {
            drawBox(m, cv::Point(startX + j * colorBlockSize + colorBlockOffset * j, startY + i * colorBlockSize + i * colorBlockOffset),
                cv::Point(startX + (j + 1) * colorBlockSize + colorBlockOffset * j, startY + (i + 1) * colorBlockSize + i * colorBlockOffset), black);
            cv::Scalar colorTemp;
            if (i * numOfColorCol + j >= colorBlockColor.size()) colorTemp = CV_RGB(255, 255, 255);
            else colorTemp = colorBlockColor[i * numOfColorCol + j];
            drawBox(m, cv::Point(startX + j * colorBlockSize + colorBlockOffset * j + colorOffset, startY + i * colorBlockSize + i * colorBlockOffset + colorOffset),
                cv::Point(startX + (j + 1) * colorBlockSize + colorBlockOffset * j - colorOffset, startY + (i + 1) * colorBlockSize + i * colorBlockOffset - colorOffset), colorTemp, -1);

        }
    }
}

void Color::initialDisplayColor(cv::Mat& m)
{
    int startX = colorStartX + firstColorOffsetWidth + g_MenuOffsetWidth;
    int startY = iconHeight + g_MenuOffsetHeight;

    drawBox(m, cv::Point(startX - firstColorOffsetWidth - 1, startY - 1),
        cv::Point(startX + firstColorOffsetWidth * 2 + firstColorWidth + secondColorOffsetWidth + secondColorWidth + colorOffset + 1, startY + ColorDisplayHeight + 1), defaultMenuColor, -1);
    drawBox(m, cv::Point(startX, startY + firstColorOffsetHeight),
        cv::Point(startX + firstColorWidth, startY + firstColorOffsetHeight + firstColorHeight), black);

    drawBox(m, cv::Point(startX + colorOffset, startY + firstColorOffsetHeight + colorOffset),
        cv::Point(startX + firstColorWidth - colorOffset, startY + firstColorOffsetHeight + firstColorHeight - colorOffset), colorOne, -1);

    startX += firstColorWidth + firstColorOffsetWidth + secondColorOffsetWidth;
    drawBox(m, cv::Point(startX, startY + secondColorOffsetHeight),
        cv::Point(startX + secondColorWidth, startY + secondColorWidth + secondColorOffsetHeight), black);

    drawBox(m, cv::Point(startX + colorOffset, startY + secondColorOffsetHeight + colorOffset),
        cv::Point(startX + secondColorWidth - colorOffset, startY + secondColorWidth + secondColorOffsetHeight - colorOffset), colorTwo, -1);
}

void Color::selectColor(cv::Mat& m, int mousePosX, int mousePosY)
{
    int startX = colorStartX + g_MenuOffsetWidth + firstColorOffsetWidth * 2 + firstColorWidth + secondColorWidth + secondColorOffsetWidth * 2 - colorBlockOffset + colorOffset;
    int startY = iconHeight + g_MenuOffsetHeight - colorBlockOffset;

    if (mousePosX < startX || mousePosX > startX + (colorBlockOffset + colorBlockSize) * numOfColorCol ||
        mousePosY < startY || mousePosY > startY + (colorBlockSize + colorOffset) * numOfColorRow) return;

    int index = (mousePosX - startX) / (colorBlockSize + colorBlockOffset) + (mousePosY - startY) / (colorBlockSize + colorBlockOffset) * numOfColorCol;

    drawBox(m, cv::Point(startX + (index % numOfColorCol + 1) * colorBlockOffset + (index % numOfColorCol) * colorBlockSize, startY + (index / numOfColorCol + 1) * colorBlockOffset + (index / numOfColorCol) * colorBlockSize),
        cv::Point(startX + (index % numOfColorCol + 1) * colorBlockOffset + (index % numOfColorCol + 1) * colorBlockSize, startY + (index / numOfColorCol + 1) * colorBlockOffset + (index / numOfColorCol + 1) * colorBlockSize), CV_RGB(135, 206, 250));
}

void Color::selectDisplayColor(cv::Mat& m, int mousePosX, int mousePosY)
{
    if (mousePosX < initStartX || mousePosX > initStartX + firstColorOffsetWidth * 2 + firstColorWidth + secondColorOffsetWidth * 2 + secondColorWidth
        || mousePosY < initStartY || mousePosY > initStartY + ColorDisplayHeight) return;

    if (mousePosX < initStartX + firstColorOffsetWidth * 2 + firstColorWidth)
    {
        drawBox(m, cv::Point(initStartX, initStartY),
            cv::Point(initStartX + firstColorOffsetWidth * 2 + firstColorWidth, initStartY + ColorDisplayHeight), CV_RGB(135, 206, 250));
    }
    else
    {
        drawBox(m, cv::Point(initStartX + firstColorOffsetWidth * 2 + firstColorWidth, initStartY),
            cv::Point(initStartX + firstColorOffsetWidth * 2 + firstColorWidth + secondColorOffsetWidth * 2 + secondColorWidth, initStartY + ColorDisplayHeight), CV_RGB(135, 206, 250));
    }
}

cv::Scalar Color::selectedDisplayColor(cv::Mat& m)
{
    initialDisplayColor(m);
    cv::Mat temp;
    m.copyTo(temp);
    int startX = colorStartX + g_MenuOffsetWidth + (selectedColorNum - 1) * (firstColorOffsetWidth * 2 + firstColorWidth);
    int startY = iconHeight + g_MenuOffsetHeight;

    drawBox(temp, cv::Point(startX, startY),
        cv::Point(startX + firstColorOffsetWidth * 2 + firstColorWidth - colorOffset, startY + ColorDisplayHeight), selectedBlockColor, -1);

    double alpha = 0.3;
    cv::addWeighted(temp, alpha, m, 1.0 - alpha, 0.0, m);

    if (selectedColorNum == 1) return colorOne;
    else return colorTwo;
}

bool Color::changeDisplayColorNum(int mousePosX, int mousePosY)
{
    if (mousePosX < initStartX || mousePosX > initStartX + firstColorOffsetWidth * 2 + firstColorWidth + secondColorOffsetWidth * 2 + secondColorWidth
        || mousePosY < initStartY || mousePosY > initStartY + ColorDisplayHeight) return false;

    if (mousePosX < initStartX + firstColorOffsetWidth * 2 + firstColorWidth) selectedColorNum = 1;
    else selectedColorNum = 2;

    return true;
}

cv::Scalar Color::changeDrawingColor(int mousePosX, int mousePosY)
{
    int startX = colorStartX + g_MenuOffsetWidth + firstColorOffsetWidth * 2 + firstColorWidth + secondColorWidth + secondColorOffsetWidth * 2 - colorBlockOffset + colorOffset;
    int startY = iconHeight + g_MenuOffsetHeight - colorBlockOffset;

    if (mousePosX < startX || mousePosX > startX + (colorBlockOffset + colorBlockSize) * numOfColorCol ||
        mousePosY < startY || mousePosY > startY + (colorBlockSize + colorOffset) * numOfColorRow) return cv::Scalar(-1,-1,-1);

    int index = (mousePosX - startX) / (colorBlockSize + colorBlockOffset) + (mousePosY - startY) / (colorBlockSize + colorBlockOffset) * numOfColorCol;

    if (index < colorBlockColor.size())
    {
        if (selectedColorNum == 1) colorOne = colorBlockColor[index];
        else colorTwo = colorBlockColor[index];
        return colorBlockColor[index];
    }
    else return white;
}

void Color::changeDisplayColor(cv::Mat& m, cv::Scalar color)
{
    if (selectedColorNum == 1)
    {
        drawBox(m, cv::Point(initStartX + firstColorOffsetWidth + colorOffset, initStartY + firstColorOffsetHeight + colorOffset),
            cv::Point(initStartX + firstColorOffsetWidth + firstColorWidth - colorOffset, initStartY + firstColorOffsetHeight + firstColorHeight - colorOffset), color, -1);
    }
    else
    {
        drawBox(m, cv::Point(initStartX + firstColorOffsetWidth * 2 + colorOffset + firstColorWidth + secondColorOffsetWidth, initStartY + secondColorOffsetHeight + colorOffset),
            cv::Point(initStartX + firstColorOffsetWidth * 2 + firstColorWidth  + secondColorWidth + secondColorOffsetWidth - colorOffset, initStartY + secondColorHeight + secondColorOffsetHeight - colorOffset), color, -1);
    }
}

