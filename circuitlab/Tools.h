#pragma once
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <ctime>
#include<iostream>
#include<stdlib.h>
#include <conio.h>
#include<iomanip>
#include<vector>
#include <Windows.h>
#include <codecvt>
#include<cstdlib>
#include<string>

using namespace std;
#ifndef KEY_DOWN
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#endif
#define clean 0x2
#define box 0x4
#define full 0x1


//简中版Windows下控制台默认代码页为936(GBK), 如果直接显示UTF8内容会乱码, 此时需要用以下代码将代码页修改到兼容UTF-8的代码页.
//首先如果你使用msvc开发应用, 必须确保启用编译器的utf8模式
//好像这个程序里没什么用，用了反而乱码
void setConsoleUTF8() 
{
    SetConsoleOutputCP(CP_UTF8);
    #pragma warning (disable: 4996)
    std::locale utf8(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
    std::wcout.imbue(utf8);
    #pragma warning (default: 4996)
}

//启用虚拟终端模式
//启用虚拟终端模式后可以在Windows中使用在Linux/Mac中可用的转义字符序列控制终端行为
//经测试虚拟终端功能仅支持win10及更新的系统.
bool EnableVTMode()
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}

//获取当前窗口宽度
int getConsoleWidth()
{
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outputHandle, &info);
    return info.srWindow.Right + 1;
}
//获取当前窗口高度
int getConsoleHeight()
{
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outputHandle, &info);
    return info.srWindow.Bottom + 1;
}
int getLargestConsoleWidth()
{
    HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //获得控制台句柄
    COORD NewSize = GetLargestConsoleWindowSize(HOUT);//获得控制台最大坐标，坐标以字符数为单位
    return NewSize.X;
}

int getLargestConsoleHeight()
{
    HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //获得控制台句柄
    COORD NewSize = GetLargestConsoleWindowSize(HOUT);//获得控制台最大坐标，坐标以字符数为单位
    return NewSize.Y;
}

//修改字符和背景颜色
//且只会修改setColorAttr(int attr)后的字符和背景颜色，原来的不会改，这个很好
//修改字符颜色建议使用VT模式完成
//下面代码首先需要启用VT模式
const char ESC = '\033';
const int ATTR_NORMAL = 0; // 传入此常量可将当前颜色设置恢复为预设值
//前景色
enum ConsoleForeground : int
{
    FG_BLACK = 30,
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    FG_WHITE = 37,
    FG_DEFAULT = 39,
    FG_LIGHT_BLACK = 90,
    FG_LIGHT_RED = 91,
    FG_LIGHT_GREEN = 92,
    FG_LIGHT_YELLOW = 93,
    FG_LIGHT_BLUE = 94,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_CYAN = 96,
    FG_LIGHT_WHITE = 97
};
// 背景色
enum ConsoleBackground : int
{
    BG_BLACK = 40,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_YELLOW = 43,
    BG_BLUE = 44,
    BG_MAGENTA = 45,
    BG_CYAN = 46,
    BG_WHITE = 47,
    BG_DEFAULT = 49,
    BG_LIGHT_BLACK = 100,
    BG_LIGHT_RED = 101,
    BG_LIGHT_GREEN = 102,
    BG_LIGHT_YELLOW = 103,
    BG_LIGHT_BLUE = 104,
    BG_LIGHT_MAGENTA = 105,
    BG_LIGHT_CYAN = 106,
    BG_LIGHT_WHITE = 107
};
void setColorAttr(int attr)
{
    std::cout << ESC << "[" << attr << "m";
}

//调用后可以隐藏光标，等待输入时就不会一直有个东西在闪 
void HideCursor()        //调用后可以隐藏光标，等待输入时就不会一直有个东西在闪 
{
    CONSOLE_CURSOR_INFO information = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &information);
}

//调用后可以显示光标，等待输入时就会一直有个东西在闪 
void ShowCursor() 
{
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void fullScreen()//全屏
{
    HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //获得控制台句柄
    COORD NewSize = GetLargestConsoleWindowSize(HOUT);//获得控制台最大坐标，坐标以字符数为单位
    NewSize.X -= 1;
    NewSize.Y -= 1;    //可以不加，不加时显示滚动条
    SetConsoleScreenBufferSize(HOUT, NewSize); //设置控制台缓冲区大小

    SMALL_RECT DisplayArea = { 0,0,0,0 };
    DisplayArea.Right = NewSize.X;
    DisplayArea.Bottom = NewSize.Y;
    SetConsoleWindowInfo(HOUT, TRUE, &DisplayArea);    //设置控制台大小

    //控制台已经最大化，但是初始位置不在屏幕左上角，添加如下代码
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);    //窗体最大化
}

