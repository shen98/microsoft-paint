#pragma once
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

	void rightclicked(cv::Mat& m, int indexOfShape, int mousePosX, int mousePosY);
private:
	void displayRightClick(cv::Mat& m, int mousePosX, int mousePosY);

private:
	const int rightClickBoxWidth = 100;
	const int rightClickBoxHeight = 200;

};

#endif