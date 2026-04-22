


#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <functional>
#include <vector>
#include <stack>
#include <tuple>
#include <stdlib.h>
#include <algorithm>  


HINSTANCE hInst;
HWND hWnd;
WCHAR szTitle[] = L"Graphics";
WCHAR szWindowClass[] = L"Graphics";
 
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HDC hdc;
HPEN selectionPen, drawingPen, zoomingPen;
HGDIOBJ oldPen;
HGDIOBJ oldBrush;

struct PointF
{
    float x, y;
};

float aspectRatio;
POINT pmin = { 0, 70 }, pmax;
PointF wmin = { 0, 0 }, wmax = { 1, 1 };

POINT worldToScreen(PointF p)
{
    return {
        pmin.x + (LONG)round((p.x - wmin.x) * (pmax.x - pmin.x) / (wmax.x - wmin.x)),
        pmax.y - (LONG)round((p.y - wmin.y) * (pmax.y - pmin.y) / (wmax.y - wmin.y)) };
}

PointF screenToWorld(POINT p)
{
    return {
        wmin.x + (p.x - pmin.x) * (wmax.x - wmin.x) / (pmax.x - pmin.x),
        wmin.y + (pmax.y - p.y) * (wmax.y - wmin.y) / (pmax.y - pmin.y) };
}

POINT mousePosition = { 0, 0 };

enum FigureType
{
    FigureType_LINE,
    FigureType_RECT,
    FigureType_ELLIPSE
};

struct Figure
{
    PointF start;
    PointF end;
    FigureType type;

    void draw(HDC hdc)
    {
        POINT start = worldToScreen(this->start);
        POINT end = worldToScreen(this->end);
        switch (type)
        {
        case FigureType_LINE:
        {
            MoveToEx(hdc, start.x, start.y, NULL);
            LineTo(hdc, end.x, end.y);
        }
        break;
        case FigureType_RECT:
        {
            Rectangle(hdc, start.x, start.y, end.x, end.y);
        }
        break;
        case FigureType_ELLIPSE:
        {
            Ellipse(hdc, start.x, start.y, end.x, end.y);
        }
        break;
        }
    }
};

BOOL isDrawing = false;
BOOL isZooming = false;
std::pair<POINT, POINT> selection;
std::pair<POINT, POINT> zoom;
auto zoomHistory = std::stack<std::pair<PointF, PointF>>();
FigureType selectedFigureType = FigureType_LINE;
std::vector<Figure> figures;

struct Button
{
    Button(int left, int top, int right, int bottom, std::function<void(Button&)> delegate, LPCWSTR txt) : text(txt)
    {
        box = RECT{ left, top, right, bottom };
        on_click = delegate;
    }

    RECT box;
    LPCWSTR text;

    std::function<void(Button&)> on_click;
    bool contains(POINT p)
    {
        return p.x <= box.right && p.y <= box.bottom && p.x >= box.left && p.y >= box.top;
    }

    auto bounds() const
    {
        return std::make_tuple(box.left, box.top, box.right, box.bottom);
    }

    void draw(HDC hdc)
    {
        std::apply(Rectangle, std::tuple_cat(std::make_tuple(hdc), std::move(bounds())));
        DrawText(hdc, text, -1, &box, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
};

std::vector<Button> btns = {
    {10, 10, 160, 60, [](Button& btn)
     {
         if (zoomHistory.size() == 0)
             return;
         std::tie(wmax, wmin) = zoomHistory.top();
         zoomHistory.pop();
         InvalidateRect(hWnd, NULL, true);
     },
     L"Отмена зума"},
    {170, 10, 320, 60, [](Button& btn)
     {
         selectedFigureType = FigureType_LINE;
     },
     L"Линия"},
    {330, 10, 480, 60, [](Button& btn)
     {
         selectedFigureType = FigureType_RECT;
     },
     L"Прямоугольник"},
    {490, 10, 640, 60, [](Button& btn)
     {
         selectedFigureType = FigureType_ELLIPSE;
     },
     L"Эллипс"} };

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(hInstance, nullptr);

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        selectionPen = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
        drawingPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
        zoomingPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);

        HPEN interfacePen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
        oldPen = SelectObject(hdc, interfacePen);

        HBRUSH backgroundBrush = CreateSolidBrush(RGB(222, 222, 222));
        oldBrush = SelectObject(hdc, backgroundBrush);
        Rectangle(hdc, pmin.x, pmin.y, pmax.x, pmax.y);
        SelectObject(hdc, oldBrush);
        DeleteObject(backgroundBrush);

        oldBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        for (auto figure : figures)
        {
            figure.draw(hdc);
        }

