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

void Color::initializeColor(cv::Mat& m, cv::Scalar colorOne, cv::Scalar colorTwo)
{
    int startX = colorStartX + firstColorOffsetWidth + g_MenuOffsetWidth;
    int startY = iconHeight + g_MenuOffsetHeight;
    shape->drawBox(m, cv::Point(startX, startY + firstColorOffsetHeight),
        cv::Point(startX + firstColorWidth, startY + firstColorOffsetHeight + firstColorHeight), black);

    shape->drawBox(m, cv::Point(startX + colorOffset, startY + firstColorOffsetHeight + colorOffset),
        cv::Point(startX + firstColorWidth - colorOffset, startY + firstColorOffsetHeight + firstColorHeight - colorOffset), colorOne, -1);

    startX += firstColorWidth + firstColorOffsetWidth + secondColorOffsetWidth;
    shape->drawBox(m, cv::Point(startX, startY + secondColorOffsetHeight),
        cv::Point(startX + secondColorWidth, startY + secondColorWidth + secondColorOffsetHeight), black);

    shape->drawBox(m, cv::Point(startX + colorOffset, startY + secondColorOffsetHeight + colorOffset),
        cv::Point(startX + secondColorWidth - colorOffset, startY + secondColorWidth + secondColorOffsetHeight - colorOffset), colorTwo, -1);

    startX += secondColorWidth + secondColorOffsetWidth;
    for (int i = 0; i < numOfColorRow; i++)
    {
        for (int j = 0; j < numOfColorCol; j++)
        {
            shape->drawBox(m, cv::Point(startX + j * colorBlockSize + colorBlockOffset * j, startY + i * colorBlockSize + i * colorBlockOffset),
                cv::Point(startX + (j + 1) * colorBlockSize + colorBlockOffset * j, startY + (i + 1) * colorBlockSize + i * colorBlockOffset), black);
            cv::Scalar colorTemp;
            if (i * numOfColorCol + j >= colorBlockColor.size()) colorTemp = CV_RGB(255, 255, 255);
            else colorTemp = colorBlockColor[i * numOfColorCol + j];
            shape->drawBox(m, cv::Point(startX + j * colorBlockSize + colorBlockOffset * j + colorOffset, startY + i * colorBlockSize + i * colorBlockOffset + colorOffset),
                cv::Point(startX + (j + 1) * colorBlockSize + colorBlockOffset * j - colorOffset, startY + (i + 1) * colorBlockSize + i * colorBlockOffset - colorOffset), colorTemp, -1);

        }
    }
}

void Color::selectColor(cv::Mat& m, int mousePosX, int mousePosY)
{
    int initStartX = colorStartX + g_MenuOffsetWidth;
    int initStartY = iconHeight + g_MenuOffsetHeight;

    int startX = colorStartX + g_MenuOffsetWidth + firstColorOffsetWidth * 2 + firstColorWidth + secondColorWidth + secondColorOffsetWidth * 2 - colorBlockOffset;
    int startY = iconHeight + g_MenuOffsetHeight - colorBlockOffset;

    if (mousePosX < initStartX || mousePosX > startX + (colorBlockSize + colorBlockOffset) * numOfColorCol
        || mousePosY < startY || mousePosY > startY + (colorBlockOffset + colorBlockSize) * numOfColorRow) return;

    if (mousePosX > initStartX && mousePosX < initStartX + firstColorOffsetWidth * 2 + firstColorWidth &&
        mousePosY > initStartY && mousePosY < initStartY + firstColorDisplayHeight)
    {
        cout << 1 << endl;
        cv::rectangle(m, cv::Point(initStartX, initStartY),
            cv::Point(initStartX + firstColorOffsetWidth * 2 + firstColorWidth, initStartY + firstColorDisplayHeight), CV_RGB(135, 206, 250));
        return;
    }

    int index = (mousePosX - startX) / (colorBlockSize + colorBlockOffset) + (mousePosY - startY) / (colorBlockSize + colorBlockOffset) * numOfColorCol;

    cv::rectangle(m, cv::Point(startX + (index % numOfColorCol + 1) * colorBlockOffset + (index % numOfColorCol) * colorBlockSize, startY + (index / numOfColorCol + 1) * colorBlockOffset + (index / numOfColorCol) * colorBlockSize),
        cv::Point(startX + (index % numOfColorCol + 1) * colorBlockOffset + (index % numOfColorCol + 1) * colorBlockSize, startY + (index / numOfColorCol + 1) * colorBlockOffset + (index / numOfColorCol + 1) * colorBlockSize), CV_RGB(135, 206, 250));
}

