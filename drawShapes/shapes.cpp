#include "stdafx.h"
#include "shapes.h"

Shapes::Shapes()
{
}

Shapes::~Shapes()
{

}

void Shapes::drawBox(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color)
{
    cv::Rect box(startPos, endPos);
    if (box.width < 0)
    {
        box.x += box.width;
        box.width *= -1;
    }
    if (box.height < 0)
    {
        box.y += box.height;
        box.height *= -1;
    }

    cv::rectangle(img, box.tl(), box.br(), color);
}

void Shapes::drawCircle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color)
{
    cv::circle(img, startPos, (int)sqrt(pow(startPos.x - endPos.x, 2) + pow(startPos.y - endPos.y, 2)), color);
}

void Shapes::drawRegularTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color)
{
    vector<cv::Point> vertices;
    vertices.push_back(endPos);
    cv::Point p1, p2;
    p1.y = endPos.y;
    p1.x = endPos.x - 2 * (endPos.x - startPos.x);
    vertices.push_back(p1);
    p2.x = startPos.x;
    p2.y = (int)startPos.y - (sqrt(3) - 1) * abs(endPos.x - startPos.x);
    vertices.push_back(p2);

    cv::polylines(img, vertices, true, color);
}

void Shapes::drawLine(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color)
{
    cv::line(img, startPos, endPos, color);
}

void Shapes::drawPolygon(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color)
{
    drawLine(img, startPos, endPos, color);
}

void Shapes::changeColor(cv::Scalar color)
{
    color = color;
}

