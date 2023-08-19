#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"globals.h"
#include"Interface.h"
//画线字符(不用启用虚拟机模式也不会出现乱码）
//"┌","┐","└","┘","─","│","┼"

class Line
{
public:
    void setStart_pos(COORD pos);
    COORD getStart_pos();
    void setEnd_pos(COORD pos);
    COORD getEnd_pos();
    void setDirection(int d);
    int getDirection();
    void setArea();
    SMALL_RECT getArea();
    void show();//显示
    void erase();//擦除

private:
    COORD start_pos;
    COORD end_pos;
    SMALL_RECT area;
    int direction = 0;//0为横线，1为竖线
};

vector<Line>lines;

void Line::setStart_pos(COORD pos)
{
    start_pos = pos;
}
void Line::setEnd_pos(COORD pos)
{
    end_pos = pos;
}
COORD Line::getStart_pos()
{
    return start_pos;
}
COORD Line::getEnd_pos()
{
    return end_pos;
}
void Line::setDirection(int d)
{
    if (d == 0 || d == 1)
    {
        direction = d;
    }
    else
    {
        cout << "line.direction must be 1 or 0 !";
    }
}
int Line::getDirection()
{
    return direction;
}
void Line::show()
{
    //如果是横线
    if (getDirection() == 0)
    {
        //起点在终点左边
        if (getStart_pos().X < getEnd_pos().X)
        {
            setpos(getStart_pos().X, getStart_pos().Y);
            for (int i = 0; i < abs(getStart_pos().X - getEnd_pos().X); i++)
            {
                cout << "─";
            }
        }
        else
        {
            setpos(getEnd_pos().X, getEnd_pos().Y);
            for (int i = 0; i < abs(getStart_pos().X - getEnd_pos().X); i++)
            {
                cout << "─";
            }
        }
    }
    //如果是竖线
    else if (getDirection() == 1)
    {
        //起点在终点上面
        if (getStart_pos().Y < getEnd_pos().Y)
        {
            for (int i = 0; i < abs(getStart_pos().Y - getEnd_pos().Y); i++)
            {
                setpos(getStart_pos().X, getStart_pos().Y + i);
                cout << "│";
            }
        }
        else
        {
            for (int i = 0; i < abs(getStart_pos().Y - getEnd_pos().Y); i++)
            {
                setpos(getEnd_pos().X, getEnd_pos().Y + i);
                cout << "│";
            }
        }
    }
}
void Line::setArea()
{
    area.Left = min(getStart_pos().X, getEnd_pos().X);
    area.Top = min(getStart_pos().Y, getEnd_pos().Y);
    area.Right = max(getStart_pos().X, getEnd_pos().X);
    area.Bottom= max(getStart_pos().Y, getEnd_pos().Y);
}
SMALL_RECT Line::getArea()
{
    return area;
}
void Line::erase()
{
    if (getDirection() == 0)
    {
        for (int i = min(getStart_pos().X, getEnd_pos().X); i <= max(getStart_pos().X, getEnd_pos().X); i++)
        {
            setpos(i, getStart_pos().Y);
            cout << " ";
        }
    }
    else if (getDirection() == 1)
    {
        for (int i = min(getStart_pos().Y, getEnd_pos().Y); i <= max(getStart_pos().Y, getEnd_pos().Y); i++)
        {
            setpos(getStart_pos().X, i);
            cout << " ";
        }
    }
}

//把T型和L型线的交点重绘成相应的转折线
void changeBoundaryPoint()
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines.size(); j++)
        {
            if (i != j)
            {
                if (lines[j].getDirection() == 0)
                {
                    //"┌","┐","└","┘","─","│","┼","┬","├","┤","┴"
                    if (lines[i].getStart_pos().Y == lines[j].getStart_pos().Y)
                    {
                        if (lines[i].getEnd_pos().Y > lines[j].getStart_pos().Y)
                        {
                            //"┬"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "┬";
                        }
                        else if (lines[i].getEnd_pos().Y < lines[j].getStart_pos().Y)
                        {
                            //"┴"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "┴";
                        }
                    }
                }
                else if (lines[j].getDirection() == 1)
                {
                    //"┌","┐","└","┘","─","│","┼","┬","├","┤","┴"
                    if (lines[i].getStart_pos().X == lines[j].getStart_pos().X)
                    {
                        if (lines[i].getEnd_pos().X > lines[j].getStart_pos().X)
                        {
                            //"├"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "├";
                        }
                        else if (lines[i].getEnd_pos().X < lines[j].getStart_pos().X)
                        {
                            //"┤"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "┤";
                        }
                    }
                }
            }
        }
    }
}

