#include "stdafx.h"
#include "draw.h"

Draw::Draw()
{

}

Draw::~Draw()
{

}

bool Draw::initialize()
{
    return true;
}

void Draw::draw(cv::Mat& m, vector<MyShape> myShapes, vector<MyBrush> myBrushes)
{
    drawShapes(m, myShapes);
    drawBrushes(m, myBrushes);
}

void Draw::drawBrushes(cv::Mat& m, vector<MyBrush> myBrushes)
{
    for (auto myBrush : myBrushes)
    {
        if (myBrush.type == NORMAL) drawLine(m, myBrush.startPos, myBrush.endPos, 
            myBrush.color, myBrush.thickness);
        else if (myBrush.type == SQUARE)
        {
            double height = sqrt(pow((myBrush.startPos.x - myBrush.endPos.x), 2) + 
                pow((myBrush.startPos.y - myBrush.endPos.y), 2));
            double cos = abs(myBrush.startPos.x - myBrush.endPos.x) / height;
            double sin = abs(myBrush.startPos.y - myBrush.endPos.y) / height;

            cv::Point p1, p2;
            p1.x = myBrush.startPos.x - 1.5 * height * sin;
            p1.y = myBrush.startPos.y - 1.5 * height * cos;
            p2.x = myBrush.endPos.x + 1.5 * height * sin;
            p2.y = myBrush.endPos.y + 1.5 * height * cos;

            drawBox(m, p1, p2, myBrush.color, myBrush.thickness);
        }
        else if (myBrush.type == SPILL)
        {
            drawCircle(m, myBrush.startPos, myBrush.endPos, myBrush.color, myBrush.thickness);
        }
    }
}

void Draw::drawShapes(cv::Mat& m, vector<MyShape> myShapes)
{
    m = cv::Scalar::all(255);
    for (auto myShape : myShapes)
    {
        if (!myShape.finished) continue;
        if (myShape.type == RECTANGLE) drawBox(m, cv::Point(myShape.corners[0].x, myShape.corners[0].y),
            cv::Point(myShape.corners[3].x, myShape.corners[3].y), cv::Point(myShape.corners[2].x, myShape.corners[2].y),
            cv::Point(myShape.corners[1].x, myShape.corners[1].y), myShape.color, myShape.thickness);
        else if (myShape.type == LINE) drawLine(m, cv::Point(myShape.corners[0].x, myShape.corners[0].y),
            cv::Point(myShape.corners[1].x, myShape.corners[1].y), myShape.color, myShape.thickness);
        else if (myShape.type == CIRCLE)
        {
            drawEllipse(m, cv::Point(myShape.corners.back().x, myShape.corners.back().y),
                cv::Point(myShape.corners[0].x, myShape.corners[0].y), myShape.color, myShape.thickness);
        }

        if (!myShape.completed)
        {
            for (auto corner : myShape.corners)
            {
                if (corner.x == -1 || corner.y == -1) continue;
                cv::circle(m, corner, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
            }
        }

        if (myShape.corners.back() != cv::Point(-1, -1)) {
            double radius = sqrt(pow((myShape.corners.back().x - myShape.corners[4].x), 2) +
                pow((myShape.corners.back().y - myShape.corners[4].y), 2));
            cv::circle(m, myShape.corners.back(), radius, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
        }
    }
}
