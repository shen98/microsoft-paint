#include "stdafx.h"
#include "paint.h"

Paint::Paint()
{

}

Paint::~Paint()
{

}

bool Paint::initialize(cv::Mat& m, int height, int width)
{
    m = cv::Mat(height, width, CV_8UC3, white);

    return true;
}

void Paint::resize(cv::Mat& m, cv::Point startPos, cv::Point endPos, int thickLevel)
{
    m = m(cv::Range(std::min(startPos.y, endPos.y) + thickLevel, std::max(startPos.y, endPos.y)),
        cv::Range(std::min(startPos.x, endPos.x) + thickLevel, std::max(startPos.x, endPos.x)));
    //cv::resize(m, m, cv::Size(abs(endPos.x - startPos.x), abs(endPos.y - startPos.y)));
}
