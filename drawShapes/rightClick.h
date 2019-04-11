#pragma onc
#ifndef _RIGHTCLICK_H_
#define _RIGHTCLICK_H_

#include "data.h"
#include "shapes.h"

class RightClick
{
public:
	RightClick();
	~RightClick();

	bool initialize();

	void rightclicked(cv::Mat& m, int indexOfShape, int mousePosX, int mousePosY, bool firstTime);
private:
	void displayRightClick(cv::Mat& m);

private:
	const int rightClickBoxWidth = 70;
	const int rightClickBoxSectionHeight = 25;
	const int rightClickBoxSectionNum = 6;
	const int rightClickBoxHeight = rightClickBoxSectionHeight * rightClickBoxSectionNum;
	const int rightClickBoxEdgeThickness = 1;
	const int rightClickBoxTextOffsetWidth = 3;
	const int rightClickBoxTextOffsetHeight = 2;
	vector<string> sectionName = { "Delete", "Paste", "Rotate", "Color", "Outline", "Fill" };
	int rightClickBoxLeftUpCornerPosX = 0;
	int rightClickBoxLeftUpCornerPosY = 0;
};

#endif