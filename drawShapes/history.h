#pragma once
#ifndef _HISTORY_H_
#define _HISTORY_H_

#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;

class History
{
public:
    History();
    ~History();

    bool initialize(cv::Mat m);
    void addHistory(cv::Mat m);
    cv::Mat getPrevHistory();
    cv::Mat getNextHistory();
private:
    vector<cv::Mat> history;                        
    int currentIndex;
};

#endif // !_HISTORY_H_