//在每次画线操作后调用，用于重新绘制线条，先画横线，再画竖线，解决横线穿过竖线时竖线的缺失问题
void updateLines()
{
    for (int i = 0; i < lines.size(); i++)
    {
        //先重画所有横线
        if (lines[i].getDirection() == 0)
        {
            lines[i].show();
        }
    }
    for (int i = 0; i < lines.size(); i++)
    {
        //再重画所有竖线
        if (lines[i].getDirection() == 1)
        {
            lines[i].show();
        }
    }
    changeBoundaryPoint();
}

void displayMessage(string);//要声明以下，不然可能因为编译顺序原因，导致下面drawLineByMouse()调用displayMessage()时报错：找不到标识符
//创建一个Line对象，通过鼠标和按键配合确定起点和终点，在屏幕上画出，并把它放入lines数组中管理
void drawLineByMouse()
{
    Line line;
    /*setpos(0, 0);
    cout << "                                                             ";
    setpos(0, 0);
    cout << "提示：请单击鼠标左键确定起点";*/
    displayMessage("提示：请单击鼠标左键确定起点");
    COORD start;//起点坐标
    COORD end;//终点坐标
    bool flag1 = false;
    bool flag2 = false;
    while (1)
    {
        if (flag1 == false)
        {
            crossFollowMouse();
        }
        SMALL_RECT tempArea;
        tempArea.Top = drawing_area_top_limit;
        tempArea.Bottom = drawing_area_bottom_limit;
        tempArea.Left = drawing_area_left_limit;
        tempArea.Right = drawing_area_right_limit;
        bool mouseInDrawingArea = mouseInArea(tempArea);
        setCursorPosToMousePos();
        //注意click()一定要放在后面，利用&&的短路性，否则每次调用click，里面的static都会更新，导致第二次的点击判断总是无效
        if (flag1 == false && click() && mouseInDrawingArea)
        {
            start = setCursorPosToMousePos();
            //用一个小交叉标记一下起点
            setpos(start.X, start.Y);
            //cout << "\033(0n";//特殊字符集中的交叉线
            cout << "┼";
            //setpos(70, 0);
            //cout << "起点坐标：" << start.X << "," << start.Y;
            /*setpos(0, 0);
            cout << "提示：请单击鼠标左键确定终点";*/
            displayMessage("提示：请单击鼠标左键确定终点");
            flag1 = true;
        }
        else if (flag1 == true && flag2 == false && click() && mouseInDrawingArea)
        {
            end = setCursorPosToMousePos();
            //用一个小交叉标记一下终点
            //setpos(end.X, end.Y);
            //cout << "\033(0n";//特殊字符集中的交叉线
            flag2 = true;
            //setpos(70, 1);
           ///cout << "终点坐标：" << end.X << "," << end.Y;
        }
        //起点终点都确定好后才开始画直线
        if (flag1 == true && flag2 == true)
        {
            //斜率小于等于1，看作画横线（除2是因为字体宽度是字体高度的一半）
            if (fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 < 1)
            {
                line.setDirection(0);
                if (end.X >= start.X)//起点在终点左边
                {
                    setpos(start.X, start.Y);
                    for (int i = 0; i < abs(start.X - end.X); i++)
                    {
                        setpos(start.X + i, start.Y);
                        //cout << "\033(0q";//特殊字符集中的小横线
                        cout << "─";
                        //cout << "\033(0n";//特殊字符集中的交叉线
                    }
                }
                else//起点在终点右边
                {
                    for (int i = 0; i < abs(start.X - end.X); i++)
                    {
                        setpos(start.X - i, start.Y);
                        //cout << "\033(0q";//特殊字符集中的小横线
                        cout << "─";
                        //cout << "\033(0n";//特殊字符集中的交叉线
                    }
                }
                end.Y = start.Y;
            }
            //横坐标没变或斜率大于1，直接画竖线（防止分母为零造成运行错误，所以必须加一个判断）
            //（利用||逻辑判断短路性，只要满足前一个条件就不计算后一个条件）
            //（除2是因为字体宽度是字体高度的一半）
            else if (start.X == end.X || fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 > 1)
            {
                line.setDirection(1);
                if (end.Y > start.Y)//起点在终点上面
                {
                    for (int i = 0; i < abs(start.Y - end.Y); i++)
                    {
                        setpos(start.X, start.Y + i);
                        //cout << "\033(0x" << endl;//特殊字符集中的竖线
                        cout << "│";
                        //cout << "\033(0n";//特殊字符集中的交叉线
                    }
                }
                else//起点在终点下面
                {
                    for (int i = 0; i < abs(start.Y - end.Y); i++)
                    {
                        setpos(start.X, start.Y - i);
                        //cout << "\033(0x" << endl;//特殊字符集中的竖线
                        cout << "│";
                        //cout << "\033(0n";//特殊字符集中的交叉线
                    }
                }
                end.X = start.X;
            }
            break;
        }
    }
    line.setStart_pos(start);
    line.setEnd_pos(end);
    line.setArea();
    lines.push_back(line);
    updateLines();
    
}
//单击鼠标左键删除作图区的line
void deleteLineByMouse()
{
    for (vector<Line>::iterator it = lines.begin(); it != lines.end();)
    {
        if (mouseInArea(it->getArea()) && click())
        {
            it->erase();
            resetArea(it->getArea());
            it = lines.erase(it);
            updateLines();//擦去自己时将与其他线的交点也擦掉了，所以要重绘所有线条
            updateGates(); //擦去自己时将与其他门的交点也擦掉了，所以要重绘所有门
        }
        else if (mouseInArea(it->getArea()))
        {
            highLightArea(it->getArea());
            it++;
        }
        else
        {
            resetArea(it->getArea());
            it++;
        }
    }
}




