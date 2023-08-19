#pragma once
#include"Tools.h"
#include"Gate.h"
#include"Line.h"
#include"test.h"
#include"Interface.h"
#include"SaveAndRead.h"
#include"globals.h"
#include"mainMenu.h"

//��������ͼ��
void createOptions()
{
    setpos(option_right_limit + 4, 2);
    cout << "������";
    //ÿ���ؼ���y����ռ3������RECT�ĵڶ����͵��ĸ�����ÿ��һ�оͼ�3����
    options.push_back(Option("AND", { option_right_limit,4,short(option_right_limit + 13),6 }));
    options.push_back(Option("OR", { option_right_limit,7,short(option_right_limit + 13),9 }));
    options.push_back(Option("NOT", { option_right_limit,10,short(option_right_limit + 13),12 }));
    options.push_back(Option("XOR", { option_right_limit,13,short(option_right_limit + 13),15 }));
    options.push_back(Option("NAND", { option_right_limit,16,short(option_right_limit + 13),18 }));
    options.push_back(Option("NOR", { option_right_limit,19,short(option_right_limit + 13),21 }));
    options.push_back(Option("����", { option_right_limit,22,short(option_right_limit + 13),24 }));
    options.push_back(Option("����", { option_right_limit,28,short(option_right_limit + 13),30 }));
    options.push_back(Option("��ȡ", { option_right_limit,31,short(option_right_limit + 13),33 }));
    options.push_back(Option("�������˵�", { option_right_limit,34,short(option_right_limit + 13),36 }));
}

void mainMenu();
//��ʾ������ƻ������
void freeDesign()
{
    //EnableVTMode();//���������ն�ģʽ,������exe�����DECת���ַ���ʱ���������
    //fullScreen();
    drawInterface();
    createOptions();
    drawOptions();
    while (1)
    {
        highLightOptions();
        /*setpos(0, 2);
        cout << "��ʾ�������Ҷ˹�������ѡ��ؼ��������������������";*/
        displayMessage("��ʾ�������Ҷ˹�������ѡ��ؼ��������������������");
        string opt = chooseOption();
        if (opt != "unknown")
        {
            if (opt == "����")
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
            else if (opt == "����")
            {
                saveDrawingArea();
            }
            else if (opt == "��ȡ")
            {
                readDrawingArea();
            }
            else if (opt == "�������˵�")
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
