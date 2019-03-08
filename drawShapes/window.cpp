#include "stdafx.h"
#include "window.h"

void my_mouse_calback(int event, int x, int y, int flags, void* param)
{
    Window* w = reinterpret_cast<Window*>(param);
    w->onMouse(event, x, y, flags, param);
}

Window::Window(int height, int width)
{
    g_Width = width;
    g_Height = height;
}

Window::~Window()
{
    cv::destroyAllWindows();
}

bool Window::initialize()
{
    windowMat = cv::Mat(g_Height, g_Width, CV_8UC3);
    bool result;

    history = new History();
    if (!history)
    {
        cout << "Cannot create new History object." << endl;
        return false;
    }

    image = new Image();
    if (!image)
    {
        cout << "Cannot create new Image object." << endl;
        return false;
    }

    menu = new Menu();
    if (!menu)
    {
        cout << "Cannot create new Menu object." << endl;
        return false;
    }

    result = menu->initialize(windowMat,g_Width);
    if (!result)
    {
        cout << "Fail to initialize menu." << endl;
        return false;
    }

    shapes = new Shapes();
    if (!shapes)
    {
        return false;
    }

    result = shapes->initialShapes();
    if (!result)
    {
        return false;
    }

    result = initialWindow();
    if (!result)
    {
        cout << "Fail to initialize window." << endl;
        return false;
    }


    return true;
}

bool Window::initialWindow()
{
    windowMat.copyTo(temp);

    windowMat = cv::Scalar::all(0);

    cv::namedWindow("1");
    cv::moveWindow("1", 20, 20);
    cv::setMouseCallback("1", my_mouse_calback, this);

    menu->initialMenu(windowMat, g_Width);
    cv::Mat a;
    windowMat.copyTo(a);
    bool result = history->initialize(a);
    if (!result)
    {
        cout << "Fail to initialize history" << endl;
        return false;
    }
    for (;;)
    {
        windowMat.copyTo(temp);
        menu->selectShape(temp, mouseX, mouseY);
        if (menu->getButtonState()[Buttons::rectangle] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawBox(temp, startPos, endPos, CV_RGB(255,0,0));
        }
        else if (menu->getButtonState()[Buttons::line] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawLine(temp, startPos, endPos, CV_RGB(255, 0, 0));
        }
        else if (menu->getButtonState()[Buttons::ellipse] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawEllipse(temp, startPos, endPos, CV_RGB(255, 0, 0));
        }
        else if (menu->getButtonState()[Buttons::roundedRectangle] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawRoundedRectangle(temp, startPos, endPos, CV_RGB(255, 0, 0));
        }
        else if (menu->getButtonState()[Buttons::triangle] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawRegularTriangle(temp, startPos, endPos, CV_RGB(255, 0, 0));
        }
        else if (menu->getButtonState()[Buttons::polygon] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawPolygon(temp, startPos, endPos, CV_RGB(255, 0, 0));
        }
        else if (menu->getButtonState()[Buttons::import])
        {
            menu->changeState(Buttons::cancel);
            wstring fileName = selectFile();
            image->loadImage(fileName, windowMat);
            cv::Mat a;
            windowMat.copyTo(a);
            addToHistory(a);
        }
        else if (menu->getButtonState()[Buttons::undo])
        {
            menu->changeState(Buttons::cancel);
            history->getPrevHistory().copyTo(windowMat);
        }
        else if (menu->getButtonState()[Buttons::redo])
        {
            menu->changeState(Buttons::cancel);
            history->getNextHistory().copyTo(windowMat);
        }

        cv::imshow("1", temp);

        int key = cv::waitKey(5);
        if (key == 27)      //Esc key
        {
            if (!menu->startDrawing()) break;
            initPoints();
            menu->changeDrawingState(false);
            menu->changeSelectState(false);
        }   
        else if (key == 13 && menu->getButtonState()[Buttons::polygon])         //enter key
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawPolygon(windowMat, endPos, initPos, CV_RGB(255, 0, 0));
            addToHistory(windowMat);
        }
    }

    return true;
}

void Window::onMouse(int event, int x, int y, int flags, void* param)
{
    switch (event)
    {
    case cv::EVENT_MOUSEMOVE:
    {
        mouseX = x; mouseY = y;
        if (y < menu->getMenuHeight() || !menu->startDrawing() || !menu->getSelectedFirst()) break;
        endPos.x = x; endPos.y = y;
    }
    break;
    case cv::EVENT_LBUTTONDOWN:
    {
        if (y >= menu->getMenuHeight() && menu->startDrawing())
        {
            if(menu->getButtonState()[Buttons::polygon] && (initPos.x == 0 && initPos.y == 0))
            {
                initPos.x = x; initPos.y = y;
            }
            menu->changeDrawingState(true);
            if (!menu->getSelectedFirst())
            {
                startPos.x = x; startPos.y = y;
                menu->changeSelectState(true);
            }
        }
        else if(y <= menu->getMenuHeight())
        {
            int button = menu->getMouseClick(x, y);
            if (button >= Buttons::rectangle && button <= Buttons::triangle)                    //add selected shape effect
            {
                menu->selectedShape(windowMat, button);
            }
            if(button != -1) menu->changeState(button);
        }

    }
    break;
    case cv::EVENT_LBUTTONUP:
    {
        if (y >= menu->getMenuHeight() && menu->startDrawing())
        {
            if (menu->getButtonState()[Buttons::polygon])
            {
                shapes->drawPolygon(windowMat, startPos, endPos, CV_RGB(255, 0, 0));
                addToHistory(windowMat);
                startPos = endPos;
                return;
            }
            if (menu->getButtonState()[Buttons::rectangle]) shapes->drawBox(windowMat, startPos, endPos, CV_RGB(255, 0, 0));
            if (menu->getButtonState()[Buttons::line]) shapes->drawLine(windowMat, startPos, endPos, CV_RGB(255, 0, 0));
            else if (menu->getButtonState()[Buttons::ellipse]) shapes->drawEllipse(windowMat, startPos, endPos, CV_RGB(255, 0, 0));
            else if (menu->getButtonState()[Buttons::roundedRectangle]) shapes->drawRoundedRectangle(windowMat, startPos, endPos, CV_RGB(255, 0, 0));
            else if (menu->getButtonState()[Buttons::triangle]) shapes->drawRegularTriangle(windowMat, startPos, endPos, CV_RGB(255, 0, 0));
            cv::Mat a;
            windowMat.copyTo(a);
            addToHistory(a);
            menu->changeDrawingState(false);
            menu->changeSelectState(false);
            endPos.x = 0; endPos.y = 0;
        }
    }
    }
}

void Window::initPoints()
{
    startPos.x = 0;
    startPos.y = 0;
    endPos.x = 0;
    endPos.y = 0;
}

wstring Window::selectFile()
{
    wchar_t filename[MAX_PATH];
    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = _T(".png\0*.png\0,jpg\0*.jpg*\0");
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = _T("Select a File, yo!");
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        return filename;
    }
    else
    {
        return NULL;
    }
}

void Window::addToHistory(cv::Mat m)
{
    history->addHistory(m);
}

