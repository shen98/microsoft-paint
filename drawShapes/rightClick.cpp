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

void RightClick::rightclicked(cv::Mat& m, int indexOfShape, int mousePosX, int mousePosY, bool firstTime)
{
	if (firstTime)
	{
		rightClickBoxLeftUpCornerPosX = mousePosX;
		rightClickBoxLeftUpCornerPosY = mousePosY;
	}
	displayRightClick(m);
}

void RightClick::displayRightClick(cv::Mat& m)
{
	drawBox(m, cv::Point(rightClickBoxLeftUpCornerPosX, rightClickBoxLeftUpCornerPosY), 
		cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth, rightClickBoxLeftUpCornerPosY + rightClickBoxHeight), 
		black, rightClickBoxEdgeThickness);
	
	for (int i = 0; i < rightClickBoxSectionNum; ++i)
	{
		drawBox(m, cv::Point(rightClickBoxLeftUpCornerPosX, rightClickBoxLeftUpCornerPosY + i * rightClickBoxSectionHeight),
			cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth, rightClickBoxLeftUpCornerPosY + (i + 1) * rightClickBoxSectionHeight),
			black, rightClickBoxEdgeThickness);
		cv::putText(m, sectionName[i], cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxTextOffsetWidth, rightClickBoxLeftUpCornerPosY + i * rightClickBoxSectionHeight + rightClickBoxSectionHeight * 3 / 4),
			cv::FONT_HERSHEY_SIMPLEX, 0.6, black, 1, cv::LINE_AA);
	}

}
