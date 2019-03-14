#include "stdafx.h"
#include "shape.h"

Shape::Shape()
{

}

Shape::~Shape()
{

}

bool Shape::initialShape(cv::Mat& m)
{
    int startX = 380 + g_MenuOffsetWidth, startY = iconHeight + g_MenuOffsetHeight;
    cv::rectangle(m, cv::Rect(cv::Point(startX, startY),
        cv::Point(startX + (shapeButtonWidth + shapeOffsetWidth * 2) * 7, startY + 3 * (shapeButtonHeight + shapeOffsetHeight * 2))), CV_RGB(255, 255, 255), -1);
    cv::putText(m, "Shapes", cv::Point(480 - 2.5 * textSize, g_MenuHeight - g_MenuOffsetHeight - textSize), cv::FONT_HERSHEY_TRIPLEX, 0.5, black, 1, cv::LINE_AA);

    shapes->drawBox(m, cv::Point(startX + shapeOffsetWidth, startY + shapeOffsetHeight),
        cv::Point(startX + shapeButtonWidth + shapeOffsetWidth - 1, startY + shapeOffsetHeight + shapeButtonHeight - 1), defaultShapeColor);
    shapes->drawLine(m, cv::Point(startX + shapeOffsetWidth * 3 + shapeButtonWidth, startY + shapeOffsetHeight),
        cv::Point(startX + shapeButtonWidth * 2 + shapeOffsetWidth * 3 - 1, startY + shapeOffsetHeight + shapeButtonHeight - 1), defaultShapeColor);
    shapes->drawEllipse(m, cv::Point(startX + shapeOffsetWidth * 5 + shapeButtonWidth * 2.5, startY + shapeOffsetWidth + 0.5 * shapeButtonHeight),
        cv::Point(startX + shapeButtonWidth * 2 + shapeOffsetWidth * 5, startY + shapeOffsetHeight - 1), defaultShapeColor);
    shapes->drawRoundedRectangle(m, cv::Point(startX + shapeOffsetWidth * 7 + 3.5 * shapeButtonWidth, startY + shapeOffsetHeight + 0.5 * shapeButtonHeight),
        cv::Point(startX + shapeButtonWidth * 3 + shapeOffsetWidth * 7 + 1, startY + shapeOffsetHeight + 1), defaultShapeColor);
    shapes->drawRegularTriangle(m, cv::Point(startX + shapeOffsetWidth * 9 + 4.5 * shapeButtonWidth, startY + shapeOffsetHeight + 0.5 * shapeButtonHeight - 1),
        cv::Point(startX + shapeButtonWidth * 4 + shapeOffsetWidth * 9, startY + shapeOffsetHeight + shapeButtonWidth - 5), defaultShapeColor);

    return true;
}

void Shape::selectShape(cv::Mat& m, int mousePosX, int mousePosY)
{
    if (mousePosY > g_MenuHeight || mousePosY < iconHeight || mousePosX < Section::shape || mousePosX > Section::thick) return;
    int index = (mousePosX - Section::shape - g_MenuOffsetWidth) / (shapeButtonWidth + shapeOffsetWidth) +
        7 * ((mousePosY - iconHeight - g_MenuOffsetHeight) / (shapeButtonHeight + shapeOffsetHeight));
    if (index < 0 || index > 20) return;

    cv::rectangle(m, cv::Rect(cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffsetWidth, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2) * shapeOffsetHeight),
        cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffsetWidth, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2 + 2) * shapeOffsetHeight)), defaultShapeColor);
}

void Shape::selectedShape(cv::Mat& m, int index)
{
    if (g_selectedShape) initialShape(m);
    cv::Mat temp;
    m.copyTo(temp);

    cv::rectangle(temp, cv::Rect(cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffsetWidth, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2) * shapeOffsetHeight),
        cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffsetWidth, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2 + 2) * shapeOffsetHeight)), CV_RGB(0, 191, 255), -1);

    double alpha = 0.3;
    cv::addWeighted(temp, alpha, m, 1.0 - alpha, 0.0, m);

    cv::rectangle(m, cv::Rect(cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffsetWidth, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2) * shapeOffsetHeight),
        cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffsetWidth, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2 + 2) * shapeOffsetHeight)), defaultShapeColor);

    g_selectedShape = true;
}

