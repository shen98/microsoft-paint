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

    drawBox(m, cv::Point(startX + shapeOffsetWidth, startY + shapeOffsetHeight),
        cv::Point(startX + shapeButtonWidth + shapeOffsetWidth - 1, startY + shapeOffsetHeight + shapeButtonHeight - 1), defaultShapeColor);
    drawLine(m, cv::Point(startX + shapeOffsetWidth * 3 + shapeButtonWidth, startY + shapeOffsetHeight),
        cv::Point(startX + shapeButtonWidth * 2 + shapeOffsetWidth * 3 - 1, startY + shapeOffsetHeight + shapeButtonHeight - 1), defaultShapeColor);
    drawEllipse(m, cv::Point(startX + shapeOffsetWidth * 5 + shapeButtonWidth * 2.5, startY + shapeOffsetWidth + 0.5 * shapeButtonHeight),
        cv::Point(startX + shapeButtonWidth * 2 + shapeOffsetWidth * 5, startY + shapeOffsetHeight - 1), defaultShapeColor);
    drawRoundedRectangle(m, cv::Point(startX + shapeOffsetWidth * 7 + 3.5 * shapeButtonWidth, startY + shapeOffsetHeight + 0.5 * shapeButtonHeight),
        cv::Point(startX + shapeButtonWidth * 3 + shapeOffsetWidth * 7 + 1, startY + shapeOffsetHeight + 1), defaultShapeColor);
    drawRegularTriangle(m, cv::Point(startX + shapeOffsetWidth * 9 + 4.5 * shapeButtonWidth, startY + shapeOffsetHeight + 0.5 * shapeButtonHeight - 1),
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
	selectedEffect(m, cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffsetWidth, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2) * shapeOffsetHeight),
		cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffsetWidth, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2 + 2) * shapeOffsetHeight),
		0.3, CV_RGB(0, 191, 255), defaultShapeColor);
	/*cv::Mat temp;
	m.copyTo(temp);

	cv::rectangle(temp, cv::Rect(cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffsetWidth, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2) * shapeOffsetHeight),
		cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffsetWidth, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2 + 2) * shapeOffsetHeight)), CV_RGB(0, 191, 255), -1);

	double alpha = 0.3;
	cv::addWeighted(temp, alpha, m, 1.0 - alpha, 0.0, m);

	cv::rectangle(m, cv::Rect(cv::Point((index % 7) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2) + g_MenuOffsetWidth, (index) / 7 * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2) * shapeOffsetHeight),
		cv::Point((index % 7 + 1) * shapeButtonWidth + 380 + shapeOffsetWidth * (index % 7 * 2 + 2) + g_MenuOffsetWidth, (1 + index / 7) * shapeButtonHeight + iconHeight + g_MenuOffsetHeight + (index / 7 * 2 + 2) * shapeOffsetHeight)), defaultShapeColor);
*/
    g_selectedShape = true;
}

