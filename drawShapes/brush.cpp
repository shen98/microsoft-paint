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

    return true;
}

bool Brush::initializeBrush(cv::Mat& m)
{
    cv::putText(m, "Type:", cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight), cv::FONT_HERSHEY_SIMPLEX, 0.5, black, 1, cv::LINE_AA);

    shapes->drawBox(m, cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight),
        cv::Point(brushStartX + brushOffsetWidth + brushRectWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight), white, -1);

    shapes->drawBox(m, cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight),
        cv::Point(brushStartX + brushOffsetWidth + brushRectWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight), black, 1);

    cv::putText(m, brushName[brushType], cv::Point(brushStartX + brushOffsetWidth + brushTextOffsetWidth, 
        brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushTextOffsetHeight + brushRectHeight / 2), cv::FONT_HERSHEY_SIMPLEX, 0.3, black, 1, cv::LINE_AA);

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


int Brush::changeBrushType(int mousePosX, int mousePosY)
{
    int startY = brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight + 1;

    if (mousePosX < brushStartX + brushOffsetWidth || mousePosX > brushStartX + brushOffsetWidth + brushRectWidth ||
        mousePosY < startY || mousePosY > startY + brushPopUpHeight) return -1;

    return (mousePosY - startY) / brushRectHeight;
}

