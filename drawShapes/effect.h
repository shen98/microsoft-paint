#pragma once

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <opencv2/opencv.hpp>

void selectedEffect(cv::Mat& m, cv::Point leftUpCorner, cv::Point rightBottomCorner,
	double alpha, cv::Scalar effectColor, cv::Scalar shapeColor);

#endif