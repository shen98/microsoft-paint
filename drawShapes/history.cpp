#include "stdafx.h"
#include "history.h"

History::History()
{
    history = vector<Event>();
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

void History::addHistory(cv::Mat m, int indexOfShape)
{
    currentIndex++;
    history.push_back(Event(m, indexOfShape));
    
    historyCopy = history;
}

Event History::getNextHistory()
{
    if (history.size() > currentIndex + 1) currentIndex++;
    return history[currentIndex];
}

Event History::getPrevHistory()
{
    if (currentIndex > 0)
    {
        currentIndex--;
    }
    cout << currentIndex << endl;
    return history[currentIndex];
}


void History::copy()
{
    historyCopy = history;
}
