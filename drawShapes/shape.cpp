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

void Shape::drawTempRect(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished)
{
    shapes->drawBox(m, p1, p2, color, thickness);

    cv::Point p3, p4;
    p3.x = p1.x;
    p3.y = p2.y;
    p4.x = p2.x;
    p4.y = p1.y;

    cv::circle(m, p1, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //left-up corner
    cv::circle(m, p2, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //right-bottom corner
    cv::circle(m, p3, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //left-bottom corner
    cv::circle(m, p4, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //right-up corner

    if (finished)
    {
        MyShape curShape(p1, p2, p3, p4, RECTANGLE, color, thickness, finished);
        myShapes.push_back(curShape);
    }
}

void Shape::drawTempLine(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished)
{
    shapes->drawLine(m, p1, p2, color, thickness);

    cv::circle(m, p1, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p2, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);

    if (finished)
    {
        MyShape curShape(p1, p2, cv::Point(-1, -1), cv::Point(-1, -1), LINE, color, thickness, finished);
        myShapes.push_back(curShape);
    }
}

void Shape::drawTempCircle(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished)
{
    shapes->drawEllipse(m, p1, p2, color, thickness);

    cv::Point p3, p4, p5, p6;

    double difWidth = abs(p1.x - p2.x), difHeight = abs(p1.y - p2.y);

    p3.x = p1.x - difWidth; p3.y = p1.y - difHeight;
    p4.x = p1.x - difWidth; p4.y = p1.y + difHeight;
    p5.x = p1.x + difWidth; p5.y = p1.y - difHeight;
    p6.x = p1.x + difWidth; p6.y = p1.y + difHeight;

    cv::circle(m, p3, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p4, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p5, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p6, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);

    if (finished)
    {
        MyShape curShape(p3, p4, p5, p6, CIRCLE, color, thickness, finished, p1);
        myShapes.push_back(curShape);
    }
}

void Shape::drawTempTriangle(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished)
{

}

cv::Point Shape::checkMousePosOnCorner(cv::Mat& m, int mousePosX, int mousePosY)
{
    mousePosX -= g_MenuOffsetWidth;
    mousePosY -= (g_MenuHeight + g_MenuOffsetHeight);
    for (int i = 0; i < myShapes.size(); ++i)
    {
        for (int j = 0; j < myShapes[i].corners.size(); ++j)
        {
            if (abs(mousePosX - myShapes[i].corners[j].x) <= 5 && abs(mousePosY - myShapes[i].corners[j].y) <= 5)
            {
                cv::circle(m, cv::Point(myShapes[i].corners[j].x + g_MenuOffsetWidth, myShapes[i].corners[j].y + g_MenuHeight + g_MenuOffsetHeight), selectedCornerSize, defaultShapeColor, -1, cv::LINE_AA);
                g_selectedCorner = j;
                if (j == 0) return myShapes[i].corners[1];
                else if (j == 1) return myShapes[i].corners[0];
                else if (j == 2) return myShapes[i].corners[3];
                else if (j == 3) return myShapes[i].corners[2];
            }
        }
    }
    return cv::Point(-1, -1);
}

void Shape::selectedCorner(cv::Mat& m, int mousePosX, int mousePosY)
{

}

void Shape::drawAllShapes(cv::Mat& m)
{
    m = cv::Scalar::all(255);
    for (auto myShape : myShapes)
    {
        if(!myShape.finished) continue;
        if (myShape.type == RECTANGLE) shapes->drawBox(m, cv::Point(myShape.corners[0].x, myShape.corners[0].y),
            cv::Point(myShape.corners[1].x, myShape.corners[1].y), myShape.color, myShape.thickness);
        else if (myShape.type == LINE) shapes->drawLine(m, cv::Point(myShape.corners[0].x, myShape.corners[0].y),
            cv::Point(myShape.corners[1].x, myShape.corners[1].y), myShape.color, myShape.thickness);
        else if (myShape.type == CIRCLE)
        {
            shapes->drawEllipse(m, cv::Point(myShape.corners[4].x, myShape.corners[4].y),
                cv::Point(myShape.corners[0].x, myShape.corners[0].y), myShape.color, myShape.thickness);
        }
        
        for (auto corner : myShape.corners)
        {
            if (corner.x == -1 || corner.y == -1) continue;
            cv::circle(m, corner, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
        }
    }
}

void Shape::changeShapeCorner(int indexOfShape, int mousePosX, int mousePosY)
{
    cv::Point p(mousePosX, mousePosY);

    changeCorner(indexOfShape, g_selectedCorner, mousePosX, mousePosY);
}

void Shape::changeShapeStatus(int indexOfShape, bool finished)
{
    myShapes[indexOfShape].finished = finished;
}

int Shape::getSelectedShapeIndex(cv::Point p)
{
    for (int i = 0; i < myShapes.size(); ++i)
    {
        for (auto corner : myShapes[i].corners)
        {
            if (corner == p) return i;
        }
    }
}

void Shape::changeCorner(int indexOfShape, int corner, int mousePosX, int mousePosY)
{
    int fixed = -1;

    mousePosX -= g_MenuOffsetWidth;
    mousePosY -= g_MenuHeight + g_MenuOffsetHeight;

    if (myShapes[indexOfShape].type == CIRCLE)
    {
        cv::Point p3, p4, p5, p6;

        double difWidth = abs(myShapes[indexOfShape].corners[4].x - mousePosX), difHeight = abs(myShapes[indexOfShape].corners[4].y - mousePosY);

        p3.x = myShapes[indexOfShape].corners[4].x - difWidth; p3.y = myShapes[indexOfShape].corners[4].y - difHeight;
        p4.x = myShapes[indexOfShape].corners[4].x - difWidth; p4.y = myShapes[indexOfShape].corners[4].y + difHeight;
        p5.x = myShapes[indexOfShape].corners[4].x + difWidth; p5.y = myShapes[indexOfShape].corners[4].y - difHeight;
        p6.x = myShapes[indexOfShape].corners[4].x + difWidth; p6.y = myShapes[indexOfShape].corners[4].y + difHeight;

        myShapes[indexOfShape].corners[0] = p3;
        myShapes[indexOfShape].corners[1] = p4;
        myShapes[indexOfShape].corners[2] = p5;
        myShapes[indexOfShape].corners[3] = p6;
        return;
    }

    if (corner == 0)
    {
        myShapes[indexOfShape].corners[0] = cv::Point(mousePosX, mousePosY);
        if (myShapes[indexOfShape].corners[2].x != -1) myShapes[indexOfShape].corners[2].x = mousePosX;
        if (myShapes[indexOfShape].corners[3].y != -1) myShapes[indexOfShape].corners[3].y = mousePosY;
    }
    else if (corner == 1)
    {
        myShapes[indexOfShape].corners[1] = cv::Point(mousePosX, mousePosY);
        if (myShapes[indexOfShape].corners[3].x != -1) myShapes[indexOfShape].corners[3].x = mousePosX;
        if (myShapes[indexOfShape].corners[2].y != -1) myShapes[indexOfShape].corners[2].y = mousePosY;
    }
    else if (corner == 2)
    {
        myShapes[indexOfShape].corners[2] = cv::Point(mousePosX, mousePosY);
        myShapes[indexOfShape].corners[0].x = mousePosX;
        myShapes[indexOfShape].corners[1].y = mousePosY;
    }
    else if (corner == 3)
    {
        myShapes[indexOfShape].corners[3] = cv::Point(mousePosX, mousePosY);
        myShapes[indexOfShape].corners[1].x = mousePosX;
        myShapes[indexOfShape].corners[0].y = mousePosY;
    }

}
