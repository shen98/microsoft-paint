#include "stdafx.h"
#include "menu.h"

Menu::Menu()
{
    g_buttonState = vector<bool>(g_ButtonNum, false);
    shapes = NULL;
}

Menu::~Menu()
{

}

bool Menu::initialize(cv::Mat& m, int width)
{
    bool result;

    shapes = new Shapes();
    if (!shapes)
    {
        cout << "Cannot create shape object." << endl;
        return false;
    }

    thickness = new Thickness();
    if (!thickness)
    {
        cout << "Cannot create thickness object." << endl;
        return false;
    }

    color = new Color();
    if (!color)
    {
        cout << "Cannot create color object." << endl;
        return false;
    }

    select = new Select();
    if (!select)
    {
        cout << "Cannot create select object." << endl;
        return false;
    }

    brush = new Brush();
    if (!brush)
    {
        cout << "Cannot create brush object." << endl;
        return false;
    }

    shape = new Shape();
    if (!shape)
    {
        cout << "Cannot create shape object" << endl;
        return false;
    }

    initialMenu(m, width);

    return true;
}

void Menu::initialMenu(cv::Mat& m, int width)
{
    m = cv::Mat(g_MenuHeight, width, CV_8UC3);
    m = cv::Scalar::all(0);
    cv::rectangle(m, cv::Rect(cv::Point(0, 0), cv::Point(width, g_MenuHeight)), defaultMenuColor, -1);

    cv::line(m, cv::Point(100, iconHeight + g_MenuOffsetHeight), cv::Point(100, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(250, iconHeight + g_MenuOffsetHeight), cv::Point(250, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(320, iconHeight + g_MenuOffsetHeight), cv::Point(320, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(380, iconHeight + g_MenuOffsetHeight), cv::Point(380, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(600, iconHeight + g_MenuOffsetHeight), cv::Point(600, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(660, iconHeight + g_MenuOffsetHeight), cv::Point(660, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));

    shape->initialShape(m);
    thickness->initialThickness(m);
    color->initializeColor(m);
    select->initialSelect(m);
    brush->initializeBrush(m);
}

int Menu::getMouseClick(int mousePosX, int mousePosY)
{
    if (mousePosX > Section::clipboard && mousePosX < Section::image)
    {

    }
    else if (mousePosX > Section::image && mousePosX < tool)
    {
        return Buttons::selectBox;
    }
    else if (mousePosX > Section::tool && mousePosX < Section::brush)
    {
        return Buttons::selectBrush;
    }
    else if (mousePosX > Section::brush && mousePosX < Section::shape)
    {

    }
    else if (mousePosX > Section::shape && mousePosX < Section::thick)
    {
        int index = (mousePosX - Section::shape - g_MenuOffsetWidth) / (shapeButtonWidth + shapeOffsetWidth)  +
            7 * ((mousePosY - iconHeight - g_MenuOffsetHeight) / (shapeButtonHeight + shapeOffsetHeight));
        if (index < 0 || index > 20) return -1;
        else return Buttons::rectangle + index;
    }
    else if (mousePosX > Section::thick && mousePosX < Section::color) return Buttons::thickness;
    else if (mousePosX > Section::color)
    {
        return -1;
    }

    return -1;
}

void Menu::selectShape(cv::Mat& m, int mousePosX, int mousePosY)
{
    shape->selectShape(m, mousePosX, mousePosY);
}

void Menu::selectedShape(cv::Mat& m, int index)
{
    shape->selectedShape(m, index);
}

void Menu::selectThickness(cv::Mat& m, int mousePosX, int mousePosY, int selected)
{
    selected = (selected - 1) / 2;
    thickness->selectThickness(m, mousePosX, mousePosY, selected);
}

int Menu::changeThickness(int mousePosX, int mousePosY)
{
    return thickness->changeThickness(mousePosX, mousePosY);
}

void Menu::selectColor(cv::Mat& m, int mousePosX, int mousePosY)
{
    color->selectColor(m, mousePosX, mousePosY);
    color->selectDisplayColor(m, mousePosX, mousePosY);
}

cv::Scalar Menu::changeColor(cv::Mat& m, int mousePosX, int mousePosY)
{
    cv::Scalar temp = color->changeDrawingColor(mousePosX, mousePosY);
    if (temp != cv::Scalar(-1, -1, -1)) color->changeDisplayColor(m, temp);
    return temp;
}

cv::Scalar Menu::changeDisplayColorNum(cv::Mat& m, int mousePosX, int mousePosY)
{
    if (color->changeDisplayColorNum(mousePosX, mousePosY))
    {
        return color->selectedDisplayColor(m);
    }
    return cv::Scalar(-1, -1, -1);
}

void Menu::selectBrush(cv::Mat& m, int mousePosX, int mousePosY)
{
    brush->selectBrush(m, mousePosX, mousePosY);
}

int Menu::changeBrush(cv::Mat& m, int mousePosX, int mousePosY)
{
    return brush->changeBrushType(m, mousePosX, mousePosY);
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

void Menu::drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness)
{
    brush->drawWithBrush(m, startPos, endPos, type, color, thickness);
}

bool Menu::getSelectThickness()
{
    return g_selectThickness;
}

void Menu::changeSelectThickness(bool state)
{
    g_selectThickness = state;
}

bool Menu::getSelectBrush()
{
    return g_selectBrush;
}

void Menu::changeSelectBrush(bool state)
{
    g_selectBrush = true;
}

int Menu::getMenuHeight()
{
    return g_MenuHeight;
}

std::vector<bool> Menu::getButtonState()
{
    return g_buttonState;
}