//-------------------------------专门给启源gg写的画线函数--------------------------------
//传入起点坐标start和终点坐标end，则可以从起点到终点画一条线
//（只能是垂直的或竖直的，如果start和end不满足垂直关系，则tanθ<45度画横线，大于45度画竖线）
// COORD是<windows.h>中定义的结构体，由两个short类型的成员 X 和 Y 构成，可以表示一个点的坐标
void drawLine(COORD start, COORD end)
{
    Line line;
    //斜率小于等于1，看作画横线（除2是因为字体宽度是字体高度的一半）
    if (fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 < 1)
    {
        line.setDirection(0);
        if (end.X >= start.X)//起点在终点左边
        {
            setpos(start.X, start.Y);
            for (int i = 0; i < abs(start.X - end.X); i++)
            {
                setpos(start.X + i, start.Y);
                //cout << "\033(0q";//特殊字符集中的小横线
                cout << "─";
                //cout << "\033(0n";//特殊字符集中的交叉线
            }
        }
        else//起点在终点右边
        {
            for (int i = 0; i < abs(start.X - end.X); i++)
            {
                setpos(start.X - i, start.Y);
                //cout << "\033(0q";//特殊字符集中的小横线
                cout << "─";
                //cout << "\033(0n";//特殊字符集中的交叉线
            }
        }
    }
    //横坐标没变或斜率大于1，直接画竖线（防止分母为零造成运行错误，所以必须加一个判断）
    //（利用||逻辑判断短路性，只要满足前一个条件就不计算后一个条件）
    //（除2是因为字体宽度是字体高度的一半）
    else if (start.X == end.X || fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 > 1)
    {
        line.setDirection(1);
        if (end.Y > start.Y)//起点在终点上面
        {
            for (int i = 0; i < abs(start.Y - end.Y); i++)
            {
                setpos(start.X, start.Y + i);
                cout << "│";
            }
        }
        else//起点在终点下面
        {
            for (int i = 0; i < abs(start.Y - end.Y); i++)
            {
                setpos(start.X, start.Y - i);
                cout << "│";
            }
        }
    }
    line.setStart_pos(start);
    line.setEnd_pos(end);
    line.setArea();
    lines.push_back(line);
    updateLines();
}