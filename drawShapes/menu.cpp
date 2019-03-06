#include "stdafx.h"
#include "menu.h"

Menu::Menu()
{
    g_buttonState = vector<bool>(g_ButtonNum, false);
}

Menu::~Menu()
{

}

bool Menu::initialize(cv::Mat& m, int width)
{
    initialMenu(m, width);

    return true;
}

void Menu::initialMenu(cv::Mat& m, int width)
{
    cv::rectangle(m, cv::Rect(cv::Point(0, 0), cv::Point(width, g_MenuHeight)), CV_RGB(255, 255, 255), -1);

    for (int i = 0; i < g_ButtonNum; ++i)
    {
        string fileName = "buttons/" + g_buttonName[i] + ".png";
        cv::Mat img = cv::imread(fileName);
        cv::resize(img, img, cv::Size(g_ButtonSize, g_ButtonSize));
        img.copyTo(m(cv::Range(g_MenuOffset, g_MenuOffset + g_ButtonSize),
            cv::Range(g_MenuOffset * (i + 1) + g_ButtonSize * i, g_MenuOffset * (i + 1) + g_ButtonSize * (i + 1))));
    }
}

int Menu::getMouseClick(int mousePosX)
{
    return (int)floor(mousePosX / (g_ButtonSize + g_MenuOffset));
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