void Shape::drawTempRect(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished)
{
    drawBox(m, p1, p2, color, thickness);

    cv::Point p3, p4, rotate, center;
    p3.x = p1.x;
    p3.y = p2.y;
    p4.x = p2.x;
    p4.y = p1.y;

    rotate.x = (p1.x + p2.x) / 2;
    rotate.y = min(p1.y, p3.y) - abs(p1.y - p3.y) / 4;

    center.x = (p1.x + p4.x) / 2;
    center.y = (p1.y + p3.y) / 2;

    cv::circle(m, p1, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //left-up corner
    cv::circle(m, p2, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //right-bottom corner
    cv::circle(m, p3, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //left-bottom corner
    cv::circle(m, p4, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //right-up corner
    cv::circle(m, rotate, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);          //Rotate

	double k1, k2;

	if (p1.x == p3.x) k1 = -1;
	else k1 = (double)(p1.y - p3.y) / (double)(p1.x - p3.x);               //gradient of line(left bottom - right bottom)

	if (p1.x == p4.x) k2 = -1;
	else k2 = (double)(p1.y - p4.y) / (double)(p1.x - p4.x);

    int d = getDistance(rotate, center);
    if (finished)
    {
        cout << d << endl;
        cout << getDistance(rotate, center) << endl;
        MyShape curShape(p1, p2, p3, p4, rotate, RECTANGLE, color, thickness, k1, k2, finished, center, d);
        myShapes.push_back(curShape);
    }
}

void Shape::drawTempLine(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished)
{
    drawLine(m, p1, p2, color, thickness);

    cv::circle(m, p1, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p2, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);

    if (finished)
    {
        MyShape curShape(p1, p2, cv::Point(-1, -1), cv::Point(-1, -1), cv::Point(-1, -1), LINE, color, thickness, -1, -1, finished);
        myShapes.push_back(curShape);
    }
}

void Shape::drawTempCircle(cv::Mat& m, cv::Point p1, cv::Point p2, cv::Scalar color, int thickness, bool finished)
{
    drawEllipse(m, p1, p2, color, thickness);

    cv::Point p3, p4, p5, p6, rotate;

    double difWidth = abs(p1.x - p2.x), difHeight = abs(p1.y - p2.y);

    p3.x = p1.x - difWidth; p3.y = p1.y - difHeight;
    p4.x = p1.x - difWidth; p4.y = p1.y + difHeight;
    p5.x = p1.x + difWidth; p5.y = p1.y - difHeight;
    p6.x = p1.x + difWidth; p6.y = p1.y + difHeight;

    rotate.x = (p3.x + p5.x) / 2;
    rotate.y = p3.y - difHeight / 2;

    cv::circle(m, p3, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p4, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p5, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, p6, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);
    cv::circle(m, rotate, unselectedCornerSize, defaultShapeColor, unselectedCornerSize, cv::LINE_AA);

    if (finished)
    {
        MyShape curShape(p3, p4, p5, p6, rotate, CIRCLE, color, thickness, -1, -1, finished, p1);
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
        if (myShapes[i].completed) continue;
        for (int j = 0; j < myShapes[i].corners.size(); ++j)
        {
            if (abs(mousePosX - myShapes[i].corners[j].x) <= 5 && abs(mousePosY - myShapes[i].corners[j].y) <= 5)
            {
                cv::circle(m, cv::Point(myShapes[i].corners[j].x + g_MenuOffsetWidth, myShapes[i].corners[j].y + g_MenuHeight + g_MenuOffsetHeight), selectedCornerSize, defaultShapeColor, -1, cv::LINE_AA);
                g_selectedCorner = ShapeCorners::Left_Up_Corner + j;
                if (j == 0) return myShapes[i].corners[1];
                else if (j == 1) return myShapes[i].corners[0];
                else if (j == 2) return myShapes[i].corners[3];
                else if (j == 3) return myShapes[i].corners[2];
                else if (j == 4) return myShapes[i].corners[4];
            }
        }
    }
    return cv::Point(-1, -1);
}

void Shape::selectedCorner(cv::Mat& m, int mousePosX, int mousePosY)
{

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
        if (myShapes[i].completed) continue;
        for (auto corner : myShapes[i].corners)
        {
            if (corner == p) return i;
        }
    }
}

void Shape::finishDrawingShape(int indexOfShape, bool status)
{
    myShapes[indexOfShape].completed = status;
}

void Shape::changeSelectedShapeColor(int indexOfShape, cv::Scalar color)
{
    if (myShapes[indexOfShape].completed) return;
    myShapes[indexOfShape].color = color;
}

std::vector<MyShape> Shape::getShapes()
{
    return myShapes;
}

bool Shape::selectedRatote()
{
    return g_selectedCorner == ShapeCorners::Rotate;
}

void Shape::rotateShape(cv::Mat& m, int indexOfShape, int mousePosX, int mousePosY)
{
    mousePosX -= g_MenuOffsetWidth;
    mousePosY -= g_MenuOffsetHeight + g_MenuHeight;
    MyShape myShape = myShapes[indexOfShape];
    int difHeight = myShape.corners[ShapeCorners::Center].y - mousePosY;
    int difWidth = myShape.corners[ShapeCorners::Center].x - mousePosX;
    int newDistance = getDistance(myShape.corners[ShapeCorners::Center], cv::Point(mousePosX, mousePosY));

    int newHeight, newWidth;
    newHeight = difHeight * myShape.distanceFromRotateToCenter / newDistance;
    newWidth = difWidth * myShape.distanceFromRotateToCenter / newDistance;

    cv::Point newRotate = cv::Point(myShape.corners[ShapeCorners::Center].x - newWidth, myShape.corners[ShapeCorners::Center].y - newHeight);
    cv::circle(m, newRotate, selectedCornerSize, defaultShapeColor, selectedCornerSize, cv::LINE_AA);
    myShapes[indexOfShape].corners[ShapeCorners::Rotate] = newRotate;
}

void Shape::changeSelectedStatus(int status)
{
    g_selectedCorner = status;
}

void Shape::changeCorner(int indexOfShape, int corner, int mousePosX, int mousePosY)
{
    int fixed = -1;

    mousePosX -= g_MenuOffsetWidth;
    mousePosY -= g_MenuHeight + g_MenuOffsetHeight;

    if (myShapes[indexOfShape].type == CIRCLE)
    {
        cv::Point p3, p4, p5, p6;

        double difWidth = abs(myShapes[indexOfShape].corners.back().x - mousePosX), 
            difHeight = abs(myShapes[indexOfShape].corners.back().y - mousePosY);

        p3.x = myShapes[indexOfShape].corners[ShapeCorners::Center].x - difWidth; p3.y = myShapes[indexOfShape].corners[ShapeCorners::Center].y - difHeight;
        p4.x = myShapes[indexOfShape].corners[ShapeCorners::Center].x - difWidth; p4.y = myShapes[indexOfShape].corners[ShapeCorners::Center].y + difHeight;
        p5.x = myShapes[indexOfShape].corners[ShapeCorners::Center].x + difWidth; p5.y = myShapes[indexOfShape].corners[ShapeCorners::Center].y - difHeight;
        p6.x = myShapes[indexOfShape].corners[ShapeCorners::Center].x + difWidth; p6.y = myShapes[indexOfShape].corners[ShapeCorners::Center].y + difHeight;

        myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner] = p3;
        myShapes[indexOfShape].corners[ShapeCorners::Right_Bottom_Corner] = p4;
        myShapes[indexOfShape].corners[ShapeCorners::Left_Bottom_Corner] = p5;
        myShapes[indexOfShape].corners[ShapeCorners::Right_Up_Corner] = p6;

        myShapes[indexOfShape].corners[ShapeCorners::Rotate].x = (p3.x + p5.x) / 2;
        myShapes[indexOfShape].corners[ShapeCorners::Rotate].y = p3.y - difHeight / 2;
        return;
    }

    if (corner == ShapeCorners::Left_Up_Corner)             //Right Bottom Corner is be fixed
    {
        changeLeftUpCorner(indexOfShape, mousePosX, mousePosY);
    }
    else if (corner == ShapeCorners::Right_Bottom_Corner)   //Left Up Corner is be fixed
    {
		changeRightBottomCorner(indexOfShape, mousePosX, mousePosY);
        
    }
    else if (corner == ShapeCorners::Left_Bottom_Corner)    //Right Up Corner is be fixed
    {
		changeLeftBottomCorner(indexOfShape, mousePosX, mousePosY);
    }
    else if (corner == ShapeCorners::Right_Up_Corner)       //Left Bottom Corner is be fixed
    {
		changeRightUpCorner(indexOfShape, mousePosX, mousePosY);
    }
    else if (corner == ShapeCorners::Rotate)
    {
        MyShape& myShape = myShapes[indexOfShape];
        double height = getDistance(myShape.corners[ShapeCorners::Left_Up_Corner], myShape.corners[ShapeCorners::Left_Bottom_Corner]);
        double width = getDistance(myShape.corners[ShapeCorners::Left_Up_Corner], myShape.corners[ShapeCorners::Right_Up_Corner]);
        double distanceFromRotateToCenter = sqrt(pow((myShape.corners[ShapeCorners::Center].y - myShape.corners[ShapeCorners::Rotate].y), 2)
            + pow((myShape.corners[ShapeCorners::Center].x - myShape.corners[ShapeCorners::Rotate].x), 2));

        double cos = -(myShape.corners[ShapeCorners::Center].x - myShape.corners[ShapeCorners::Rotate].x) / distanceFromRotateToCenter;
        double sin = -(myShape.corners[ShapeCorners::Center].y - myShape.corners[ShapeCorners::Rotate].y) / distanceFromRotateToCenter;

        cv::Point upper, lower;
        upper.x = myShape.corners[ShapeCorners::Center].x + 0.672 * (myShape.corners[ShapeCorners::Rotate].x - myShape.corners[ShapeCorners::Center].x);
        upper.y = myShape.corners[ShapeCorners::Center].y + 0.672 * (myShape.corners[ShapeCorners::Rotate].y - myShape.corners[ShapeCorners::Center].y);
        lower.x = myShape.corners[ShapeCorners::Center].x - 0.672 * (myShape.corners[ShapeCorners::Rotate].x - myShape.corners[ShapeCorners::Center].x);
        lower.y = myShape.corners[ShapeCorners::Center].y - 0.672 * (myShape.corners[ShapeCorners::Rotate].y - myShape.corners[ShapeCorners::Center].y);

        myShape.corners[ShapeCorners::Right_Up_Corner].x = upper.x - sin * 0.5 * width;
        myShape.corners[ShapeCorners::Right_Up_Corner].y = upper.y + cos * 0.5 * width;
        myShape.corners[ShapeCorners::Left_Up_Corner].x = upper.x + sin * 0.5 * width;
        myShape.corners[ShapeCorners::Left_Up_Corner].y = upper.y - cos * 0.5 * width;
        myShape.corners[ShapeCorners::Right_Bottom_Corner].x = lower.x - sin * 0.5 * width;
        myShape.corners[ShapeCorners::Right_Bottom_Corner].y = lower.y + cos * 0.5 * width;
        myShape.corners[ShapeCorners::Left_Bottom_Corner].x = lower.x + sin * 0.5 * width;
        myShape.corners[ShapeCorners::Left_Bottom_Corner].y = lower.y - cos * 0.5 * width;

		myShape.k1 = (double)(myShape.corners[ShapeCorners::Left_Up_Corner].y - myShape.corners[ShapeCorners::Left_Bottom_Corner].y) /
			(double)(myShape.corners[ShapeCorners::Left_Up_Corner].x - myShape.corners[ShapeCorners::Left_Bottom_Corner].x);
		myShape.k2 = (double)(myShape.corners[ShapeCorners::Left_Up_Corner].y - myShape.corners[ShapeCorners::Right_Up_Corner].y) /
			(double)(myShape.corners[ShapeCorners::Left_Up_Corner].x - myShape.corners[ShapeCorners::Right_Up_Corner].x);
    }

    if (corner != ShapeCorners::Rotate) {
        myShapes[indexOfShape].corners[ShapeCorners::Rotate].x = (myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner].x + myShapes[indexOfShape].corners[ShapeCorners::Right_Bottom_Corner].x) / 2;
        myShapes[indexOfShape].corners[ShapeCorners::Rotate].y = min(myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner].y, myShapes[indexOfShape].corners[Left_Bottom_Corner].y)
            - abs(myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner].y - myShapes[indexOfShape].corners[ShapeCorners::Left_Bottom_Corner].y) / 4;
    
		ReCenter(indexOfShape);
    }
}