//调用后无法最小化和调整控制台窗口大小（右上角的两个按钮消失，只剩下关闭按钮）
void canNotChangeConsoleSize()
{
    HWND hwnd = GetConsoleWindow();//获取窗口句柄
    LONG_PTR sty = GetWindowLongPtrA(hwnd, GWL_STYLE);//获取窗口样式
    sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX;//去除可变化大小（&是与运算，~是取反运算）
    SetWindowLongPtrA(hwnd, GWL_STYLE, sty);//应用窗体样式
}

void setpos(int i, int j)            //控制光标位置， 列， 行，横着数i格，数着数j格 
{
    //COORD是window.h中提前定义好的结构体，里面有X和Y（注意大写）两个成员，都是short类型 
    COORD pos;
    pos.X = i;
    pos.Y = j;
    //以上三行也可以简写为 COORD pos = { i,j };    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    //HANDLE是句柄数据类型（类似于int），该数据类型用于接收系统窗口等的唯一标识（句柄），通过该标识来控制这些窗口
    //GetStdHandle()是windows.h中获取句柄的函数，返回一个句柄 
    //STD_OUTPUT_HANDLE是windows.h提前定义好的 标准输出句柄 
    // SetConsoleCursorPosition()是windows.h提前定义好的设置控制台光标位置的函数，参数是输出窗口的句柄和COORD类型的坐标 
    SetConsoleCursorPosition(h, pos);
}

//更高效的清屏函数
void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
        (TCHAR)' ',     // Character to write to the buffer
        dwConSize,       // Number of cells to write
        coordScreen,     // Coordinates of first cell
        &cCharsWritten))// Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
        csbi.wAttributes, // Character attributes to use
        dwConSize,        // Number of cells to set attribute
        coordScreen,      // Coordinates of first cell
        &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}

//将光标位置设置到当前鼠标所指位置，并返回当前光标位置COORD结构体
COORD setCursorPosToMousePos()
{
    HWND hwnd = GetForegroundWindow();
    POINT pt;
    GetCursorPos(&pt);
    //把窗口坐标系（原点在屏幕左上角）转换为客户区坐标系（原点在黑框框左上角）
    //如果调用成功，会将POINT结构体pt中记录的坐标转换为新的坐标
    // 所以一定要先GetCursorPos(&pt);再ScreenToClient(hwnd, &pt);否则没有用
    ScreenToClient(hwnd, &pt);
    // 输出句柄
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //经过测试的完美数据（一个字符宽度为8单位，高度为16单位，减1是避免光标位置与鼠标重叠，不好看）(只适用于本电脑，换了分辨率就不行）
    //int fontsize_x = 8;
    //int fontsize_y = 16;
    // 
    //通用公式，每行（列）像素值个数/每行（列）字符个数
    int fontsize_x = GetSystemMetrics(SM_CXFULLSCREEN) / getConsoleWidth();
    int fontsize_y = GetSystemMetrics(SM_CYFULLSCREEN) / getConsoleHeight();
    COORD pos;
    pos.X = pt.x / fontsize_x;
    pos.Y = pt.y / fontsize_y;
    SetConsoleCursorPosition(outputHandle, pos);
    return pos;
}

COORD getCursorPos()
{
    HWND hwnd = GetForegroundWindow();
    POINT pt;
    GetCursorPos(&pt);
    //把窗口坐标系（原点在屏幕左上角）转换为客户区坐标系（原点在黑框框左上角）
    //如果调用成功，会将POINT结构体pt中记录的坐标转换为新的坐标
    // 所以一定要先GetCursorPos(&pt);再ScreenToClient(hwnd, &pt);否则没有用
    ScreenToClient(hwnd, &pt);
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int fontsize_x = GetSystemMetrics(SM_CXFULLSCREEN) / getConsoleWidth();
    int fontsize_y = GetSystemMetrics(SM_CYFULLSCREEN) / getConsoleHeight();
    COORD pos;
    pos.X = pt.x / fontsize_x;
    pos.Y = pt.y / fontsize_y;
    SetConsoleCursorPosition(outputHandle, pos);
    return pos;
}

//移除控制台的快速编辑模式，使得无法用鼠标左键选择某个光标或区域，
//防止鼠标左键单击事件 与之冲突 导致鼠标左键点击判断无效
void disableQuickEditMode()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
    mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
    mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, mode);
}

//隐藏控制台窗口的最大化按钮和窗口调整大小功能
void DisableMaximizeAndResize() 
{
    HWND consoleWindow = GetConsoleWindow();
    DWORD style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

//隐藏控制台窗口边框
void HideConsoleWindowBorders()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG_PTR style = GetWindowLongPtr(consoleWindow, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX | WS_BORDER);
    SetWindowLongPtr(consoleWindow, GWL_STYLE, style);
}

//禁止移动窗口位置(好像没什么用)
void DisableMaximizeAndMove() 
{
    HWND consoleWindow = GetConsoleWindow();
    LONG_PTR style = GetWindowLongPtr(consoleWindow, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
    SetWindowLongPtr(consoleWindow, GWL_STYLE, style);
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}