#pragma once
#include"fun.h"
#include"totable.h"
#include"mainMenu.h"

using namespace std;

void createSimplifyOptions()
{
    //每个控件在y方向占3格，所以RECT的第二个和第四个参数每加一行就加3就行
    options.push_back(Option("模式1：直接输入为1的项", { 1,1,50,3 }));
    options.push_back(Option("模式2：真值表形式输入", { 1,4,50,6 }));
    options.push_back(Option("模式3：逻辑表达式形式输入", { 1,7,50,9 }));
    options.push_back(Option("模式4：由表达式得真值表", { 1,10,50,12 }));
    options.push_back(Option("返回主菜单", { 1,13,50,15 }));
}

void mainMenu();//先声明一下，不然下面找不到标识符

//显示化简工具界面
void simplify()
{
    createSimplifyOptions();
    drawOptions();
    while (1)
    {
        highLightOptions();
        totable project1;
        //setpos(0, 0);
        //cout << "（模式一：直接输入为1的数  模式二：真值表形式输入）" << endl;
        string opt = chooseOption();
        if (opt != "unknown")
        {
            if (opt == "返回主菜单")
            {
                options.clear();
                clearScreen();
                mainMenu();
            }
            else if (opt == "模式1：直接输入为1的项")
            {
                options.clear();
                clearScreen();
                bool t = project1.init1();
                if (t == false) {
                    cout << "1" << endl;
                    break;
                }
                else {
                    project1.setprime();
                    project1.minimise();
                    project1.show();
                    system("pause");
                    options.clear();
                    clearScreen();
                    simplify();
                    break;
                }
            }
            else if (opt == "模式2：真值表形式输入")
            {
                options.clear();
                clearScreen();
                bool t = project1.init2();
                if (t == false) {
                    cout << "1" << endl;
                    system("pause");
                    options.clear();
                    clearScreen();
                    simplify();
                    break;
                }
                else {
                    project1.setprime();
                    project1.minimise();
                    project1.show();
                    system("pause");
                    options.clear();
                    clearScreen();
                    simplify();
                    break;
                }
            }
            else if (opt == "模式3：逻辑表达式形式输入")
            {
                options.clear();
                clearScreen();
                bool t=project1.init3();
                if (t == false) {
                    cout << "1" << endl;
                    system("pause");
                    options.clear();
                    clearScreen();
                    simplify();
                    break;
                }
                else {
                    project1.setprime();
                    project1.minimise();
                    project1.show();
                    system("pause");
                    options.clear();
                    clearScreen();
                    simplify();
                    break;
                }
                
            }
            else if (opt == "模式4：由表达式得真值表")
            {
                options.clear();
                clearScreen();
                project1.init4();
                system("pause");
                options.clear();
                clearScreen();
                simplify();
                break;
            }
        }

    }

}


