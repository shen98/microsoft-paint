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

    startX += secondColorWidth + secondColorOffsetWidth + colorOffset;
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


    if (selectedColorNum == 0) return;
    else
    {
        cv::Mat temp;
        m.copyTo(temp);
        int startX = colorStartX + g_MenuOffsetWidth + (selectedColorNum - 1) * (firstColorOffsetWidth * 2 + firstColorWidth);
        int startY = iconHeight + g_MenuOffsetHeight;

        shape->drawBox(temp, cv::Point(startX, startY),
            cv::Point(startX + firstColorOffsetWidth * 2 + firstColorWidth, startY + ColorDisplayHeight), selectedBlockColor, -1);

        double alpha = 0.3;
        cv::addWeighted(temp, alpha, m, 1.0 - alpha, 0.0, m);
    }

}

void Color::selectColor(cv::Mat& m, int mousePosX, int mousePosY)
{
    int startX = colorStartX + g_MenuOffsetWidth + firstColorOffsetWidth * 2 + firstColorWidth + secondColorWidth + secondColorOffsetWidth * 2 - colorBlockOffset + colorOffset;
    int startY = iconHeight + g_MenuOffsetHeight - colorBlockOffset;

    if (mousePosX < startX || mousePosX > startX + (colorBlockOffset + colorBlockSize) * numOfColorCol ||
        mousePosY < startY || mousePosY > startY + (colorBlockSize + colorOffset) * numOfColorRow) return;

    int index = (mousePosX - startX) / (colorBlockSize + colorBlockOffset) + (mousePosY - startY) / (colorBlockSize + colorBlockOffset) * numOfColorCol;

    shape->drawBox(m, cv::Point(startX + (index % numOfColorCol + 1) * colorBlockOffset + (index % numOfColorCol) * colorBlockSize, startY + (index / numOfColorCol + 1) * colorBlockOffset + (index / numOfColorCol) * colorBlockSize),
        cv::Point(startX + (index % numOfColorCol + 1) * colorBlockOffset + (index % numOfColorCol + 1) * colorBlockSize, startY + (index / numOfColorCol + 1) * colorBlockOffset + (index / numOfColorCol + 1) * colorBlockSize), CV_RGB(135, 206, 250));
}

void Color::selectDisplayColor(cv::Mat& m, int mousePosX, int mousePosY)
{
    int initStartX = colorStartX + g_MenuOffsetWidth;
    int initStartY = iconHeight + g_MenuOffsetHeight;

    if (mousePosX < initStartX || mousePosX > initStartX + firstColorOffsetWidth * 2 + firstColorWidth + secondColorOffsetWidth * 2 + secondColorWidth
        || mousePosY < initStartY || mousePosY > initStartY + ColorDisplayHeight) return;

    if (mousePosX < initStartX + firstColorOffsetWidth * 2 + firstColorWidth)
    {
        shape->drawBox(m, cv::Point(initStartX, initStartY),
            cv::Point(initStartX + firstColorOffsetWidth * 2 + firstColorWidth, initStartY + ColorDisplayHeight), CV_RGB(135, 206, 250));
    }
    else
    {
        initStartX += firstColorOffsetWidth * 2 + firstColorWidth;
        shape->drawBox(m, cv::Point(initStartX, initStartY),
            cv::Point(initStartX + secondColorOffsetWidth * 2 + secondColorWidth, initStartY + ColorDisplayHeight), CV_RGB(135, 206, 250));
    }
}

void Color::changeDisplayColorNum(int mousePosX, int mousePosY)
{
    int initStartX = colorStartX + g_MenuOffsetWidth;
    int initStartY = iconHeight + g_MenuOffsetHeight;

    if (mousePosX < initStartX || mousePosX > initStartX + firstColorOffsetWidth * 2 + firstColorWidth + secondColorOffsetWidth * 2 + secondColorWidth
        || mousePosY < initStartY || mousePosY > initStartY + ColorDisplayHeight) return;

    if (mousePosX < initStartX + firstColorOffsetWidth * 2 + firstColorWidth) selectedColorNum = 1;
    else selectedColorNum = 2;
}

cv::Scalar Color::changeDrawingColor(int mousePosX, int mousePosY)
{
    int startX = colorStartX + g_MenuOffsetWidth + firstColorOffsetWidth * 2 + firstColorWidth + secondColorWidth + secondColorOffsetWidth * 2 - colorBlockOffset + colorOffset;
    int startY = iconHeight + g_MenuOffsetHeight - colorBlockOffset;

    if (mousePosX < startX || mousePosX > startX + (colorBlockOffset + colorBlockSize) * numOfColorCol ||
        mousePosY < startY || mousePosY > startY + (colorBlockSize + colorOffset) * numOfColorRow) return cv::Scalar(-1,-1,-1);

    int index = (mousePosX - startX) / (colorBlockSize + colorBlockOffset) + (mousePosY - startY) / (colorBlockSize + colorBlockOffset) * numOfColorCol;

    if (index < colorBlockColor.size()) return colorBlockColor[index];
    else return CV_RGB(255, 255, 255);
}

