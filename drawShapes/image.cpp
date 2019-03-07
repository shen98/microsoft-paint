#include "stdafx.h"
#include "image.h"

Image::Image()
{

}

Image::~Image()
{

}

bool Image::loadImage(wstring fileName, cv::Mat& m)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    std::string converted_str = converter.to_bytes(fileName);

    cv::Mat img = cv::imread(converted_str);
    cv::Rect pos;
    if (img.rows > initialImageSize || img.cols > initialImageSize)
    {
         pos = reScale(img, true);
    }
    if (img.empty()) return false;
    img.copyTo(m(cv::Range(0, img.rows), cv::Range(0, img.cols)));

    pos = cv::Rect(cv::Point(0, 0), cv::Point(pos.height, pos.width));
    cout << pos.tl() << " " << pos.br() << endl;
    myImage image(img, pos);
    images.push_back(image);

    return true;
}

cv::Rect Image::reScale(cv::Mat& img, bool fixedRatio, double width, double height)
{
    cv::Rect r;
    if (fixedRatio)
    {
        if (img.rows < img.cols)
        {
            cv::resize(img, img, cv::Size(width, img.rows / (img.cols / width)));
            r.width = width;
            r.height = img.rows / (img.cols / width);
        }
        else
        {
            cv::resize(img, img, cv::Size(img.cols / (img.rows / width), width));
            r.width = img.cols / (img.rows / width);
            r.height = width;
        }
    }

    return r;
}

bool Image::selectImage(int mousePosX, int mousePosY)
{

    return true;
}
