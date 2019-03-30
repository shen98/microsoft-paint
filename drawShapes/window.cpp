#include "stdafx.h"
#include "window.h"

void my_mouse_calback(int event, int x, int y, int flags, void* param)
{
    Window* w = reinterpret_cast<Window*>(param);
    w->onMouse(event, x, y, flags, param);
}

Window::Window()
{
    drawingColor = black;
}

Window::~Window()
{
    cv::destroyAllWindows();
}

bool Window::initialize(int height, int width)
{
    backgroundMat = cv::Mat(height, width, CV_8UC3);

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

    result = menu->initialize(menuMat, width);
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

    paint = new Paint();
    if (!paint)
    {
        cout << "Cannot create paint object." << endl;
        return false;
    }

    result = paint->initialize(windowMat, height - g_MenuHeight - 2 * windowOffsetHeight, width - 2 * windowOffsetWidth);
    if (!result)
    {
        cout << "Cannot initialize paint." << endl;
        return false;
    }

   /* cv::Mat a;
    windowMat.copyTo(a);
    result = history->initialize(a);
    if (!result)
    {
        cout << "Fail to initialize history" << endl;
        return false;
    }*/

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
        menuMat.copyTo(backgroundMat(cv::Range(0, g_MenuHeight), cv::Range(0, g_Width)));
        windowMat.copyTo(backgroundMat(cv::Range(g_MenuHeight + windowOffsetHeight, windowMat.rows + g_MenuHeight + windowOffsetHeight), cv::Range(windowOffsetWidth, windowMat.cols + windowOffsetWidth)));
        backgroundMat.copyTo(temp);
        paint->paint(windowMat);
        paint->selectShape(temp, mouseX, mouseY);
        menu->selectColor(temp, mouseX, mouseY);
        paint->checkMousePosOnCorner(temp, mouseX, mouseY);
        
        if (menu->getButtonState()[Buttons::selectBox] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) shapes->drawDottedRectangle(temp, startPos, endPos, black, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::rectangle] && menu->startDrawing())
        {
            //if (endPos.x != 0 && endPos.y != 0) shapes->drawBox(temp, startPos, endPos, drawingColor, thichLevel);
            if (endPos.x != 0 && endPos.y != 0) paint->drawTempShape(RECTANGLE, temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::line] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) paint->drawTempShape(LINE, temp, startPos, endPos, drawingColor, thichLevel);
        }
        else if (menu->getButtonState()[Buttons::ellipse] && menu->startDrawing())
        {
            if (endPos.x != 0 && endPos.y != 0) paint->drawTempShape(CIRCLE, temp, startPos, endPos, drawingColor, thichLevel);
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
            history->addHistory(a);
        }
        else if (menu->getButtonState()[Buttons::undo])
        {

        }
        else if (menu->getButtonState()[Buttons::redo])
        {
            menu->changeState(Buttons::cancel);
            history->getNextHistory().m.copyTo(windowMat);
        }
        else if (menu->getButtonState()[Buttons::selectBrush])
        {
            menu->selectBrush(temp, mouseX, mouseY);
        }

        cv::imshow("1", temp);

        int key = cv::waitKey(10);
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
            history->addHistory(windowMat, changeShape);
        }
        else if (key == 13 && selectedSelectBox)
        {
            backgroundMat = cv::Mat(g_Height, g_Width, CV_8UC3);
            paint->resize(windowMat, startPos, endPos, thichLevel);
            endPos.x = 0; endPos.y = 0;
            selectedSelectBox = false;
        }
        else if (key == 13 && changeShape != -1)
        {
            if(selectedShapes) paint->finishDrawingShape(changeShape, true);
        }
        else if(key == 26)                                                          //Ctrl + z undo
        {
            /*Event e = history->getPrevHistory();
            e.m.copyTo(windowMat);
            if (e.indexOfShape != -1)
            {
                menu->changeShapeStatus(e.indexOfShape, false);
                menu->finishDrawingShape(e.indexOfShape, false);
            }
            menu->changeState(g_prevSelectedShape);*/
        }
        else if (key == 25)                                                         //Ctrl + y redo
        {
            /*Event e = history->getNextHistory();
            e.m.copyTo(windowMat);
            if (e.indexOfShape != -1)
            {
                menu->changeShapeStatus(e.indexOfShape, true);
            }
            menu->changeState(g_prevSelectedShape);*/
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
        if (paint->selectedRotate() && changeShapeCorner)
        {
            paint->rotateShape(windowMat, changeShape, x, y);
        }
        if (changeShapeCorner)
        {
            paint->changeShapeCorner(changeShape, x, y);
            break;
        }
        if (startDrawWithBrush)
        {
            paint->drawWithBrush(windowMat, startPos, cv::Point(x, y), brushType, drawingColor, thichLevel);
            startPos.x = x; startPos.y = y;
        }
        mouseX = x; mouseY = y;
        if (y < menu->getMenuHeight() || !menu->startDrawing() || !menu->getSelectedFirst() || selectedSelectBox) break;
        endPos.x = x; endPos.y = y;
    }
    break;
    case cv::EVENT_LBUTTONDOWN:
    {
        cv::Point p = paint->checkMousePosOnCorner(temp, x, y);
        if (p != cv::Point(-1, -1))
        {
            startPos = p;
            menu->changeState(Buttons::rectangle);
            menu->changeDrawingState(true);
            changeShape = paint->getSelectedShapeIndex(p);
            changeShapeCorner = true;
            selectedShapes = true;
            break;
        }
        cv::Scalar c = menu->changeDisplayColorNum(menuMat, x, y);
        if (c != cv::Scalar(-1, -1, -1))
        {
            drawingColor = c;
            if(selectedShapes) paint->changeSelectedShapeColor(changeShape, drawingColor);
            menu->changeState(g_prevSelectedShape);
            break;
        }
        else if (menu->changeColor(menuMat, x, y) != cv::Scalar(-1, -1, -1))
        {
            drawingColor = menu->changeColor(menuMat, x, y);
            if(selectedShapes) paint->changeSelectedShapeColor(changeShape, drawingColor);
            menu->changeState(g_prevSelectedShape);
            break;
        }
        else if (menu->getSelectThickness())
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
            if (drawWithBrush)
            {
                startPos.x = x; startPos.y = y;
                startDrawWithBrush = true;
                break;
            }
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
        else if (menu->getSelectBrush() && menu->getButtonState()[Buttons::selectBrush])
        {
            int type = menu->changeBrush(menuMat, x, y);
            if (type != -1)
            {
                brushType = type;
                drawWithBrush = true;
            }
            menu->changeState(Buttons::cancel);
            menu->changeDrawingState(true);
            menu->changeSelectBrush(false);
            selectedShapes = false;
            break;
        }
        else if(y <= menu->getMenuHeight())
        {
            int button = menu->getMouseClick(x, y);
            if (button >= Buttons::rectangle && button <= Buttons::triangle)                    //add selected shape effect
            {
                paint->selectedShape(menuMat, button - Buttons::rectangle);
                selectedShapes = true;
            }
            if(button != -1) menu->changeState(button);
            if (button != Buttons::selectBrush) drawWithBrush = false;
            if (button >= Buttons::normalBrush && button <= Buttons::polygon) g_prevSelectedShape = button;
            if (button == Buttons::thickness) menu->changeSelectThickness(true);
            else if (button == Buttons::selectBrush) menu->changeSelectBrush(true);
        }
    }
    break;
    case cv::EVENT_LBUTTONUP:
    {
        if (changeShapeCorner)
        {
            paint->changeShapeStatus(changeShape, true);
            //changeShape = -1;
            changeShapeCorner = false;
            paint->changeSelectedStatus(-1);
            break;
        }
        if (startDrawWithBrush)
        {
            startDrawWithBrush = !startDrawWithBrush;
            break;
        }
        if (y >= menu->getMenuHeight() && menu->startDrawing())
        {
            if(endPos.x == 0 && endPos.y == 0) break;
            changeShape++;
            startPos = cv::Point(startPos.x - windowOffsetWidth, startPos.y - g_MenuHeight - windowOffsetHeight);
            endPos = cv::Point(endPos.x - windowOffsetWidth, endPos.y - g_MenuHeight - windowOffsetHeight);
            if (menu->getButtonState()[Buttons::polygon])
            {
                shapes->drawPolygon(windowMat, startPos, endPos, drawingColor, thichLevel);
                //history->addHistory(windowMat, changeShape);
                startPos = endPos;
                return;
            }
            if (menu->getButtonState()[Buttons::rectangle]) paint->drawTempShape(RECTANGLE, windowMat, startPos, endPos, drawingColor, thichLevel, true);
            else if (menu->getButtonState()[Buttons::line]) paint->drawTempShape(LINE, windowMat, startPos, endPos, drawingColor, thichLevel, true);
            else if (menu->getButtonState()[Buttons::ellipse]) paint->drawTempShape(CIRCLE, windowMat, startPos, endPos, drawingColor, thichLevel, true);
            else if (menu->getButtonState()[Buttons::roundedRectangle]) shapes->drawRoundedRectangle(windowMat, startPos, endPos, drawingColor, thichLevel);
            else if (menu->getButtonState()[Buttons::triangle]) shapes->drawRegularTriangle(windowMat, startPos, endPos, drawingColor, thichLevel);
            else if (menu->getButtonState()[Buttons::selectBox])
            {
                shapes->drawDottedRectangle(windowMat, startPos, endPos, drawingColor, thichLevel);
                selectedSelectBox = true;
                menu->changeState(Buttons::cancel);
                menu->changeDrawingState(false);
                menu->changeSelectState(false);
                break;
            }
            cv::Mat a;
            windowMat.copyTo(a);
            //history->addHistory(a, changeShape);
            menu->changeState(g_prevSelectedShape);
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