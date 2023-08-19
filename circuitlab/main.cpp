#include"Tools.h"
#include"Gate.h"
#include"Line.h"
#include"test.h"
#include"Interface.h"
#include"SaveAndRead.h"
#include"globals.h"
#include"freeDesign.h"
#include"mainMenu.h"
void initGlobals()
{
    drawing_area_top_limit = 3;//������ͼ����������
    drawing_area_bottom_limit = getLargestConsoleHeight() - 1; // ������ͼ���¼�������
    drawing_area_left_limit = 0;//������ͼ����������
    drawing_area_right_limit = getLargestConsoleWidth() - 25; // ������ͼ���Ҽ�������

    option_right_limit = getLargestConsoleWidth() - 20;//�ؼ������������ֵ

    message_area_top_limit = 0;//��Ϣ��ʾ����������
    message_area_bottom_limit = 2;//��Ϣ��ʾ����������
    message_area_left_limit = 0;//��Ϣ��ʾ������������
    message_area_right_limit = getLargestConsoleWidth() - 25;//��Ϣ��ʾ���Ҽ�������
}

void prepareAndTips()
{
    EnableVTMode();
    HideCursor();
    fullScreen();
    cout << "��ʾ��" << endl;
    cout << "��ϵͳ�汾���⣬����ʱ�����δ�Զ�����ȫ��ģʽ�����ֶ�����ȫ��ģʽ��Ȼ�������������������ܵ���ͼ���λ�����⡣" << endl;
    cout << "����ʱ����ȫ��ģʽ������Դ���ʾ���������������" << endl;
    _getch();
    clearScreen();
    //canNotChangeConsoleSize();
    DisableMaximizeAndResize();
    DisableMaximizeAndMove();
    disableQuickEditMode();
}
int main()
{
    prepareAndTips();
    initGlobals();
    mainMenu();
    return 0;
}