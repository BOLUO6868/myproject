#pragma once
#include"Tools.h"
#include"Gate.h"
#include"Line.h"
#include"Option.h"
#include"SaveAndRead.h"
#include<string>
#include"freeDesign.h"
//设置字体颜色test
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
//不改变字符的前提下重置背景色和前景色test
void test02()
{
    cout << "\033(0lqqqqqqqqqqk" << endl;
    cout << "\033(0x " << left << setw(9) << "哈哈哈哈" << "\033(0x" << endl;
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

////画组件选项，鼠标扫过highlight test
////有bug，待修复，只有第一个控件被highlight，且范围不对
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
////测试文件夹和文件操作
//void test05()
//{
//   /* string path;
//    cout << "请输入文件名：";
//    getline(cin, path);
//    createFolder(path);*/
//    createFolder();
//}