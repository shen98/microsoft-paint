#include "stdafx.h"
#include "shapes.h"

bool initialShapes()
{
    return true;
}

void drawBox(cv::Mat& img, cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4, cv::Scalar color, int thickness)
{
    drawLine(img, p1, p2, color, thickness);
    drawLine(img, p2, p4, color, thickness);
    drawLine(img, p1, p3, color, thickness);
    drawLine(img, p3, p4, color, thickness);
}

void drawBox(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
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

void drawCircle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    cv::circle(img, startPos, (int)sqrt(pow(startPos.x - endPos.x, 2) + pow(startPos.y - endPos.y, 2)), color, thickness, cv::LINE_AA);
}

void drawRegularTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    vector<cv::Point> vertices;
    vertices.push_back(endPos);
    cv::Point p1, p2;
    p1.y = endPos.y;
    p1.x = endPos.x - 2 * (endPos.x - startPos.x);
    vertices.push_back(p1);
    p2.x = startPos.x;
    p2.y = startPos.y - (sqrt(3) - 1) * abs(endPos.x - startPos.x);
    vertices.push_back(p2);

    cv::polylines(img, vertices, true, color, thickness, cv::LINE_AA);
}

void drawRightTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{

}

void drawLine(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    cv::line(img, startPos, endPos, color, thickness, cv::LINE_AA);
}

void drawPolygon(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    drawLine(img, startPos, endPos, color, thickness);
}

void drawEllipse(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
{
    cv::Size size(abs(endPos.x - startPos.x), abs(endPos.y - startPos.y));
    cv::ellipse(img, startPos, size, 0, 0, 460, color, thickness, cv::LINE_AA);
}

void drawRoundedRectangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness)
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

void drawDottedLine(cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness /*= 1*/)
{
    cv::LineIterator it(m, startPos, endPos);

    for (int i = 0; i < it.count; i++, it++)
    {
        if (i % 5 != 0)
        {
            (*it)[0] = (uchar)color[0]; 
            (*it)[1] = (uchar)color[1]; 
            (*it)[2] = (uchar)color[2]; 
        }
    }
}

void drawDottedRectangle(cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness /*= 1*/)
{
    cv::Point p1 = startPos;
    cv::Point p2 = cv::Point(endPos.x, startPos.y);
    cv::Point p3 = cv::Point(startPos.x, endPos.y);
    cv::Point p4 = endPos;

    drawDottedLine(m, p1, p2, color);
    drawDottedLine(m, p1, p3, color);
    drawDottedLine(m, p2, p4, color);
    drawDottedLine(m, p3, p4, color);
}