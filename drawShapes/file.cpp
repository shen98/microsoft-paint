#include "stdafx.h"
#include "file.h"

File::File()
{

}

File::~File()
{

}

void File::initializeFile(cv::Mat& m)
{
	drawBox(m, cv::Point(buttonWidthOffset, buttonHeightOffset),
		cv::Point(buttonWidthOffset + buttonWidth, buttonHeightOffset + buttonHeight), black);
	cv::putText(m, "File", cv::Point(buttonWidthOffset + buttonTextWidthOffset, buttonHeightOffset + buttonHeight- buttonTextHeightOffset),
		cv::FONT_HERSHEY_SIMPLEX, 0.6, black, 1, cv::LINE_AA);
}
