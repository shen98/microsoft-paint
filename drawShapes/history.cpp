#include "stdafx.h"
#include "history.h"

History::History()
{
    history = vector<cv::Mat>();
    currentIndex = 0;
}

History::~History()
{

}

bool History::initialize(cv::Mat m)
{
    history.push_back(m);

    return true;
}

void History::addHistory(cv::Mat m)
{
    currentIndex++;
    history.push_back(m);
}

cv::Mat History::getNextHistory()
{
    if (history.size() > currentIndex + 1) currentIndex++;
    return history[currentIndex];
}

cv::Mat History::getPrevHistory()
{
    if (currentIndex > 0) currentIndex--;
    return history[currentIndex];
}


