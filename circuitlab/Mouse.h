#pragma once
#include<iostream>
#include<windows.h>
#include<ctime>
#include"globals.h"
#include"Gate.h"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //��Ҫ�ģ����Ǳ������� 

using namespace std;
//�Ҽ������ͺ�������
//������������⣬����֪���ǵ�������ѡ�������������֮����뵥��һ���Ҽ�����ʱ�Ҽ�����Ҳ���������
//(���������ѽ����ֻ����ú���ȡ������̨�Ŀ��ٱ༭ģʽ����)
//�ж��������
bool click()
{
    static clock_t s = clock();
    clock_t e = clock();
    if (KEY_DOWN(VK_LBUTTON) && (e - s) / CLOCKS_PER_SEC > 0.03)//�������ʱ���жϣ��ᵼ�µ���һ��ȴ���жϵ����˺ܶ��
    {
        s = clock();
        return true;
    }
    return false;
}
//�ж��Ҽ������¼���
bool click_Right()
{
    static clock_t s = clock();
    clock_t e = clock();
    if (KEY_DOWN(VK_RBUTTON) && (e - s) / CLOCKS_PER_SEC > 0.03)//�������ʱ���жϣ��ᵼ�µ���һ��ȴ���жϵ����˺ܶ��
    {
        s = clock();
        return true;
    }
    return false;
}
//�ж����˫���¼�(�����У����ǵ��������һᵼ�������쳣��
bool doubleClick()
{
    if (WM_LBUTTONDBLCLK)
    {
        return true;
    }
    return false;
}

//��ĳ�������������Ϊ�׵׺��֣�highlight��
void highLightArea(SMALL_RECT area)
{
    //SMALL_RECT�ĳ�ʼ����ʽΪ���������¡�

    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // ����ʵ����ɫ�����ı���
    DWORD getWrittenCount = 0;

    // ��ɫ�������
    //COORD writtenPos = { 5, 0 };
    COORD writtenPos = { 5, 0 };

    // ��ɫ
    // ����������̨������������ǰ��ɫ���ţ���ɫ�ַ�����int����ɫ�������COORD������ʵ����ɫ������ָ��DWORD��ûʲô�ã���һ��Ҫ�����Ҳ���Ϊnull��
    // eg: FillConsoleOutputAttribute(outputHandle, 0xF0, 9, writtenPos, &getWrittenCount);
    // ���ӣ�5,0����ʼ������5���������0��ʼ�㣩������9���ַ���Ϊ��ɫ��������ɫ����
    // ���Windows����̨API����ʹ�ã��£�  API����  һ��
    for (short i = area.Top; i <= area.Bottom; i++)
    {
        writtenPos = { area.Left,i };
        FillConsoleOutputAttribute(outputHandle, 0XF0, area.Right - area.Left + 1, writtenPos, &getWrittenCount);
    }
}

//��highlight����������û�ԭ״�����ڵװ��֣�
void resetArea(SMALL_RECT area)
{
    //SMALL_RECT�ĳ�ʼ����ʽΪ���������¡�

    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // ����ʵ����ɫ�����ı���
    DWORD getWrittenCount = 0;

    // ��ɫ�������
    COORD writtenPos = { 5, 0 };

    // ��ɫ
    // ����������̨������������ǰ��ɫ���ţ���ɫ�ַ�����int����ɫ�������COORD������ʵ����ɫ������ָ��DWORD��ûʲô�ã���һ��Ҫ�����Ҳ���Ϊnull��
    // eg: FillConsoleOutputAttribute(outputHandle, 0xF0, 9, writtenPos, &getWrittenCount);
    // ���ӣ�5,0����ʼ������5���������0��ʼ�㣩������9���ַ���Ϊ��ɫ��������ɫ����
    // ���Windows����̨API����ʹ�ã��£�  API����  һ��
    for (short i = area.Top; i <= area.Bottom; i++)
    {
        writtenPos = { area.Left,i };
        FillConsoleOutputAttribute(outputHandle, 07, area.Right - area.Left + 1, writtenPos, &getWrittenCount);
    }
}

