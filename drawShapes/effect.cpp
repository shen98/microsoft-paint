#include "stdafx.h"	
#include "effect.h"

void selectedEffect(cv::Mat& m, cv::Point leftUpCorner, cv::Point rightBottomCorner,
	double alpha, cv::Scalar effectColor, cv::Scalar shapeColor)
{
	cv::Mat temp;
	m.copyTo(temp);

	cv::rectangle(temp, cv::Rect(leftUpCorner, rightBottomCorner), effectColor, -1);

	cv::addWeighted(temp, alpha, m, 1.0 - alpha, 0.0, m);

	cv::rectangle(m, cv::Rect(leftUpCorner, rightBottomCorner), shapeColor);
}
