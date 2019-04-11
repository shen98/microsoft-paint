#include "stdafx.h"
#include "paint.h"

Paint::Paint()
{

}

Paint::~Paint()
{

}

bool Paint::initialize(cv::Mat& m, int height, int width)
{
    m = cv::Mat(height, width, CV_8UC3, white);
    bool result;

    draw = new Draw();
    if (!draw)
    {
        cout << "Cannot create Draw object." << endl;
        return false;
    }

    result = draw->initialize();
    if (!result)
    {
        cout << "Cannot initialize draw." << endl;
        return false;
    }

    shape = new Shape();
    if (!shape)
    {
        cout << "Cannot create shape object" << endl;
        return false;
    }

    brush = new Brush();
    if (!brush)
    {
        return false;
    }

	rightClick = new RightClick();
	if (!rightClick)
	{
		cout << "Cannot create RightClick object." << endl;
		return false;
	}

	result = rightClick->initialize();
	if (!result)
	{
		cout << "Cannot initialize RightClick object." << endl;
		return false;
	}

    return true;
}

void Paint::resize(cv::Mat& m, cv::Point startPos, cv::Point endPos, int thickLevel)
{
    m = m(cv::Range(std::min(startPos.y, endPos.y) + thickLevel, std::max(startPos.y, endPos.y)),
        cv::Range(std::min(startPos.x, endPos.x) + thickLevel, std::max(startPos.x, endPos.x)));
    //cv::resize(m, m, cv::Size(abs(endPos.x - startPos.x), abs(endPos.y - startPos.y)));
}

void Paint::paint(cv::Mat& m)
{
    draw->draw(m, shape->getShapes(), brush->getBrushes());
}

void Paint::drawTempShape(int index, cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness, bool finished /*= false*/)
{
    switch (index)
    {
    case 0:
        shape->drawTempRect(m, startPos, endPos, color, thickness, finished);
        break;
    case 1:
        shape->drawTempLine(m, startPos, endPos, color, thickness, finished);
        break;
    case 2:
        shape->drawTempCircle(m, startPos, endPos, color, thickness, finished);
        break;
    default:
        break;
    }
}

cv::Point Paint::checkMousePosOnCorner(cv::Mat& m, int mousePosX, int mousePosY)
{
    return shape->checkMousePosOnCorner(m, mousePosX, mousePosY);
}

void Paint::changeShapeCorner(int indexOfShape, int mousePosX, int mousePosY)
{
    shape->changeShapeCorner(indexOfShape, mousePosX, mousePosY);
}

void Paint::changeShapeStatus(int indexOfShape, bool finished)
{
    shape->changeShapeStatus(indexOfShape, finished);
}

int Paint::getSelectedShapeIndex(cv::Point p)
{
    return shape->getSelectedShapeIndex(p);
}

void Paint::finishDrawingShape(int indexOfShape, bool status /*= false*/)
{
    shape->finishDrawingShape(indexOfShape, status);
}

void Paint::selectShape(cv::Mat& m, int mousePosX, int mousePosY)
{
    shape->selectShape(m, mousePosX, mousePosY);
}

void Paint::selectedShape(cv::Mat& m, int index)
{
    shape->selectedShape(m, index);
}

void Paint::changeSelectedShapeColor(int indexOfShape, cv::Scalar color)
{
    shape->changeSelectedShapeColor(indexOfShape, color);
}

void Paint::changeSelectedStatus(int status)
{
    shape->changeSelectedStatus(status);
}

void Paint::drawWithBrush(cv::Mat& m, cv::Point startPos, cv::Point endPos, int type, cv::Scalar color, int thickness /*= 1*/)
{
    brush->drawWithBrush(m, startPos, endPos, type, color, thickness);
}

void Paint::rightclicked(cv::Mat& m ,int indexOfShape, int mousePosX, int mousePosY, bool firstTime)
{
	rightClick->rightclicked(m, indexOfShape, mousePosX, mousePosY, firstTime);
}

bool Paint::selectedRotate()
{
    return shape->selectedRatote();
}

void Paint::rotateShape(cv::Mat& m, int indexOfShape, int mousePosX, int mousePosY)
{
    shape->rotateShape(m, indexOfShape, mousePosX, mousePosY);
}
