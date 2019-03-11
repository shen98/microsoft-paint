#include "stdafx.h"
#include "window.h"

void my_mouse_calback(int event, int x, int y, int flags, void* param)
{
    Window* w = reinterpret_cast<Window*>(param);
    w->onMouse(event, x, y, flags, param);
}

Window::Window()
{
    drawingColor = CV_RGB(255, 255, 255);
}

Window::~Window()
{
    cv::destroyAllWindows();
}

bool Window::initialize(int height, int width)
{
    windowMat = cv::Mat(height, width, CV_8UC3);

    windowMat = cv::Scalar::all(0);

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

    result = menu->initialize();
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

    menu->initialMenu(windowMat, width);


    cv::Mat a;
    windowMat.copyTo(a);
    result = history->initialize(a);
    if (!result)
    {
        cout << "Fail to initialize history" << endl;
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
    cv::namedWindow("1");
    cv::moveWindow("1", 20, 20);
    cv::setMouseCallback("1", my_mouse_calback, this);

    for (;;)
    {
        windowMat.copyTo(temp);
        menu->selectShape(temp, mouseX, mouseY);
        menu->selectColor(temp, mouseX, mouseY);
        if (menu->getButtonState()[Buttons::rectangle] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawBox(temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::line] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawLine(temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::ellipse] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawEllipse(temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::roundedRectangle] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawRoundedRectangle(temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::triangle] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawRegularTriangle(temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::polygon] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawPolygon(temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::thickness])
        {
            menu->selectThickness(temp, mouseX, mouseY, thichLevel);
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

        int key = cv::waitKey(50);
        if (key == 27)      //Esc key
        {
            if (!menu->startDrawing()) break;
            initPoints();
            menu->changeDrawingState(false);
            menu->changeSelectState(false);
        }   
        else if (key == 13 && menu->getButtonState()[Buttons::polygon])         //enter key
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawPolygon(windowMat, endPos, initPos, drawingColor);
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
        menu->changeDisplayColorNum(x, y);
        if (menu->changeColor(windowMat, x, y) != cv::Scalar(-1, -1, -1))
        {
            drawingColor = menu->changeColor(windowMat, x, y);
            menu->changeState(g_prevSelectedShape);
            break;
        }
        if (menu->getSelectThickness())
        {
            int thick = menu->changeThickness(x, y);
            if (thick == -1) break;
            else
            {
                thichLevel = 1 + thick * 2;
            }
            menu->changeSelectThickness(false);
            if (g_prevSelectedShape != -1)
            {
                menu->changeState(g_prevSelectedShape);
                endPos.x = 0; endPos.y = 0;
            }
            else menu->changeState(Buttons::cancel);
        }
        else if (y >= menu->getMenuHeight() && menu->startDrawing())
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
            if (button >= Buttons::rectangle && button <= Buttons::polygon) g_prevSelectedShape = button;
            if (button == Buttons::thickness) menu->changeSelectThickness(true);
        }

    }
    break;
    case cv::EVENT_LBUTTONUP:
    {
        if (y >= menu->getMenuHeight() && menu->startDrawing())
        {
            if(endPos.x == 0 && endPos.y == 0) break;
            if (menu->getButtonState()[Buttons::polygon])
            {
                shapes->drawPolygon(windowMat, startPos, endPos, drawingColor, thichLevel);
                addToHistory(windowMat);
                startPos = endPos;
                return;
            }
            if (menu->getButtonState()[Buttons::rectangle]) shapes->drawBox(windowMat, startPos, endPos, drawingColor, thichLevel);
            if (menu->getButtonState()[Buttons::line]) shapes->drawLine(windowMat, startPos, endPos, drawingColor, thichLevel);
            else if (menu->getButtonState()[Buttons::ellipse]) shapes->drawEllipse(windowMat, startPos, endPos, drawingColor, thichLevel);
            else if (menu->getButtonState()[Buttons::roundedRectangle]) shapes->drawRoundedRectangle(windowMat, startPos, endPos, drawingColor, thichLevel);
            else if (menu->getButtonState()[Buttons::triangle]) shapes->drawRegularTriangle(windowMat, startPos, endPos, drawingColor, thichLevel);
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