        HBRUSH interfaceBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, interfaceBrush);
        Rectangle(hdc, 0, 0, pmax.x, pmin.y);

        for (auto btn : btns)
            btn.draw(hdc);

        SelectObject(hdc, oldBrush);
        DeleteObject(interfaceBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(interfacePen);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_SIZE:
    {
        pmax = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        aspectRatio = (float)(pmax.x - pmin.x) / (float)(pmax.y - pmin.y);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if (mousePosition.y < pmin.y)
        {
            for (auto& btn : btns)
            {
                if (btn.contains(mousePosition))
                {
                    btn.on_click(btn);
                    break;
                }
            }
            break;
        }

        if (!isDrawing && !isZooming)
        {
            selection.first = mousePosition;
            isDrawing = true;

            hdc = GetDC(hWnd);
            SetROP2(hdc, R2_NOTXORPEN);
            oldPen = SelectObject(hdc, selectionPen);
            MoveToEx(hdc, selection.first.x, selection.first.y, NULL);
            LineTo(hdc, selection.second.x, selection.second.y);
        }
    }
    break;
    case WM_RBUTTONDOWN:
    {
        if (mousePosition.y < pmin.y)
            break;

        if (!isZooming && !isDrawing)
        {
            zoom.first = mousePosition;
            isZooming = true;

            hdc = GetDC(hWnd);
            SetROP2(hdc, R2_NOTXORPEN);
            oldPen = SelectObject(hdc, zoomingPen);
            Rectangle(hdc, zoom.first.x, zoom.first.y, zoom.second.x, zoom.second.y);
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        if (isDrawing)
        {
            MoveToEx(hdc, selection.first.x, selection.first.y, NULL);
            LineTo(hdc, selection.second.x, selection.second.y);

            isDrawing = false;

            SetROP2(hdc, R2_COPYPEN);

            oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));

            PointF worldTopLeft = screenToWorld(selection.first);
            PointF worldBottomRight = screenToWorld(selection.second);
            Figure f = { worldTopLeft, worldBottomRight, selectedFigureType };
            figures.push_back(f);

            SelectObject(hdc, drawingPen);
            f.draw(hdc);
            SelectObject(hdc, oldPen);
            SelectObject(hdc, oldBrush);
            ReleaseDC(hWnd, hdc);
        }
    }
    case WM_RBUTTONUP:
{
    if (isZooming)
    {
        // Обновляем позицию мыши
        mousePosition.x = GET_X_LPARAM(lParam);
        mousePosition.y = GET_Y_LPARAM(lParam);
        
        MoveToEx(hdc, zoom.first.x, zoom.first.y, NULL);
        Rectangle(hdc, zoom.first.x, zoom.first.y, zoom.second.x, zoom.second.y);

        isZooming = false;

        SetROP2(hdc, R2_COPYPEN);

        zoomHistory.push({ wmax, wmin });

        POINT bottomLeft = { std::min(zoom.first.x, zoom.second.x), 
                             std::max(zoom.first.y, zoom.second.y) };
        POINT topRight = { std::max(zoom.first.x, zoom.second.x), 
                           std::min(zoom.first.y, zoom.second.y) };

        PointF wminNew = screenToWorld(bottomLeft);
        wmax = screenToWorld(topRight);
        wmin = wminNew;

        InvalidateRect(hWnd, NULL, true);

        SelectObject(hdc, oldPen);
        ReleaseDC(hWnd, hdc);
    }
    break; 
}
    break;
    case WM_MOUSEMOVE:
    {
        if (isDrawing)
        {
            MoveToEx(hdc, selection.first.x, selection.first.y, NULL);
            LineTo(hdc, selection.second.x, selection.second.y);
        }

        if (isZooming)
        {
            Rectangle(hdc, zoom.first.x, zoom.first.y, zoom.second.x, zoom.second.y);
        }

        mousePosition.x = GET_X_LPARAM(lParam);
        mousePosition.y = GET_Y_LPARAM(lParam);

        LONG selectionNewY = mousePosition.y;
        if (selectionNewY > pmin.y)
            selection.second = { mousePosition.x, selectionNewY };

        int sign = (((zoom.first.x - mousePosition.x) * (zoom.first.y - mousePosition.y)) < 0) ? -1 : 1;
        LONG zoomNewY = zoom.first.y - sign * (LONG)round((float)(zoom.first.x - mousePosition.x) / aspectRatio);
        if (zoomNewY > pmin.y)
            zoom.second = { mousePosition.x, zoomNewY };

        if (isDrawing)
        {
            MoveToEx(hdc, selection.first.x, selection.first.y, NULL);
            LineTo(hdc, selection.second.x, selection.second.y);
        }

        if (isZooming)
        {
            Rectangle(hdc, zoom.first.x, zoom.first.y, zoom.second.x, zoom.second.y);
        }
    }
    break;
    case WM_DESTROY:
        DeleteObject(selectionPen);
        DeleteObject(drawingPen);
        DeleteObject(zoomingPen);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}