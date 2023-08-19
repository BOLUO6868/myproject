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


//���а�Windows�¿���̨Ĭ�ϴ���ҳΪ936(GBK), ���ֱ����ʾUTF8���ݻ�����, ��ʱ��Ҫ�����´��뽫����ҳ�޸ĵ�����UTF-8�Ĵ���ҳ.
//���������ʹ��msvc����Ӧ��, ����ȷ�����ñ�������utf8ģʽ
//�������������ûʲô�ã����˷�������
void setConsoleUTF8() 
{
    SetConsoleOutputCP(CP_UTF8);
    #pragma warning (disable: 4996)
    std::locale utf8(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
    std::wcout.imbue(utf8);
    #pragma warning (default: 4996)
}

//���������ն�ģʽ
//���������ն�ģʽ�������Windows��ʹ����Linux/Mac�п��õ�ת���ַ����п����ն���Ϊ
//�����������ն˹��ܽ�֧��win10�����µ�ϵͳ.
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

//��ȡ��ǰ���ڿ��
int getConsoleWidth()
{
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outputHandle, &info);
    return info.srWindow.Right + 1;
}
//��ȡ��ǰ���ڸ߶�
int getConsoleHeight()
{
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outputHandle, &info);
    return info.srWindow.Bottom + 1;
}
int getLargestConsoleWidth()
{
    HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //��ÿ���̨���
    COORD NewSize = GetLargestConsoleWindowSize(HOUT);//��ÿ���̨������꣬�������ַ���Ϊ��λ
    return NewSize.X;
}

int getLargestConsoleHeight()
{
    HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //��ÿ���̨���
    COORD NewSize = GetLargestConsoleWindowSize(HOUT);//��ÿ���̨������꣬�������ַ���Ϊ��λ
    return NewSize.Y;
}

//�޸��ַ��ͱ�����ɫ
//��ֻ���޸�setColorAttr(int attr)����ַ��ͱ�����ɫ��ԭ���Ĳ���ģ�����ܺ�
//�޸��ַ���ɫ����ʹ��VTģʽ���
//�������������Ҫ����VTģʽ
const char ESC = '\033';
const int ATTR_NORMAL = 0; // ����˳����ɽ���ǰ��ɫ���ûָ�ΪԤ��ֵ
//ǰ��ɫ
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
// ����ɫ
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

//���ú�������ع�꣬�ȴ�����ʱ�Ͳ���һֱ�и��������� 
void HideCursor()        //���ú�������ع�꣬�ȴ�����ʱ�Ͳ���һֱ�и��������� 
{
    CONSOLE_CURSOR_INFO information = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &information);
}

//���ú������ʾ��꣬�ȴ�����ʱ�ͻ�һֱ�и��������� 
void ShowCursor() 
{
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void fullScreen()//ȫ��
{
    HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //��ÿ���̨���
    COORD NewSize = GetLargestConsoleWindowSize(HOUT);//��ÿ���̨������꣬�������ַ���Ϊ��λ
    NewSize.X -= 1;
    NewSize.Y -= 1;    //���Բ��ӣ�����ʱ��ʾ������
    SetConsoleScreenBufferSize(HOUT, NewSize); //���ÿ���̨��������С

    SMALL_RECT DisplayArea = { 0,0,0,0 };
    DisplayArea.Right = NewSize.X;
    DisplayArea.Bottom = NewSize.Y;
    SetConsoleWindowInfo(HOUT, TRUE, &DisplayArea);    //���ÿ���̨��С

    //����̨�Ѿ���󻯣����ǳ�ʼλ�ò�����Ļ���Ͻǣ�������´���
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);    //�������
}

//���ú��޷���С���͵�������̨���ڴ�С�����Ͻǵ�������ť��ʧ��ֻʣ�¹رհ�ť��
void canNotChangeConsoleSize()
{
    HWND hwnd = GetConsoleWindow();//��ȡ���ھ��
    LONG_PTR sty = GetWindowLongPtrA(hwnd, GWL_STYLE);//��ȡ������ʽ
    sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX;//ȥ���ɱ仯��С��&�������㣬~��ȡ�����㣩
    SetWindowLongPtrA(hwnd, GWL_STYLE, sty);//Ӧ�ô�����ʽ
}