double Shape::getDistance(cv::Point p1, cv::Point p2)
{
    return sqrt(pow((p1.y - p2.y), 2)
        + pow((p1.x - p2.x), 2));
}

void Shape::changeLeftUpCorner(int indexOfShape, int mousePosX, int mousePosY)		//right bottom is fixed
{
	MyShape& myShape = myShapes[indexOfShape];
	double c1, c2, c;
	if (myShape.k1 == -1)
	{
		myShape.corners[ShapeCorners::Left_Bottom_Corner].x = mousePosX;
		myShape.corners[ShapeCorners::Right_Up_Corner].y = mousePosY;
		myShape.corners[ShapeCorners::Left_Up_Corner] = cv::Point(mousePosX, mousePosY);
		return;
	}

	if (myShape.k2 == -1)
	{
		cout << 1 << endl;

	}
	
	c1 = myShape.corners[ShapeCorners::Right_Bottom_Corner].y - myShape.k1 * myShape.corners[ShapeCorners::Right_Bottom_Corner].x;
	c2 = myShape.corners[ShapeCorners::Right_Bottom_Corner].y - myShape.k2 * myShape.corners[ShapeCorners::Right_Bottom_Corner].x;
	c = mousePosY - myShape.k2 * mousePosX;

	if (myShapes[indexOfShape].corners[ShapeCorners::Left_Bottom_Corner].x != -1)
	{
		myShape.corners[ShapeCorners::Left_Bottom_Corner].x = (c - c1) / (myShape.k1 - myShape.k2);
		myShape.corners[ShapeCorners::Left_Bottom_Corner].y = myShape.k2*myShape.corners[ShapeCorners::Left_Bottom_Corner].x + c;
	}

	c = mousePosY - myShape.k1*mousePosX;

	if (myShapes[indexOfShape].corners[ShapeCorners::Right_Up_Corner].y != -1)
	{
		myShape.corners[ShapeCorners::Right_Up_Corner].x = (c - c2) / (myShape.k2 - myShape.k1);
		myShape.corners[ShapeCorners::Right_Up_Corner].y = myShape.k1*myShape.corners[ShapeCorners::Right_Up_Corner].x + c;
	}
	myShape.corners[ShapeCorners::Left_Up_Corner] = cv::Point(mousePosX, mousePosY);

	ReCenter(indexOfShape);
}

