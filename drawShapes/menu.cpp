#include "stdafx.h"
#include "menu.h"

Menu::Menu()
{
    g_buttonState = vector<bool>(g_ButtonNum, false);
    shape = NULL;
}

Menu::~Menu()
{

}

bool Menu::initialize(cv::Mat& m, int width)
{
    initialMenu(m, width);

    shape = new Shapes();
    if (!shape)
    {
        return false;
    }

    return true;
}

void Menu::initialMenu(cv::Mat& m, int width)
{
    cout << g_MenuHeight << endl;
    cv::rectangle(m, cv::Rect(cv::Point(0, 0), cv::Point(width, g_MenuHeight)), CV_RGB(230, 230, 250), -1);

    cv::line(m, cv::Point(100, iconHeight + g_MenuOffset), cv::Point(100, g_MenuHeight - g_MenuOffset), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(250, iconHeight + g_MenuOffset), cv::Point(250, g_MenuHeight - g_MenuOffset), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(320, iconHeight + g_MenuOffset), cv::Point(320, g_MenuHeight - g_MenuOffset), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(380, iconHeight + g_MenuOffset), cv::Point(380, g_MenuHeight - g_MenuOffset), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(580, iconHeight + g_MenuOffset), cv::Point(580, g_MenuHeight - g_MenuOffset), CV_RGB(135, 206, 250));

    initialShapes(m);
    /*for (int i = 0; i < g_ButtonNum; ++i)
    {
        string fileName = "buttons/" + g_buttonName[i] + ".png";
        cv::Mat img = cv::imread(fileName);
        cv::resize(img, img, cv::Size(g_ButtonSize, g_ButtonSize));
        img.copyTo(m(cv::Range(g_MenuOffset, g_MenuOffset + g_ButtonSize),
            cv::Range(g_MenuOffset * (i + 1) + g_ButtonSize * i, g_MenuOffset * (i + 1) + g_ButtonSize * (i + 1))));
    }*/
}

int Menu::getMouseClick(int mousePosX, int mousePosY)
{
    if (mousePosX > Section::clipboard && mousePosX < Section::image)
    {

    }
    else if (mousePosX > Section::image && mousePosX < tool)
    {

    }
    else if (mousePosX > Section::tool && mousePosX < Section::brush)
    {

    }
    else if (mousePosX > Section::brush && mousePosX < Section::shape)
    {

    }
    else if (mousePosX > Section::shape)
    {
        int index = (mousePosX - Section::shape - g_MenuOffset) / (shapeButtonWidth + shapeOffsetWidth)  +  
            7 * ((mousePosY - iconHeight - g_MenuOffset) / (shapeButtonHeight + shapeOffsetHeight));
        if (index < 0 || index > 20) return -1;
        else return Buttons::rectangle + index;
    }
}

void Menu::initialShapes(cv::Mat& m)
{
    int startX = 380 + g_MenuOffset, startY = iconHeight + g_MenuOffset;
    cv::rectangle(m, cv::Rect(cv::Point(startX, startY),
        cv::Point(startX + (shapeButtonWidth + shapeOffsetWidth * 2) * 7, startY + 3 * (shapeButtonHeight + shapeOffsetHeight * 2))), CV_RGB(255,255,255), -1);
    cv::putText(m, "Shapes", cv::Point(480 - 2.5 * textSize, g_MenuHeight - g_MenuOffset - textSize), cv::FONT_HERSHEY_TRIPLEX, 0.5, CV_RGB(0, 0, 0));

    shape->drawBox(m, cv::Point(startX + shapeOffsetWidth, startY + shapeOffsetHeight), 
        cv::Point(startX + shapeButtonWidth + shapeOffsetWidth - 1, startY + shapeOffsetHeight + shapeButtonHeight - 1), defaultShapeColor);
    shape->drawLine(m, cv::Point(startX + shapeOffsetWidth * 3 + shapeButtonWidth, startY + shapeOffsetHeight), 
        cv::Point(startX + shapeButtonWidth * 2 + shapeOffsetWidth * 3 - 1, startY + shapeOffsetHeight + shapeButtonHeight - 1), defaultShapeColor);
    shape->drawEllipse(m, cv::Point(startX + shapeOffsetWidth * 5 + shapeButtonWidth * 2.5, startY + shapeOffsetWidth + 0.5 * shapeButtonHeight),
        cv::Point(startX + shapeButtonWidth * 2 + shapeOffsetWidth * 5, startY + shapeOffsetHeight - 1), defaultShapeColor);
    shape->drawRoundedRectangle(m, cv::Point(startX + shapeOffsetWidth * 7 + 3.5 * shapeButtonWidth, startY + shapeOffsetHeight + 0.5 * shapeButtonHeight),
        cv::Point(startX + shapeButtonWidth * 3 + shapeOffsetWidth * 7 + 1, startY + shapeOffsetHeight + 1), defaultShapeColor);
    shape->drawRegularTriangle(m, cv::Point(startX + shapeOffsetWidth * 9 + 4.5 * shapeButtonWidth, startY + shapeOffsetHeight + 0.5 * shapeButtonHeight - 1),
        cv::Point(startX + shapeButtonWidth * 4 + shapeOffsetWidth * 9, startY + shapeOffsetHeight + shapeButtonWidth - 5), defaultShapeColor);

}

void Menu::selectShape(cv::Mat& m, int mousePosX, int mousePosY)
{
    if (mousePosY > g_MenuHeight || mousePosY < iconHeight || mousePosX < Section::shape) return;
    int index = (mousePosX - Section::shape - g_MenuOffset) / (shapeButtonWidth + shapeOffsetWidth) +
        7 * ((mousePosY - iconHeight - g_MenuOffset) / (shapeButtonHeight + shapeOffsetHeight));
    if (index < 0 || index > 20) return;

    cv::rectangle(m, cv::Rect(cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffset, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffset + (index / 7 * 2) * shapeOffsetHeight),
        cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffset, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffset + (index / 7 * 2 + 2) * shapeOffsetHeight)), defaultShapeColor);
}

void Menu::changeState(int num)
{
    for (int i = 0; i < g_ButtonNum; ++i)
    {
        if (i != num) g_buttonState[i] = false;
        else g_buttonState[i] = true;
    }

    if (num != Buttons::cancel) g_startDrawing = true;
    else g_startDrawing = false;
}

bool Menu::startDrawing()
{
    return g_startDrawing;
}

void Menu::changeDrawingState(bool state)
{
    g_startDrawing = state;
}

bool Menu::getSelectedFirst()
{
    return selectedFirst;
}

void Menu::changeSelectState(bool state)
{
    selectedFirst = state;
}

int Menu::getMenuHeight()
{
    return g_MenuHeight;
}

std::vector<bool> Menu::getButtonState()
{
    return g_buttonState;
}
