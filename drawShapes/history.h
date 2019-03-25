#pragma once
#ifndef _HISTORY_H_
#define _HISTORY_H_

#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;

#define SHAPE 0             //indicate which type of event 
#define BRUSH 1

struct Event
{
    cv::Mat m;
    int indexOfShape;

    Event(cv::Mat m, int indexOfShape = -1) : m(m), indexOfShape(indexOfShape)
    {}
};

class History
{
public:
    History();
    ~History();

    bool initialize(cv::Mat m);
    void addHistory(cv::Mat m, int indexOfShape = -1);
    Event getPrevHistory();
    Event getNextHistory();

private:
    void copy();

private:
    vector<Event> history;
    vector<Event> historyCopy;
    int currentIndex;
};

#endif // !_HISTORY_H_
