#pragma once
#include"Tools.h"
#include"Gate.h"
#include"Line.h"
#include"Option.h"
#include"SaveAndRead.h"
#include<string>
#include"freeDesign.h"
//����������ɫtest
void test01()
{
    setColorAttr(43);
    setColorAttr(32);
    cout << "hahahaha" << endl;
    setColorAttr(37);
    setColorAttr(40);
    cout << "gagag" << endl;
    system("pause");
}
//���ı��ַ���ǰ�������ñ���ɫ��ǰ��ɫtest
void test02()
{
    cout << "\033(0lqqqqqqqqqqk" << endl;
    cout << "\033(0x " << left << setw(9) << "��������" << "\033(0x" << endl;
    cout << "\033(0mqqqqqqqqqqj" << endl;
    
    while (1)
    {
        SMALL_RECT s1 = { 0,0,5,4 };
        SMALL_RECT s2 = { 6,0,11,4 };
        if (mouseInArea(s1))
        {
            highLightArea(s1);
        }
        else
        {
            resetArea(s1);
        }
        if (mouseInArea(s2))
        {
            highLightArea(s2);
        }
        else
        {
            resetArea(s2);
        }

    }
}

////�����ѡ����ɨ��highlight test
////��bug�����޸���ֻ�е�һ���ؼ���highlight���ҷ�Χ����
//void test03()
//{
//    createOptions();
//    drawOptions();
//    while (1)
//    {
//        highLightOptions();
//    }
//}
//
//void test04()
//{
//    createOptions();
//    drawOptions();
//    while (1)
//    {
//        highLightOptions();
//        string opt = chooseOption();
//        /*if (opt == "AND")
//        {
//            cout << "AND" << endl;
//        }*/
//    }
//}
//
////�����ļ��к��ļ�����
//void test05()
//{
//   /* string path;
//    cout << "�������ļ�����";
//    getline(cin, path);
//    createFolder(path);*/
//    createFolder();
//}