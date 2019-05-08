#pragma once

#ifndef _FILE_H_
#define _FILE_H_

#include "data.h"
#include "shapes.h"

class File
{
public:
	File();
	~File();

	void initializeFile(cv::Mat& m);
private:
	const int buttonWidth = 50;
	const int buttonHeight = 20;
	const int buttonWidthOffset = 2;
	const int buttonHeightOffset = 3;
	const int buttonTextWidthOffset = 2;
	const int buttonTextHeightOffset = 2;
};

#endif