#pragma once
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <tchar.h>
#include <codecvt>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;

const double initialImageSize = 100.0;

struct myImage
{
    cv::Mat img;                //info of this image
    cv::Rect pos;               //position of this image

    myImage(cv::Mat img, cv::Rect pos)
    {
        img = img;
        pos = pos;
    }
};

class Image
{
public:
    Image();
    ~Image();

    bool loadImage(wstring fileName, cv::Mat& m);
    cv::Rect reScale(cv::Mat& img, bool fixedRatio, double width = initialImageSize, double height = initialImageSize);

    bool selectImage(int mousePosX, int mousePosY);

private:
    vector<myImage> images;
};

#endif