//�ж�����Ƿ���ĳ�����η�Χ��
bool mouseInArea(SMALL_RECT area)
{
    //SMALL_RECT�ĳ�ʼ����ʽΪ���������¡�
    HWND hwnd = GetForegroundWindow();
    POINT pt;
    GetCursorPos(&pt);
    //�Ѵ�������ϵ��ԭ������Ļ���Ͻǣ�ת��Ϊ�ͻ�������ϵ��ԭ���ںڿ�����Ͻǣ�
    //������óɹ����ὫPOINT�ṹ��pt�м�¼������ת��Ϊ�µ�����
    // ����һ��Ҫ��GetCursorPos(&pt);��ScreenToClient(hwnd, &pt);����û����
    ScreenToClient(hwnd, &pt);
    // ������
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //�������Եı������������ݣ�һ���ַ����Ϊ8��λ���߶�Ϊ16��λ����1�Ǳ�����λ��������ص������ÿ���(ֻ�����ڴ˵��ԣ����˷ֱ��ʾͲ���)
    //int fontsize_x = 8;
    //int fontsize_y = 16;

    //ͨ�ù�ʽ��ÿ�У��У�����ֵ����/ÿ�У��У��ַ�����
    int fontsize_x = GetSystemMetrics(SM_CXFULLSCREEN) / getConsoleWidth();
    int fontsize_y = GetSystemMetrics(SM_CYFULLSCREEN) / getConsoleHeight();
    COORD pos;
    pos.X = pt.x / fontsize_x;
    pos.Y = pt.y / fontsize_y;

    if (area.Left <= pos.X && pos.X <= area.Right && area.Top <= pos.Y && pos.Y <= area.Bottom)
    {
        return true;
    }
 
    return false;
}

//��ȡ����ڿ���̨����ϵ�µ����꣨һ��λ��һ���ַ��������Լ�д�ģ�
COORD getMousePosOfClient()
{
    HWND hwnd = GetForegroundWindow();
    POINT pt;
    GetCursorPos(&pt);
    //�Ѵ�������ϵ��ԭ������Ļ���Ͻǣ�ת��Ϊ�ͻ�������ϵ��ԭ���ںڿ�����Ͻǣ�
    //������óɹ����ὫPOINT�ṹ��pt�м�¼������ת��Ϊ�µ�����
    // ����һ��Ҫ��GetCursorPos(&pt);��ScreenToClient(hwnd, &pt);����û����
    ScreenToClient(hwnd, &pt);
    // ������
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //�������Եı������������ݣ�һ���ַ����Ϊ8��λ���߶�Ϊ16��λ����1�Ǳ�����λ��������ص������ÿ���(ֻ�����ڴ˵��ԣ����˷ֱ��ʾͲ���)
    //int fontsize_x = 8;
    //int fontsize_y = 16;

    //ͨ�ù�ʽ��ÿ�У��У�����ֵ����/ÿ�У��У��ַ�����
    int fontsize_x = GetSystemMetrics(SM_CXFULLSCREEN) / getConsoleWidth();
    int fontsize_y = GetSystemMetrics(SM_CYFULLSCREEN) / getConsoleHeight();
    COORD pos;
    pos.X = pt.x / fontsize_x;
    pos.Y = pt.y / fontsize_y;
    return pos;
}


//����������һ�£���Ȼ������Ϊ����˳��ԭ�����Ӳ��������Ҳ�����ʶ��
void updateGates();//�����������Ż�����
void updateLines();//�����������߻�����
void drawInterface();//��֪��Ϊʲô�ܻ�ѻ�ͼ���ұ߽�����������߽��ֲ��ᣬ�����ˣ�ֱ�ӱ����ػ��߽���
//��һ���������� ʮ�� ָʾ������λ��
void crossFollowMouse()
{
    static COORD pre_cursor_pos = getCursorPos();
    static bool flag = false;//һ��Ҫ��һ��flag���������ǻ����ѡ������LINE�ַ�
    SMALL_RECT drawing_area;
    drawing_area.Left = drawing_area_left_limit;
    drawing_area.Right = drawing_area_right_limit - 12;
    drawing_area.Top = drawing_area_top_limit + 2;
    drawing_area.Bottom = drawing_area_bottom_limit - 5;
    if (mouseInArea(drawing_area) && flag == false)
    {
        pre_cursor_pos = getCursorPos();
        flag = true;
    }
    if (mouseInArea(drawing_area) && flag == true)
    {
        COORD current_cursor_pos = getCursorPos();
        //������λ�÷����仯
        if ((current_cursor_pos.X != pre_cursor_pos.X || current_cursor_pos.Y != pre_cursor_pos.Y))
        {
            COORD tempPos = current_cursor_pos;//�ȱ������ڵĹ��λ�ã���Ȼ�ػ��š��ߺ󣬼�ʹ���λ�ò��������λ��Ҳ�ᱻ�ı䣬�����жϲ���
            setpos(pre_cursor_pos.X, pre_cursor_pos.Y);
            cout << "  ";
            setpos(current_cursor_pos.X, current_cursor_pos.Y);
            cout << "��";
            updateGates();//�����������Ż�����
            updateLines();//�����������߻�����
            drawInterface();//��֪��Ϊʲô�ܻ�ѻ�ͼ���ұ߽�����������߽��ֲ��ᣬ�����ˣ�ֱ�ӱ����ػ��߽���
            current_cursor_pos = tempPos;
            pre_cursor_pos = current_cursor_pos;//ע�����ﲻ����getCursorPos()��ȡ��ǰʱ�̹��λ�ã���Ӧ����Ϊ�ոջ�ȡ���Ĺ��λ��,��������ƶ�̫��ᵼ��ͿĨ����
        }
    }
}