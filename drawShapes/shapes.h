#pragma once
#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;

void drawBox(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawBox(cv::Mat& img, cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4, cv::Scalar color, int thickness);
void drawCircle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawRegularTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawRightTriangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawLine(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawPolygon(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawEllipse(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawRoundedRectangle(cv::Mat& img, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawDottedLine(cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);
void drawDottedRectangle(cv::Mat& m, cv::Point startPos, cv::Point endPos, cv::Scalar color, int thickness = 1);

#endif;
