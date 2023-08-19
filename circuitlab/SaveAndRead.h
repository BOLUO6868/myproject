#pragma once
#include <iostream>
#include<cstdlib> 
#include"globals.h"
#include<fstream>
#include<string>
using namespace std;

//将C:\Users\86198\Desktop变为C:\\Users\\86198\\Desktop并返回（即将一个\变为\\）
string decoratePath(string path)
{
    string res;
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == '\\')
        {
            res += '\\';
        }
        res += path[i];
    }
    return res;
}


//可以指定路径，但路径中不能有空格 
//若该路径下的最终文件夹已存在，会自动打印提示信息 
string createFolder(string folderPath = "C:\\Users\\86198\\Desktop\\黑框框测试文件夹")
{
    string command;
    command = "mkdir " + folderPath;
    system(command.c_str());
    return folderPath;
}

void saveGates(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\黑框框测试文件夹\\gates保存测试文档.dat")
{
    ofstream f;
    f.open(folderPathPlusProjectName + "\\gates保存测试文档.dat", ios::binary | ios::out);
    if (!f.is_open())
    {
        displayMessage("文件打开失败！请检查路径或项目名称是否输入错误");
    }
    else
    {
        for (int i = 0; i < gates.size(); i++)
        {
            f.write((const char*)&gates[i], sizeof(gates[i]));
        }
        f.close();
    }
}
void saveLines(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\黑框框测试文件夹\\lines保存测试文档.dat")
{
    ofstream f(folderPathPlusProjectName + "\\lines保存测试文档.dat", ios::binary | ios::out);
    //f.open("C:\\Users\\86198\\Desktop\\黑框框测试文件夹\\lines保存测试文档.txt", ios::binary | ios::in | ios::out);
    if (!f.is_open())
    {
        displayMessage("文件打开失败！请检查路径或项目名称是否输入错误");
    }
    else
    {
        for (int i = 0; i < lines.size(); i++)
        {
            f.write((const char*)&lines[i], sizeof(lines[i]));
        }
        f.close();
    }
}
void saveDrawingArea()
{
    displayMessage("请输入项目名称：");
    string projectName;
    ShowCursor();
    getline(cin, projectName);
    displayMessage("请输入保存路径：");
    string folderPath;
    getline(cin, folderPath);
    folderPath = decoratePath(folderPath);
    string folderPathPlusProjectName = folderPath + "\\" + projectName + ".dat";
    createFolder(folderPathPlusProjectName);
    saveGates(folderPathPlusProjectName);
    saveLines(folderPathPlusProjectName);

    displayMessage("保存成功！");
    HideCursor();
}

void readGates(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\黑框框测试文件夹\\gates保存测试文档.dat")
{
    ifstream f;
    Gate g;
    f.open(folderPathPlusProjectName + "\\gates保存测试文档.dat", ios::binary | ios::in);
    if (!f.is_open())
    {
        displayMessage("文件打开失败！请检查路径或项目名称是否输入错误");
    }
    else
    {
        while (!f.eof())
        {
            f.read((char*)&g, sizeof(g));
            gates.push_back(g);
            g.show();
        }
        f.close();
        displayMessage("Gates读取成功！");
    }
    
}
void readLines(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\黑框框测试文件夹\\lines保存测试文档.dat")
{
    ifstream f;
    Line l;
    f.open(folderPathPlusProjectName + "\\lines保存测试文档.dat", ios::binary | ios::in);
    if (!f.is_open())
    {
        displayMessage("文件打开失败！请检查路径或项目名称是否输入错误");
    }
    else
    {
        while (!f.eof())
        {
            f.read((char*)&l, sizeof(l));
            lines.push_back(l);
            l.show();
        }
        updateLines();
        f.close();
        displayMessage("Lines读取成功！");
    }
}
void readDrawingArea()
{
    displayMessage("请输入项目名称(eg: project01)：");
    string projectName;
    ShowCursor();
    getline(cin, projectName);
    displayMessage("请输入保存路径(eg：C:\\Users\\86198\\Desktop)：");
    string folderPath;
    getline(cin, folderPath);
    folderPath = decoratePath(folderPath);
    string folderPathPlusProjectName = folderPath + "\\" + projectName + ".dat";
    //先清除掉原来的gate和line，但要把窗口和option画回来
    gates.clear();
    lines.clear();
    clearScreen();
    drawOptions();
    drawInterface();
    //再读取存档
    readGates(folderPathPlusProjectName);
    readLines(folderPathPlusProjectName);
    HideCursor();
}