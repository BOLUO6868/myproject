#pragma once
#include <iostream>
#include<cstdlib> 
#include"globals.h"
#include<fstream>
#include<string>
using namespace std;

//��C:\Users\86198\Desktop��ΪC:\\Users\\86198\\Desktop�����أ�����һ��\��Ϊ\\��
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


//����ָ��·������·���в����пո� 
//����·���µ������ļ����Ѵ��ڣ����Զ���ӡ��ʾ��Ϣ 
string createFolder(string folderPath = "C:\\Users\\86198\\Desktop\\�ڿ������ļ���")
{
    string command;
    command = "mkdir " + folderPath;
    system(command.c_str());
    return folderPath;
}

void saveGates(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\�ڿ������ļ���\\gates��������ĵ�.dat")
{
    ofstream f;
    f.open(folderPathPlusProjectName + "\\gates��������ĵ�.dat", ios::binary | ios::out);
    if (!f.is_open())
    {
        displayMessage("�ļ���ʧ�ܣ�����·������Ŀ�����Ƿ��������");
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
void saveLines(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\�ڿ������ļ���\\lines��������ĵ�.dat")
{
    ofstream f(folderPathPlusProjectName + "\\lines��������ĵ�.dat", ios::binary | ios::out);
    //f.open("C:\\Users\\86198\\Desktop\\�ڿ������ļ���\\lines��������ĵ�.txt", ios::binary | ios::in | ios::out);
    if (!f.is_open())
    {
        displayMessage("�ļ���ʧ�ܣ�����·������Ŀ�����Ƿ��������");
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
    displayMessage("��������Ŀ���ƣ�");
    string projectName;
    ShowCursor();
    getline(cin, projectName);
    displayMessage("�����뱣��·����");
    string folderPath;
    getline(cin, folderPath);
    folderPath = decoratePath(folderPath);
    string folderPathPlusProjectName = folderPath + "\\" + projectName + ".dat";
    createFolder(folderPathPlusProjectName);
    saveGates(folderPathPlusProjectName);
    saveLines(folderPathPlusProjectName);

    displayMessage("����ɹ���");
    HideCursor();
}

void readGates(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\�ڿ������ļ���\\gates��������ĵ�.dat")
{
    ifstream f;
    Gate g;
    f.open(folderPathPlusProjectName + "\\gates��������ĵ�.dat", ios::binary | ios::in);
    if (!f.is_open())
    {
        displayMessage("�ļ���ʧ�ܣ�����·������Ŀ�����Ƿ��������");
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
        displayMessage("Gates��ȡ�ɹ���");
    }
    
}
void readLines(string folderPathPlusProjectName = "C:\\Users\\86198\\Desktop\\�ڿ������ļ���\\lines��������ĵ�.dat")
{
    ifstream f;
    Line l;
    f.open(folderPathPlusProjectName + "\\lines��������ĵ�.dat", ios::binary | ios::in);
    if (!f.is_open())
    {
        displayMessage("�ļ���ʧ�ܣ�����·������Ŀ�����Ƿ��������");
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
        displayMessage("Lines��ȡ�ɹ���");
    }
}
void readDrawingArea()
{
    displayMessage("��������Ŀ����(eg: project01)��");
    string projectName;
    ShowCursor();
    getline(cin, projectName);
    displayMessage("�����뱣��·��(eg��C:\\Users\\86198\\Desktop)��");
    string folderPath;
    getline(cin, folderPath);
    folderPath = decoratePath(folderPath);
    string folderPathPlusProjectName = folderPath + "\\" + projectName + ".dat";
    //�������ԭ����gate��line����Ҫ�Ѵ��ں�option������
    gates.clear();
    lines.clear();
    clearScreen();
    drawOptions();
    drawInterface();
    //�ٶ�ȡ�浵
    readGates(folderPathPlusProjectName);
    readLines(folderPathPlusProjectName);
    HideCursor();
}