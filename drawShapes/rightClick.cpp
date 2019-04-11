#include "stdafx.h"
#include "rightClick.h"

RightClick::RightClick()
{

}

RightClick::~RightClick()
{

}

bool RightClick::initialize()
{
	return true;
}

void RightClick::rightclicked(cv::Mat& m, int indexOfShape, int mousePosX, int mousePosY)
{
	displayRightClick(m, mousePosX, mousePosY);
}

void RightClick::displayRightClick(cv::Mat& m, int mousePosX, int mousePosY)
{

}
