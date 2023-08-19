#pragma once
#include"fun.h"
#include"totable.h"
#include"mainMenu.h"

using namespace std;

void createSimplifyOptions()
{
    //ÿ���ؼ���y����ռ3������RECT�ĵڶ����͵��ĸ�����ÿ��һ�оͼ�3����
    options.push_back(Option("ģʽ1��ֱ������Ϊ1����", { 1,1,50,3 }));
    options.push_back(Option("ģʽ2����ֵ����ʽ����", { 1,4,50,6 }));
    options.push_back(Option("ģʽ3���߼����ʽ��ʽ����", { 1,7,50,9 }));
    options.push_back(Option("ģʽ4���ɱ��ʽ����ֵ��", { 1,10,50,12 }));
    options.push_back(Option("�������˵�", { 1,13,50,15 }));
}

void mainMenu();//������һ�£���Ȼ�����Ҳ�����ʶ��

//��ʾ���򹤾߽���
void simplify()
{
    createSimplifyOptions();
    drawOptions();
    while (1)
    {
        highLightOptions();
        totable project1;
        //setpos(0, 0);
        //cout << "��ģʽһ��ֱ������Ϊ1����  ģʽ������ֵ����ʽ���룩" << endl;
        string opt = chooseOption();
        if (opt != "unknown")
        {
            if (opt == "�������˵�")
            {
                options.clear();
                clearScreen();
                mainMenu();
            }
            else if (opt == "ģʽ1��ֱ������Ϊ1����")
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
            else if (opt == "ģʽ2����ֵ����ʽ����")
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
            else if (opt == "ģʽ3���߼����ʽ��ʽ����")
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
            else if (opt == "ģʽ4���ɱ��ʽ����ֵ��")
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