void Shape::changeRightUpCorner(int indexOfShape, int mousePosX, int mousePosY)
{
	MyShape& myShape = myShapes[indexOfShape];
	double c1, c2, c;
	if (myShape.k1 == -1)
	{
		myShapes[indexOfShape].corners[ShapeCorners::Right_Up_Corner] = cv::Point(mousePosX, mousePosY);
		myShapes[indexOfShape].corners[ShapeCorners::Right_Bottom_Corner].x = mousePosX;
		myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner].y = mousePosY;
		return;
	}

	if (myShape.k2 == -1)
	{
		cout << 1 << endl;

	}

	c1 = myShape.corners[ShapeCorners::Left_Bottom_Corner].y - myShape.k1 * myShape.corners[ShapeCorners::Left_Bottom_Corner].x;
	c2 = myShape.corners[ShapeCorners::Left_Bottom_Corner].y - myShape.k2 * myShape.corners[ShapeCorners::Left_Bottom_Corner].x;
	c = mousePosY - myShape.k2 * mousePosX;

	myShape.corners[ShapeCorners::Left_Up_Corner].x = (c - c1) / (myShape.k1 - myShape.k2);
	myShape.corners[ShapeCorners::Left_Up_Corner].y = myShape.k2*myShape.corners[ShapeCorners::Left_Up_Corner].x + c;

	c = mousePosY - myShape.k1*mousePosX;

	myShape.corners[ShapeCorners::Right_Bottom_Corner].x = (c - c2) / (myShape.k2 - myShape.k1);
	myShape.corners[ShapeCorners::Right_Bottom_Corner].y = myShape.k1*myShape.corners[ShapeCorners::Right_Bottom_Corner].x + c;

	myShape.corners[ShapeCorners::Right_Up_Corner] = cv::Point(mousePosX, mousePosY);

	ReCenter(indexOfShape);
}

