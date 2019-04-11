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
    
    if (type == SPILL)
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

            myBrushes.push_back(MyBrush(p1, p2, type, color, -1));
        }
    }
    else myBrushes.push_back(MyBrush(startPos, endPos, type, color, thickness));
}

void Brush::selectBrush(cv::Mat& m, int mousePosX, int mousePosY)
{
    int startY = brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight + 1;
    drawBox(m, cv::Point(brushStartX + brushOffsetWidth, startY),
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

    drawBox(m, cv::Point(brushStartX + brushOffsetWidth, startY + index * brushRectHeight),
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

std::vector<MyBrush> Brush::getBrushes()
{
    return myBrushes;
}

void Brush::updateBrushType(cv::Mat& m, int type)
{
    drawBox(m, cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight),
        cv::Point(brushStartX + brushOffsetWidth + brushRectWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight), white, -1);

    drawBox(m, cv::Point(brushStartX + brushOffsetWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight),
        cv::Point(brushStartX + brushOffsetWidth + brushRectWidth, brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushRectHeight), black, 1);

    cv::putText(m, brushName[type], cv::Point(brushStartX + brushOffsetWidth + brushTextOffsetWidth,
        brushStartY + brushOffsetHeight * 2 + brushTextHeight + brushTextOffsetHeight + brushRectHeight / 2), cv::FONT_HERSHEY_SIMPLEX, 0.3, black, 1, cv::LINE_AA);
}

