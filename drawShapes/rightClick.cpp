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
		|| mousePosY < rightClickBoxLeftUpCornerPosY || mousePosY > rightClickBoxLeftUpCornerPosY + rightClickBoxHeight)
	{
		if (prevSectionNum == -1) return -1;
		else
		{
			if (mousePosX > rightClickBoxLeftUpCornerPosX + rightClickBoxWidth * 2 ||
				(mousePosX < rightClickBoxLeftUpCornerPosX + rightClickBoxWidth * 2 && mousePosX > rightClickBoxLeftUpCornerPosX + rightClickBoxWidth &&
					(mousePosY < rightClickBoxLeftUpCornerPosY + prevSectionNum * rightClickBoxSectionHeight || mousePosY > rightClickBoxLeftUpCornerPosY + (prevSectionNum + 4) * rightClickBoxSectionHeight)) ||
				(mousePosX < rightClickBoxLeftUpCornerPosX + rightClickBoxWidth && mousePosX > rightClickBoxLeftUpCornerPosX &&
					(mousePosY < rightClickBoxLeftUpCornerPosY || mousePosY > rightClickBoxLeftUpCornerPosY + rightClickBoxHeight)) ||
				mousePosX < rightClickBoxLeftUpCornerPosX) return -1;
		}
	}
	if (mousePosX < rightClickBoxLeftUpCornerPosX + rightClickBoxWidth && mousePosX > rightClickBoxLeftUpCornerPosX)
	{
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
	else
	{
		int index = (mousePosY - rightClickBoxLeftUpCornerPosY - prevSectionNum * rightClickBoxSectionHeight) / rightClickBoxSectionHeight;
		
		switch (prevSectionNum)
		{
		case RightClickSection::RC_Rotate:
		{
			shape->rotateShape(indexOfShape, 360 - 90 * (index + 1));
			return RightClickSection::RC_Rotate;
		}
		case RightClickSection::RC_Color:
		{
			break;
		}
		default:
			break;
		}
	}
}

void RightClick::displayRightClick(cv::Mat& m)
{
	//drawBox(m, cv::Point(rightClickBoxLeftUpCornerPosX, rightClickBoxLeftUpCornerPosY), 
	//	cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth, rightClickBoxLeftUpCornerPosY + rightClickBoxHeight), 
	//	black, rightClickBoxEdgeThickness);
	
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
	int index = -1;
	if (mousePosX < rightClickBoxLeftUpCornerPosX || mousePosX > rightClickBoxLeftUpCornerPosX + rightClickBoxWidth
		|| mousePosY < rightClickBoxLeftUpCornerPosY || mousePosY > rightClickBoxLeftUpCornerPosY + rightClickBoxHeight)
	{
		if (prevSectionNum == -1) return;
		else
		{
			if (mousePosX > rightClickBoxLeftUpCornerPosX + rightClickBoxWidth * 2 ||
				(mousePosX < rightClickBoxLeftUpCornerPosX + rightClickBoxWidth * 2 && mousePosX > rightClickBoxLeftUpCornerPosX + rightClickBoxWidth &&
				(mousePosY < rightClickBoxLeftUpCornerPosY + prevSectionNum * rightClickBoxSectionHeight || mousePosY > rightClickBoxLeftUpCornerPosY + (prevSectionNum + 4) * rightClickBoxSectionHeight)) ||
					(mousePosX < rightClickBoxLeftUpCornerPosX + rightClickBoxWidth && mousePosX > rightClickBoxLeftUpCornerPosX &&
				(mousePosY < rightClickBoxLeftUpCornerPosY || mousePosY > rightClickBoxLeftUpCornerPosY + rightClickBoxHeight)) ||
				mousePosX < rightClickBoxLeftUpCornerPosX) return;
		}
	}

	if (mousePosX < rightClickBoxLeftUpCornerPosX + rightClickBoxWidth && mousePosX > rightClickBoxLeftUpCornerPosX)
	{
		index = (mousePosY - rightClickBoxLeftUpCornerPosY) / rightClickBoxSectionHeight;

		selectedEffect(m, cv::Point(rightClickBoxLeftUpCornerPosX, rightClickBoxLeftUpCornerPosY + index * rightClickBoxSectionHeight),
			cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth, rightClickBoxLeftUpCornerPosY + (index + 1) * rightClickBoxSectionHeight),
			0.3, CV_RGB(0, 191, 255), black);

	}
	if(index == -1)	displaySectionOptions(m, prevSectionNum);
	else 	displaySectionOptions(m, index);
}

void RightClick::displaySectionOptions(cv::Mat& m, int sectionNum)
{
	if (sectionNum == RightClickSection::RC_Rotate)
	{
		//drawBox(m, cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth, rightClickBoxLeftUpCornerPosY + sectionNum* rightClickBoxSectionHeight),
		//	cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth * 2, rightClickBoxLeftUpCornerPosY + (sectionNum + 4) * rightClickBoxSectionHeight),
		//	black, rightClickBoxEdgeThickness);

		for (int i = 0; i < SectionNum::RotateNum; ++i)
		{
			drawBox(m, cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth, rightClickBoxLeftUpCornerPosY + (i + sectionNum) * rightClickBoxSectionHeight),
				cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth * 2, rightClickBoxLeftUpCornerPosY + (i + 1 + sectionNum) * rightClickBoxSectionHeight),
				black, rightClickBoxEdgeThickness);
			cv::putText(m, RotateSection[i], cv::Point(rightClickBoxLeftUpCornerPosX + rightClickBoxWidth + rightClickBoxTextOffsetWidth, 
				rightClickBoxLeftUpCornerPosY + (sectionNum + i) * rightClickBoxSectionHeight + rightClickBoxSectionHeight * 3 / 4),
				cv::FONT_HERSHEY_SIMPLEX, 0.6, black, 1, cv::LINE_AA);
		}
	}

	prevSectionNum = sectionNum;
}
