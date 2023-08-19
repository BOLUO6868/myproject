#pragma once
#include"Tools.h"
int drawing_area_top_limit = 3;//自由作图区上限坐标
int drawing_area_bottom_limit = getLargestConsoleHeight() - 1; // 自由作图区下极限坐标
int drawing_area_left_limit = 0;//自由作图区左极限坐标
int drawing_area_right_limit = getLargestConsoleWidth() - 25; // 自由作图区右极限坐标

short option_right_limit = getLargestConsoleWidth() - 20;//控件左边坐标的最大值

int message_area_top_limit = 0;//信息提示区上限坐标
int message_area_bottom_limit = 2;//信息提示区下限坐标
int message_area_left_limit = 0;//信息提示区上左极限坐标
int message_area_right_limit = getLargestConsoleWidth() - 25;//信息提示区右极限坐标

short menu_option_left_limit = getConsoleWidth() / 2 + 10;
short menu_option_top_limit = getConsoleHeight() / 3 * 2;
