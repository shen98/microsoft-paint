#pragma once

#include <opencv2/opencv.hpp>

const int g_MenuHeight = 130;
const int g_MenuOffsetWidth = 5;
const int g_MenuOffsetHeight = 8;
const int g_ButtonSize = 40;
const int g_ButtonNum = 20;
const int iconHeight = 20;
const int textSize = 10;
const int shapeButtonWidth = 20;
const int shapeButtonHeight = 16;
const int shapeOffsetWidth = 2;
const int shapeOffsetHeight = 3;
const int g_Width = 1200;
const int g_Height = 600;
const int windowOffsetWidth = 5;
const int windowOffsetHeight = 10;
const cv::Scalar selectedBlockColor = CV_RGB(0, 191, 255);
const cv::Scalar black = CV_RGB(0, 0, 0);
const cv::Scalar white = CV_RGB(255, 255, 255);
const cv::Scalar defaultMenuColor = CV_RGB(230, 230, 250);

enum Section
{
    clipboard = 0,
    image = 100,
    tool = 250,
    brush = 320,
    shape = 380,
    thick = 600,
    color = 660,
    other = 1058
};