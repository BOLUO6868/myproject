#pragma once
#include"Tools.h"
#include"Option.h"
#include"globals.h"
//画线字符(不用启用虚拟机模式也不会出现乱码）
//"┌","┐","└","┘","─","│","┼"




//绘制整个操作界面的边界等
void drawInterface()
{
    setpos(0, drawing_area_top_limit + 1);
    cout << "绘图区";
    //绘图区上边界
    setpos(0, drawing_area_top_limit);
    for (int i = 0; i < drawing_area_right_limit; i++)
    {
        //cout << "\033(0q";//特殊字符集中的小横线
        cout << "─";
    }
    //cout << "\033(0k";
    cout << "┐"; 

    //绘图区右边界
    for (int i = drawing_area_top_limit + 1; i < drawing_area_bottom_limit; i++)
    {
        setpos(drawing_area_right_limit, i);
        //cout << "\033(0x";//特殊字符集中的小竖线
        cout << "│";
    }

    ////绘图区下边界
    setpos(0, drawing_area_bottom_limit);
    for (int i = 0; i < drawing_area_right_limit; i++)
    {
        //cout << "\033(0q";//特殊字符集中的小横线
        cout << "─";
    }
    //cout << "\033(0j";
    cout << "┘";
}

//清空信息窗口原有信息，并打印提示信息message
void displayMessage(string message)
{
    static int lineNumber = 0;
    //消息区已满，清空原始消息
    if (lineNumber > message_area_bottom_limit - message_area_top_limit)
    {
        for (int i = message_area_top_limit; i <= message_area_bottom_limit; i++)
        {
            setpos(message_area_left_limit, i);
            for (int j = message_area_left_limit; j <= message_area_right_limit; j++)
            {
                cout << " ";
            }
        }
        lineNumber = 0;
        setpos(message_area_left_limit, lineNumber);
        cout << message;
    }
    //打印新的消息
    setpos(message_area_left_limit, lineNumber);
    cout << message;
    lineNumber++;
}