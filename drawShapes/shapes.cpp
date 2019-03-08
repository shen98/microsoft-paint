#include "stdafx.h"
#include "shapes.h"

Shapes::Shapes()
{
}

Shapes::~Shapes()
{

}



bool Shapes::initialShapes()
{
    return true;
}

void Shapes::drawBox(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
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

    cv::rectangle(img, box.tl(), box.br(), color, thickness, cv::LINE_AA);
}

void Shapes::drawCircle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    cv::circle(img, startPos, (int)sqrt(pow(startPos.x - endPos.x, 2) + pow(startPos.y - endPos.y, 2)), color, thickness, cv::LINE_AA);
}

void Shapes::drawRegularTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
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

    cv::polylines(img, vertices, true, color, thickness, cv::LINE_AA);
}

void Shapes::drawRightTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{

}

void Shapes::drawLine(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    cv::line(img, startPos, endPos, color, thickness, cv::LINE_AA);
}

void Shapes::drawPolygon(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    drawLine(img, startPos, endPos, color, thickness);
}

void Shapes::drawEllipse(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    cv::Size size(abs(endPos.x - startPos.x), abs(endPos.y - startPos.y));
    cv::ellipse(img, startPos, size, 0, 0, 460, color, thickness, cv::LINE_AA);
}

void Shapes::drawRoundedRectangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    int cornerRadius = abs(startPos.x - endPos.x) / 4;
    cv::Point p1 = cv::Point(startPos.x - abs(endPos.x - startPos.x), startPos.y - abs(endPos.y - startPos.y) - 1);
    cv::Point p2 = cv::Point(startPos.x + abs(endPos.x - startPos.x), startPos.y - abs(endPos.y - startPos.y) - 1);
    cv::Point p3 = cv::Point(startPos.x + abs(endPos.x - startPos.x), startPos.y + abs(endPos.y - startPos.y));
    cv::Point p4 = cv::Point(startPos.x - abs(endPos.x - startPos.x), startPos.y + abs(endPos.y - startPos.y));
        
    drawLine(img, cv::Point(p1.x + cornerRadius, p1.y), cv::Point(p2.x - cornerRadius, p2.y), color, thickness);
    drawLine(img, cv::Point(p2.x, cornerRadius + p2.y), cv::Point(p2.x, p3.y - cornerRadius), color, thickness);
    drawLine(img, cv::Point(p3.x - cornerRadius, p3.y), cv::Point(p4.x + cornerRadius, p4.y), color, thickness);
    drawLine(img, cv::Point(p1.x, cornerRadius + p1.y), cv::Point(p1.x, p4.y - cornerRadius), color, thickness);

    cv::ellipse(img, p1 + cv::Point(cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 180.0, 0, 90, color, thickness, cv::LINE_AA);
    cv::ellipse(img, p2 + cv::Point(-cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 270.0, 0, 90, color, thickness, cv::LINE_AA);
    cv::ellipse(img, p3 + cv::Point(-cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 0.0, 0, 90, color, thickness, cv::LINE_AA);
    cv::ellipse(img, p4 + cv::Point(cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 90.0, 0, 90, color, thickness, cv::LINE_AA);
}

void Shapes::changeColor(cv::Scalar color)
{
    color = color;
}