void setpos(int i, int j)            //���ƹ��λ�ã� �У� �У�������i��������j�� 
{
    //COORD��window.h����ǰ����õĽṹ�壬������X��Y��ע���д��������Ա������short���� 
    COORD pos;
    pos.X = i;
    pos.Y = j;
    //��������Ҳ���Լ�дΪ COORD pos = { i,j };    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    //HANDLE�Ǿ���������ͣ�������int�����������������ڽ���ϵͳ���ڵȵ�Ψһ��ʶ���������ͨ���ñ�ʶ��������Щ����
    //GetStdHandle()��windows.h�л�ȡ����ĺ���������һ����� 
    //STD_OUTPUT_HANDLE��windows.h��ǰ����õ� ��׼������ 
    // SetConsoleCursorPosition()��windows.h��ǰ����õ����ÿ���̨���λ�õĺ�����������������ڵľ����COORD���͵����� 
    SetConsoleCursorPosition(h, pos);
}

//����Ч����������
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

//�����λ�����õ���ǰ�����ָλ�ã������ص�ǰ���λ��COORD�ṹ��
COORD setCursorPosToMousePos()
{
    HWND hwnd = GetForegroundWindow();
    POINT pt;
    GetCursorPos(&pt);
    //�Ѵ�������ϵ��ԭ������Ļ���Ͻǣ�ת��Ϊ�ͻ�������ϵ��ԭ���ںڿ�����Ͻǣ�
    //������óɹ����ὫPOINT�ṹ��pt�м�¼������ת��Ϊ�µ�����
    // ����һ��Ҫ��GetCursorPos(&pt);��ScreenToClient(hwnd, &pt);����û����
    ScreenToClient(hwnd, &pt);
    // ������
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //�������Ե��������ݣ�һ���ַ����Ϊ8��λ���߶�Ϊ16��λ����1�Ǳ�����λ��������ص������ÿ���(ֻ�����ڱ����ԣ����˷ֱ��ʾͲ��У�
    //int fontsize_x = 8;
    //int fontsize_y = 16;
    // 
    //ͨ�ù�ʽ��ÿ�У��У�����ֵ����/ÿ�У��У��ַ�����
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
    //�Ѵ�������ϵ��ԭ������Ļ���Ͻǣ�ת��Ϊ�ͻ�������ϵ��ԭ���ںڿ�����Ͻǣ�
    //������óɹ����ὫPOINT�ṹ��pt�м�¼������ת��Ϊ�µ�����
    // ����һ��Ҫ��GetCursorPos(&pt);��ScreenToClient(hwnd, &pt);����û����
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

//�Ƴ�����̨�Ŀ��ٱ༭ģʽ��ʹ���޷���������ѡ��ĳ����������
//��ֹ�����������¼� ��֮��ͻ ��������������ж���Ч
void disableQuickEditMode()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
    mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
    mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, mode);
}

//���ؿ���̨���ڵ���󻯰�ť�ʹ��ڵ�����С����
void DisableMaximizeAndResize() 
{
    HWND consoleWindow = GetConsoleWindow();
    DWORD style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

//���ؿ���̨���ڱ߿�
void HideConsoleWindowBorders()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG_PTR style = GetWindowLongPtr(consoleWindow, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX | WS_BORDER);
    SetWindowLongPtr(consoleWindow, GWL_STYLE, style);
}

//��ֹ�ƶ�����λ��(����ûʲô��)
void DisableMaximizeAndMove() 
{
    HWND consoleWindow = GetConsoleWindow();
    LONG_PTR style = GetWindowLongPtr(consoleWindow, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
    SetWindowLongPtr(consoleWindow, GWL_STYLE, style);
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}