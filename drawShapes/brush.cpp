#include "stdafx.h"
#include "brush.h"

Brush::Brush()
{

}

Brush::~Brush()
{

}

bool Brush::initialize(cv::Mat& m)
{
    shapes = new Shapes();
    if (!shapes)
    {
        return false;
    }

    srand(static_cast <unsigned> (time(NULL)));

    return true;
}

bool Brush::initializeBrush(cv::Mat& m)
{
    cv::putText(m, "Type:", cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight), cv::FONT_HERSHEY_SIMPLEX, 0.5, black, 1, cv::LINE_AA);

    updateBrushType(m, 0);

    return true;
}

void Brush::drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness)
{
    startPos = cv::Point(startPos.x - windowOffsetWidth, startPos.y - g_MenuHeight - windowOffsetHeight);
    endPos = cv::Point(endPos.x - windowOffsetWidth, endPos.y - g_MenuHeight - windowOffsetHeight);
    
    if(type == 0) shapes->drawLine(m, startPos, endPos, color, thickness);
    else if (type == 1)
    {
        double height = sqrt(pow((startPos.x - endPos.x), 2) + pow((startPos.y - endPos.y), 2));
        double cos = abs(startPos.x - endPos.x) / height;
        double sin = abs(startPos.y - endPos.y) / height;

        cv::Point p1, p2;
        p1.x = startPos.x - 1.5 * height * sin;
        p1.y = startPos.y - 1.5 * height * cos;
        p2.x = endPos.x + 1.5 * height * sin;
        p2.y = endPos.y + 1.5 * height * cos;

        shapes->drawBox(m, p1, p2, color, thickness);
    }
    else if (type == 2)
    {
        int i = 0;
        while (i++ < 10)
        {
            float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (thickness * 50))) - 25 * thickness;
            float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (thickness * 50))) - 25 * thickness;
            float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (thickness * 2)));

            cv::Point p1, p2;
            p1.x = startPos.x + x;
            p1.y = startPos.y + y;
            p2.x = p1.x;
            p2.y = p1.y - r;

            shapes->drawCircle(m, p1, p2, color, -1);
        }
    }
}

void Brush::selectBrush(cv::Mat& m, int mousePosX, int mousePosY)
{
    int startY = brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight + 1;
    shapes->drawBox(m, cv::Point(brushStartX + brushOffsetWidth, startY),
        cv::Point(brushStartX + brushOffsetWidth + brushPopUpWidth, startY + brushPopUpHeight), white, -1);

    for (int i = 0; i < brushName.size(); ++i)
    {
        cv::putText(m, brushName[i], cv::Point(brushStartX + brushOffsetWidth + brushTextOffsetWidth,
            startY + i * brushRectHeight + brushTextOffsetHeight + brushRectHeight / 2), cv::FONT_HERSHEY_SIMPLEX, 0.3, black, 1, cv::LINE_AA);
    }

    startY = brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight + 1;

    if (mousePosX < brushStartX + brushOffsetWidth || mousePosX > brushStartX + brushOffsetWidth + brushRectWidth ||
        mousePosY < startY || mousePosY > startY + brushPopUpHeight) return;

    int index = (mousePosY - startY) / brushRectHeight;

    shapes->drawBox(m, cv::Point(brushStartX + brushOffsetWidth, startY + index * brushRectHeight),
        cv::Point(brushStartX + brushOffsetWidth + brushPopUpWidth, startY + (index + 1) * brushRectHeight), popUpEdgeColor);
}


int Brush::changeBrushType(cv::Mat& m, int mousePosX, int mousePosY)
{
    int startY = brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight + 1;

    if (mousePosX < brushStartX + brushOffsetWidth || mousePosX > brushStartX + brushOffsetWidth + brushRectWidth ||
        mousePosY < startY || mousePosY > startY + brushPopUpHeight) return -1;

    brushType = (mousePosY - startY) / brushRectHeight;
    updateBrushType(m, brushType);

    return (mousePosY - startY) / brushRectHeight;
}

void Brush::updateBrushType(cv::Mat& m, int type)
{
    shapes->drawBox(m, cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight),
        cv::Point(brushStartX + brushOffsetWidth + brushRectWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight), white, -1);

    shapes->drawBox(m, cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight),
        cv::Point(brushStartX + brushOffsetWidth + brushRectWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight), black, 1);

    cv::putText(m, brushName[type], cv::Point(brushStartX + brushOffsetWidth + brushTextOffsetWidth,
        brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushTextOffsetHeight + brushRectHeight / 2), cv::FONT_HERSHEY_SIMPLEX, 0.3, black, 1, cv::LINE_AA);
}

