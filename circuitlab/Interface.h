#pragma once
#include"Tools.h"
#include"Option.h"
#include"globals.h"
//�����ַ�(�������������ģʽҲ����������룩
//"��","��","��","��","��","��","��"




//����������������ı߽��
void drawInterface()
{
    setpos(0, drawing_area_top_limit + 1);
    cout << "��ͼ��";
    //��ͼ���ϱ߽�
    setpos(0, drawing_area_top_limit);
    for (int i = 0; i < drawing_area_right_limit; i++)
    {
        //cout << "\033(0q";//�����ַ����е�С����
        cout << "��";
    }
    //cout << "\033(0k";
    cout << "��"; 

    //��ͼ���ұ߽�
    for (int i = drawing_area_top_limit + 1; i < drawing_area_bottom_limit; i++)
    {
        setpos(drawing_area_right_limit, i);
        //cout << "\033(0x";//�����ַ����е�С����
        cout << "��";
    }

    ////��ͼ���±߽�
    setpos(0, drawing_area_bottom_limit);
    for (int i = 0; i < drawing_area_right_limit; i++)
    {
        //cout << "\033(0q";//�����ַ����е�С����
        cout << "��";
    }
    //cout << "\033(0j";
    cout << "��";
}

//�����Ϣ����ԭ����Ϣ������ӡ��ʾ��Ϣmessage
void displayMessage(string message)
{
    static int lineNumber = 0;
    //��Ϣ�����������ԭʼ��Ϣ
    if (lineNumber > message_area_bottom_limit - message_area_top_limit)
    {
        for (int i = message_area_top_limit; i <= message_area_bottom_limit; i++)
        {
            setpos(message_area_left_limit, i);
            for (int j = message_area_left_limit; j <= message_area_right_limit; j++)
            {
                cout << " ";
            }
        }
        lineNumber = 0;
        setpos(message_area_left_limit, lineNumber);
        cout << message;
    }
    //��ӡ�µ���Ϣ
    setpos(message_area_left_limit, lineNumber);
    cout << message;
    lineNumber++;
}