void Shape::changeLeftBottomCorner(int indexOfShape, int mousePosX, int mousePosY)
{
	MyShape& myShape = myShapes[indexOfShape];
	double c1, c2, c;
	if (myShape.k1 == -1)
	{
		myShapes[indexOfShape].corners[ShapeCorners::Left_Bottom_Corner] = cv::Point(mousePosX, mousePosY);
		myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner].x = mousePosX;
		myShapes[indexOfShape].corners[ShapeCorners::Right_Bottom_Corner].y = mousePosY;
		return;
	}

	if (myShape.k2 == -1)
	{
		cout << 1 << endl;

	}

	c1 = myShape.corners[ShapeCorners::Right_Up_Corner].y - myShape.k1 * myShape.corners[ShapeCorners::Right_Up_Corner].x;
	c2 = myShape.corners[ShapeCorners::Right_Up_Corner].y - myShape.k2 * myShape.corners[ShapeCorners::Right_Up_Corner].x;
	c = mousePosY - myShape.k2 * mousePosX;

	myShape.corners[ShapeCorners::Right_Bottom_Corner].x = (c - c1) / (myShape.k1 - myShape.k2);
	myShape.corners[ShapeCorners::Right_Bottom_Corner].y = myShape.k2*myShape.corners[ShapeCorners::Right_Bottom_Corner].x + c;

	c = mousePosY - myShape.k1*mousePosX;

	myShape.corners[ShapeCorners::Left_Up_Corner].x = (c - c2) / (myShape.k2 - myShape.k1);
	myShape.corners[ShapeCorners::Left_Up_Corner].y = myShape.k1*myShape.corners[ShapeCorners::Left_Up_Corner].x + c;

	myShape.corners[ShapeCorners::Left_Bottom_Corner] = cv::Point(mousePosX, mousePosY);

	ReCenter(indexOfShape);
}

