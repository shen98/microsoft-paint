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
	selectSection(m, mousePosX, mousePosY);
}

int RightClick::selectedRightClickSection(Shape* shape, int indexOfShape, int mousePosX, int mousePosY)
{
	if (mousePosX < rightClickBoxLeftUpCornerPosX || mousePosX > rightClickBoxLeftUpCornerPosX + rightClickBoxWidth
		|| mousePosY < rightClickBoxLeftUpCornerPosY || mousePosY > rightClickBoxLeftUpCornerPosY + rightClickBoxHeight) return -1;
	int index = (mousePosY - rightClickBoxLeftUpCornerPosY) / rightClickBoxSectionHeight;
	
	switch (index)
	{
	case RightClickSection::RC_Delete:
	{
		shape->deleteShape(indexOfShape);
		return RightClickSection::RC_Delete;
	}
	case RightClickSection::RC_Paste:
	{
		break;
	}
	case RightClickSection::RC_Rotate:
	{
		shape->rotateShape(indexOfShape, 90);
		return RightClickSection::RC_Rotate;
	}
	case RightClickSection::RC_Color:
	{
		break;
	}
	case RightClickSection::RC_Outline:
	{
		break;
	}
	case RightClickSection::RC_Fill:
	{
		break;
	}
	default:
		break;
	}
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

void RightClick::selectSection(cv::Mat& m, int mousePosX, int mousePosY)
{
	if (mousePosX < rightClickBoxLeftUpCornerPosX || mousePosX > rightClickBoxLeftUpCornerPosX + rightClickBoxWidth
		|| mousePosY < rightClickBoxLeftUpCornerPosY || mousePosY > rightClickBoxLeftUpCornerPosY + rightClickBoxHeight) return;

	int index = (mousePosY - rightClickBoxLeftUpCornerPosY) / rightClickBoxSectionHeight;

	selectedEffect(m, cv::Point(rightClickBoxLeftUpCornerPosX, rightClickBoxLeftUpCornerPosY + index * rightClickBoxSectionHeight),
		cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth, rightClickBoxLeftUpCornerPosY + (index + 1) * rightClickBoxSectionHeight),
		0.3, CV_RGB(0, 191, 255), black);
}
