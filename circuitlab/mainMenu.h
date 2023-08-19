#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"Option.h"
#include"globals.h"
#include"freeDesign.h"
#include"simplify.h"
#include"printLetter.h"

//打印CIRCUITLAB大标题
void print_title()
{
    /* print_L(2,2);
     print_I(9, 2);
     print_R(16, 2);
     print_T(23, 2);
     print_U(30, 2);
     print_B(37, 2);
     print_A(170, 40);
     print_C(30, 30);*/

    int t = getLargestConsoleWidth() / 2 - 34;
    int p = 9;
    print_C(t, p);
    print_I(t + 7, p);
    print_R(t + 14, p);
    print_C(t + 21, p);
    print_U(t + 28, p);
    print_I(t + 35, p);
    print_T(t + 42, p);
    print_L(t + 49, p);
    print_A(t + 56, p);
    print_B(t + 64, p);

    setColorAttr(40);
}

void createMenuOptions()
{
    //每个控件在y方向占3格，所以RECT的第二个和第四个参数每加一行就加3就行
    options.push_back(Option("自由设计画板", { menu_option_left_limit,menu_option_top_limit, menu_option_left_limit + 18,menu_option_top_limit + 2 }));
    options.push_back(Option("逻辑表达式化简", { menu_option_left_limit,menu_option_top_limit + 3, menu_option_left_limit + 18,menu_option_top_limit + 5 }));
    options.push_back(Option("退出", { menu_option_left_limit,menu_option_top_limit + 6, menu_option_left_limit + 18,menu_option_top_limit + 8 }));
}

void freeDesign();//先声明一下，不然下面会找不到标识符
void simplify();
//显示主菜单界面
void mainMenu()
{
    print_title();
    createMenuOptions();
    drawOptions();
    while (1)
    {
        highLightOptions();
        string opt = chooseOption();
        if (opt != "unknown")
        {
            if (opt == "自由设计画板")
            {
                options.clear();
                clearScreen();
                freeDesign();
                break;
            }
            else if (opt == "逻辑表达式化简")
            {
                options.clear();
                clearScreen();
                simplify();
                break;
            }
            else if (opt == "退出")
            {
                exit(0);
            }
        }
    }
    
}