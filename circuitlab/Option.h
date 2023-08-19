#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"globals.h"
#include"Gate.h"
#include"Line.h"
//画线字符(不用启用虚拟机模式也不会出现乱码）
//"┌","┐","└","┘","─","│","┼"

ostream& operator<<(ostream& cout, SMALL_RECT s)
{
    cout << s.Left << "," << s.Top << "," << s.Right << "," << s.Bottom << endl;
    return cout;
}

class Option
{
public:
    Option(string s = "unknown", SMALL_RECT a = { option_right_limit,4,short(option_right_limit + 11),6 });
    void setName(string s);
    string getName();
    void setArea(SMALL_RECT a);
    SMALL_RECT getArea();
    void draw();
    bool isHighLight;

private:
    string name;//选项名称
    SMALL_RECT area;//选项图标范围
};

vector<Option>options;//管理所有选项控件的数组

Option::Option(string s, SMALL_RECT a)
{
    name = s;
    area = a;
    isHighLight = false;
}

void Option::setName(string s)
{
    //名字最长九个字符
    if (s.size() <= 9)
    {
        name = s;
    }
    else
    {
        s = s.substr(0, 9);
        name = s;
    }
}
string Option::getName()
{
    return name;
}
void Option::setArea(SMALL_RECT a)
{
    area = a;
}
SMALL_RECT Option::getArea()
{
    return area;
}
void Option::draw()
{
    //画线字符(不用启用虚拟机模式也不会出现乱码）
    //"┌","┐","└","┘","─","│","┼"
    setpos(area.Left, area.Top);
    cout << "┌";
    for (int i = area.Left; i <= area.Right - 3; i++)
    {
        cout << "─";
    }
    cout << "┐";
    setpos(area.Left, area.Top + 1);
    cout << "│ " << left << setw(area.Right - area.Left - 3) << name << "│";
    setpos(area.Left, area.Top + 2);
    cout << "└";
    for (int i = area.Left; i <= area.Right - 3; i++)
    {
        cout << "─";
    }
    cout << "┘";
}


//绘制所有图标
void drawOptions()
{
    for (int i = 0; i < options.size(); i++)
    {
        options[i].draw();
    }
}



//遍历所有选项图标，如果鼠标的位置在图标区域，就highlight该图标
void highLightOptions()
{
    for (int i = 0; i < options.size(); i++)
    {
        //如果鼠标的位置在图标区域，且该图标未被highlight，就highlight该图标
        if (mouseInArea(options[i].getArea()) && !options[i].isHighLight)
        {
            highLightArea(options[i].getArea());
            options[i].isHighLight = true;
        }
        //如果鼠标的位置不在图标区域，且该图标已被highlight，就resetArea该图标
        else if (!mouseInArea(options[i].getArea()) && options[i].isHighLight)
        {
            resetArea(options[i].getArea());
            options[i].isHighLight = false;
        }
    }
}

void deleteGateByMouse();//要声明一下，不然可能由于编译顺序的原因，下面chooseOption里调用deleteGateByMouse会报错：找不到标识符
void deleteLineByMouse();//要声明一下，不然可能由于编译顺序的原因，下面chooseOption里调用deleteLineByMouse会报错：找不到标识符
//判断鼠标是否单击了某个选项，如果是，返回该选项的编号
string chooseOption()
{
    while (1)
    {
        highLightOptions();
        deleteGateByMouse();
        deleteLineByMouse();
        for (int i = 0; i < options.size(); i++)
        {
            if (mouseInArea(options[i].getArea()) && click())
            {
                return options[i].getName();
            }
        }
    }
    return "unknown";
}