void Shape::changeRightBottomCorner(int indexOfShape, int mousePosX, int mousePosY)
{
	MyShape& myShape = myShapes[indexOfShape];
	double c1, c2, c;
	if (myShape.k1 == -1)
	{
		myShapes[indexOfShape].corners[ShapeCorners::Right_Bottom_Corner] = cv::Point(mousePosX, mousePosY);
		if (myShapes[indexOfShape].corners[ShapeCorners::Right_Up_Corner].x != -1)
			myShapes[indexOfShape].corners[ShapeCorners::Right_Up_Corner].x = mousePosX;
		if (myShapes[indexOfShape].corners[ShapeCorners::Left_Bottom_Corner].y != -1)
			myShapes[indexOfShape].corners[ShapeCorners::Left_Bottom_Corner].y = mousePosY;
		return;
	}

	if (myShape.k2 == -1)
	{
		cout << 1 << endl;

	}

	c1 = myShape.corners[ShapeCorners::Left_Up_Corner].y - myShape.k1 * myShape.corners[ShapeCorners::Left_Up_Corner].x;
	c2 = myShape.corners[ShapeCorners::Left_Up_Corner].y - myShape.k2 * myShape.corners[ShapeCorners::Left_Up_Corner].x;
	c = mousePosY - myShape.k2 * mousePosX;

	if (myShapes[indexOfShape].corners[ShapeCorners::Right_Up_Corner].x != -1)
	{
		myShape.corners[ShapeCorners::Right_Up_Corner].x = (c - c1) / (myShape.k1 - myShape.k2);
		myShape.corners[ShapeCorners::Right_Up_Corner].y = myShape.k2*myShape.corners[ShapeCorners::Right_Up_Corner].x + c;
	}

	c = mousePosY - myShape.k1*mousePosX;

	if (myShapes[indexOfShape].corners[ShapeCorners::Left_Bottom_Corner].y != -1)
	{
		myShape.corners[ShapeCorners::Left_Bottom_Corner].x = (c - c2) / (myShape.k2 - myShape.k1);
		myShape.corners[ShapeCorners::Left_Bottom_Corner].y = myShape.k1*myShape.corners[ShapeCorners::Left_Bottom_Corner].x + c;
	}
	myShape.corners[ShapeCorners::Right_Bottom_Corner] = cv::Point(mousePosX, mousePosY);

	ReCenter(indexOfShape);
}

void Shape::ReCenter(int indexOfShape)
{
	myShapes[indexOfShape].corners[ShapeCorners::Center].x = (myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner].x + myShapes[indexOfShape].corners[ShapeCorners::Right_Bottom_Corner].x) / 2;
	myShapes[indexOfShape].corners[ShapeCorners::Center].y = (myShapes[indexOfShape].corners[ShapeCorners::Left_Up_Corner].y + myShapes[indexOfShape].corners[ShapeCorners::Right_Bottom_Corner].y) / 2;
}

