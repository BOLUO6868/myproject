#pragma once
#include"Tools.h"
int drawing_area_top_limit = 3;//������ͼ����������
int drawing_area_bottom_limit = getLargestConsoleHeight() - 1; // ������ͼ���¼�������
int drawing_area_left_limit = 0;//������ͼ����������
int drawing_area_right_limit = getLargestConsoleWidth() - 25; // ������ͼ���Ҽ�������

short option_right_limit = getLargestConsoleWidth() - 20;//�ؼ������������ֵ

int message_area_top_limit = 0;//��Ϣ��ʾ����������
int message_area_bottom_limit = 2;//��Ϣ��ʾ����������
int message_area_left_limit = 0;//��Ϣ��ʾ������������
int message_area_right_limit = getLargestConsoleWidth() - 25;//��Ϣ��ʾ���Ҽ�������

short menu_option_left_limit = getConsoleWidth() / 2 + 10;
short menu_option_top_limit = getConsoleHeight() / 3 * 2;
