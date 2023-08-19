#pragma once
#include"Tools.h"
#include"Gate.h"
#include"Line.h"
#include"test.h"
#include"Interface.h"
#include"SaveAndRead.h"
#include"globals.h"
#include"mainMenu.h"

//创建所有图标
void createOptions()
{
    setpos(option_right_limit + 4, 2);
    cout << "工具栏";
    //每个控件在y方向占3格，所以RECT的第二个和第四个参数每加一行就加3就行
    options.push_back(Option("AND", { option_right_limit,4,short(option_right_limit + 13),6 }));
    options.push_back(Option("OR", { option_right_limit,7,short(option_right_limit + 13),9 }));
    options.push_back(Option("NOT", { option_right_limit,10,short(option_right_limit + 13),12 }));
    options.push_back(Option("XOR", { option_right_limit,13,short(option_right_limit + 13),15 }));
    options.push_back(Option("NAND", { option_right_limit,16,short(option_right_limit + 13),18 }));
    options.push_back(Option("NOR", { option_right_limit,19,short(option_right_limit + 13),21 }));
    options.push_back(Option("电线", { option_right_limit,22,short(option_right_limit + 13),24 }));
    options.push_back(Option("保存", { option_right_limit,28,short(option_right_limit + 13),30 }));
    options.push_back(Option("读取", { option_right_limit,31,short(option_right_limit + 13),33 }));
    options.push_back(Option("返回主菜单", { option_right_limit,34,short(option_right_limit + 13),36 }));
}

void mainMenu();
//显示自由设计画板界面
void freeDesign()
{
    //EnableVTMode();//启用虚拟终端模式,否则在exe中输出DEC转义字符集时会出现乱码
    //fullScreen();
    drawInterface();
    createOptions();
    drawOptions();
    while (1)
    {
        highLightOptions();
        /*setpos(0, 2);
        cout << "提示：请在右端工具栏内选择控件或操作（单击鼠标左键）";*/
        displayMessage("提示：请在右端工具栏内选择控件或操作（单击鼠标左键）");
        string opt = chooseOption();
        if (opt != "unknown")
        {
            if (opt == "电线")
            {
                drawLineByMouse();
            }
            else if (opt == "AND")
            {
                drawGateByMouse("AND");
            }
            else if (opt == "OR")
            {
                drawGateByMouse("OR");
            }
            else if (opt == "NOT")
            {
                drawGateByMouse("NOT");
            }
            else if (opt == "NAND")
            {
                drawGateByMouse("NAND");
            }
            else if (opt == "NOR")
            {
                drawGateByMouse("NOR");
            }
            else if (opt == "XOR")
            {
                drawGateByMouse("XOR");
            }
            else if (opt == "保存")
            {
                saveDrawingArea();
            }
            else if (opt == "读取")
            {
                readDrawingArea();
            }
            else if (opt == "返回主菜单")
            {
                options.clear();
                gates.clear();
                lines.clear();
                clearScreen();
                mainMenu();
            }
        }
    }
}
