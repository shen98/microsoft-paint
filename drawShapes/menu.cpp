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
    //initialMenu(m, width);

    shape = new Shapes();
    if (!shape)
    {
        return false;
    }

    thickness = new Thickness();
    if (!thickness)
    {
        return false;
    }

    color = new Color();
    if (!color)
    {
        return false;
    }

    return true;
}

void Menu::initialMenu(cv::Mat& m, int width, cv::Scalar colorOne, cv::Scalar colorTwo, int thickLevel)
{
    cv::rectangle(m, cv::Rect(cv::Point(0, 0), cv::Point(width, g_MenuHeight)), CV_RGB(230, 230, 250), -1);

    cv::line(m, cv::Point(100, iconHeight + g_MenuOffsetHeight), cv::Point(100, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(250, iconHeight + g_MenuOffsetHeight), cv::Point(250, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(320, iconHeight + g_MenuOffsetHeight), cv::Point(320, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(380, iconHeight + g_MenuOffsetHeight), cv::Point(380, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(600, iconHeight + g_MenuOffsetHeight), cv::Point(600, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));
    cv::line(m, cv::Point(660, iconHeight + g_MenuOffsetHeight), cv::Point(660, g_MenuHeight - g_MenuOffsetHeight), CV_RGB(135, 206, 250));

    initialShapes(m);
    thickness->initialThickness(m);
    color->initializeColor(m, colorOne, colorTwo);
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
    else if (mousePosX > Section::shape && mousePosX < Section::thick)
    {
        int index = (mousePosX - Section::shape - g_MenuOffsetWidth) / (shapeButtonWidth + shapeOffsetWidth)  +
            7 * ((mousePosY - iconHeight - g_MenuOffsetHeight) / (shapeButtonHeight + shapeOffsetHeight));
        if (index < 0 || index > 20) return -1;
        else return Buttons::rectangle + index;
    }
    else if (mousePosX > Section::thick && mousePosX < Section::color) return Buttons::thickness;
}

void Menu::initialShapes(cv::Mat& m)
{
    int startX = 380 + g_MenuOffsetWidth, startY = iconHeight + g_MenuOffsetHeight;
    cv::rectangle(m, cv::Rect(cv::Point(startX, startY),
        cv::Point(startX + (shapeButtonWidth + shapeOffsetWidth * 2) * 7, startY + 3 * (shapeButtonHeight + shapeOffsetHeight * 2))), CV_RGB(255,255,255), -1);
    cv::putText(m, "Shapes", cv::Point(480 - 2.5 * textSize, g_MenuHeight - g_MenuOffsetHeight - textSize), cv::FONT_HERSHEY_TRIPLEX, 0.5, CV_RGB(0, 0, 0));

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
    if (mousePosY > g_MenuHeight || mousePosY < iconHeight || mousePosX < Section::shape || mousePosX > Section::thick) return;
    int index = (mousePosX - Section::shape - g_MenuOffsetWidth) / (shapeButtonWidth + shapeOffsetWidth) +
        7 * ((mousePosY - iconHeight - g_MenuOffsetHeight) / (shapeButtonHeight + shapeOffsetHeight));
    if (index < 0 || index > 20) return;

    cv::rectangle(m, cv::Rect(cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffsetWidth, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2) * shapeOffsetHeight),
        cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffsetWidth, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2 + 2) * shapeOffsetHeight)), defaultShapeColor);
}

void Menu::selectedShape(cv::Mat& m, int index)
{
    if (g_selectedShape) initialShapes(m);
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


bool Menu::getSelectThickness()
{
    return g_selectThickness;
}

void Menu::changeSelectThickness(bool state)
{
    g_selectThickness = state;
}

int Menu::getMenuHeight()
{
    return g_MenuHeight;
}

std::vector<bool> Menu::getButtonState()
{
    return g_buttonState;
}
