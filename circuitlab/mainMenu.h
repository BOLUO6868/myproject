#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"Option.h"
#include"globals.h"
#include"freeDesign.h"
#include"simplify.h"
#include"printLetter.h"

//��ӡCIRCUITLAB�����
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
    //ÿ���ؼ���y����ռ3������RECT�ĵڶ����͵��ĸ�����ÿ��һ�оͼ�3����
    options.push_back(Option("������ƻ���", { menu_option_left_limit,menu_option_top_limit, menu_option_left_limit + 18,menu_option_top_limit + 2 }));
    options.push_back(Option("�߼����ʽ����", { menu_option_left_limit,menu_option_top_limit + 3, menu_option_left_limit + 18,menu_option_top_limit + 5 }));
    options.push_back(Option("�˳�", { menu_option_left_limit,menu_option_top_limit + 6, menu_option_left_limit + 18,menu_option_top_limit + 8 }));
}

void freeDesign();//������һ�£���Ȼ������Ҳ�����ʶ��
void simplify();
//��ʾ���˵�����
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
            if (opt == "������ƻ���")
            {
                options.clear();
                clearScreen();
                freeDesign();
                break;
            }
            else if (opt == "�߼����ʽ����")
            {
                options.clear();
                clearScreen();
                simplify();
                break;
            }
            else if (opt == "�˳�")
            {
                exit(0);
            }
        }
    }
    
}