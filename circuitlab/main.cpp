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
    drawing_area_top_limit = 3;//自由作图区上限坐标
    drawing_area_bottom_limit = getLargestConsoleHeight() - 1; // 自由作图区下极限坐标
    drawing_area_left_limit = 0;//自由作图区左极限坐标
    drawing_area_right_limit = getLargestConsoleWidth() - 25; // 自由作图区右极限坐标

    option_right_limit = getLargestConsoleWidth() - 20;//控件左边坐标的最大值

    message_area_top_limit = 0;//信息提示区上限坐标
    message_area_bottom_limit = 2;//信息提示区下限坐标
    message_area_left_limit = 0;//信息提示区上左极限坐标
    message_area_right_limit = getLargestConsoleWidth() - 25;//信息提示区右极限坐标
}

void prepareAndTips()
{
    EnableVTMode();
    HideCursor();
    fullScreen();
    cout << "提示：" << endl;
    cout << "因系统版本问题，若此时该软件未自动进入全屏模式，请手动进入全屏模式，然后按任意键继续，否则可能导致图像错位等问题。" << endl;
    cout << "若此时已是全屏模式，请忽略此提示，并按任意键继续" << endl;
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