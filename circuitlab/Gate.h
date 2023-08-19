#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"globals.h"
#include"Interface.h"
//画线字符(不用启用虚拟机模式也不会出现乱码）
//"┌","┐","└","┘","─","│","┼"

class Gate
{
public:
    void setName(string s);
    string getName();
    void setPos(COORD p);
    COORD getPos();
    void setArea();
    SMALL_RECT getArea();
    void show();//显示
    void erase();//擦除

private:
    COORD pos;//左上角
    SMALL_RECT area;
    bool input1 = 0;//输入1
    bool input2 = 0;//输入2
    bool input3 = 0;//输入3
    bool output = 0;//输出
    //string name;
    //文件读写时要注意不要使用string类型的数据
    //string类中有一个成员指针 char* ，该指针指向存储字符串的空间，
    //当我们把string类的数据存储到文件中再读出来时，不能保证指针有效。
    //所以若Gate类中含有string，read没问题，但write时会运行时错误（访问权限冲突）
    char name[40];
};

vector<Gate>gates;

void Gate::setName(string s)
{
    if (s == "AND" || s == "OR" || s == "NAND" || s == "NOR" || s == "XOR" || s == "NOT")
    {
        int i = 0;
        for (i = 0; i < s.size(); i++)
        {
            name[i] = s[i];
        }
        name[i] = '\0';//加上结束符，这样cout<<name 时才能不把后面的脏数据也输出来
    }
    else
    {
        setpos(50, 1);
        cout << "error，do not have a kind of gate called: " << s;
    }
}
string Gate::getName()
{
    return name;
}
void Gate::setPos(COORD p)
{
    pos = p;
}
COORD Gate::getPos()
{
    return pos;
}
void Gate::show()
{
    COORD gate_pos = getPos();
    setpos(gate_pos.X, gate_pos.Y);
    cout << "┌─────┐";
    setpos(gate_pos.X, gate_pos.Y + 1);
    cout << "┼" << "     │";
    setpos(gate_pos.X, gate_pos.Y + 2);
    cout << "┼ " << setw(4) << name << "┼";
    setpos(gate_pos.X, gate_pos.Y + 3);
    cout << "┼" << "     │";
    setpos(gate_pos.X, gate_pos.Y + 4);
    cout << "└─────┘";
}
void Gate::setArea()
{
    area.Left = getPos().X;
    area.Top = getPos().Y;
    area.Right = getPos().X + 7;
    area.Bottom = getPos().Y + 4;
}
SMALL_RECT Gate::getArea()
{
    return area;
}
void Gate::erase()
{
    COORD gate_pos = getPos();
    setpos(gate_pos.X, gate_pos.Y);
    cout << "              ";
    setpos(gate_pos.X, gate_pos.Y + 1);
    cout << "  " << "      ";
    setpos(gate_pos.X, gate_pos.Y + 2);
    cout << "              ";
    setpos(gate_pos.X, gate_pos.Y + 3);
    cout << "              ";
    setpos(gate_pos.X, gate_pos.Y + 4);
    cout << "              ";
}


//重绘所有门
void updateGates()
{
    for (int i = 0; i < gates.size(); i++)
    {
        gates[i].show();
    }
}
//在选择某个门后，在确定门的左上角坐标前，一直有一个名为name的门跟着鼠标移动
void gateFollowMouse(string name)
{
    static COORD pre_cursor_pos = getCursorPos();
    SMALL_RECT drawing_area;
    drawing_area.Left = drawing_area_left_limit;
    drawing_area.Right = drawing_area_right_limit - 12;
    drawing_area.Top = drawing_area_top_limit + 2;
    drawing_area.Bottom = drawing_area_bottom_limit - 5;
    if (mouseInArea(drawing_area))
    {
        COORD current_cursor_pos = getCursorPos();
        //如果鼠标位置发生变化
        if ((current_cursor_pos.X != pre_cursor_pos.X || current_cursor_pos.Y != pre_cursor_pos.Y))
        {
            Gate g;
            g.setPos(pre_cursor_pos);
            g.setArea();
            g.erase();
            g.setPos(current_cursor_pos);
            g.setArea();
            g.setName(name);
            g.show();
            COORD tempPos = current_cursor_pos;//先保存现在的光标位置，不然重绘门、线后，即使鼠标位置不动，光标位置也会被改变，导致判断不对
            updateGates();//将被擦掉的门画回来
            updateLines();//将被擦掉的线画回来
            drawInterface();//不知道为什么总会把绘图区右边界擦掉，其他边界又不会，不管了，直接暴力重画边界线
            current_cursor_pos = tempPos;
            pre_cursor_pos = current_cursor_pos;//注意这里不能用getCursorPos()获取当前时刻光标位置，而应设置为刚刚获取到的光标位置,否则鼠标移动太快会导致涂抹现象
        }
    }
}

//创建一个门对象，在鼠标位置作为门的左上角，按s画一个门，并将该门放入gates数组中在管理门的名字根据name来定
void drawGateByMouse(string name)
{
    Gate g;
    g.setName(name);
    /*setpos(0, 0);
    cout << "                                                               ";
    setpos(0, 0);
    cout << "提示：请单击鼠标左键确定左上角坐标";*/
    displayMessage("提示：请单击鼠标左键确定左上角坐标");
    COORD gate_pos;//门的左上角坐标
    while (1)
    {
        //crossFollowMouse();
        COORD mouse_pos = setCursorPosToMousePos();
        SMALL_RECT tempArea;
        tempArea.Top = drawing_area_top_limit + 1;
        tempArea.Bottom = drawing_area_bottom_limit - 1;
        tempArea.Left = drawing_area_left_limit;
        tempArea.Right = drawing_area_right_limit - 12;
        bool mouseInDrawingArea = mouseInArea(tempArea);
        if (mouseInArea(tempArea))
        {
            gateFollowMouse(name);
        }
        if(click() && mouseInDrawingArea)
        {
            //画线字符(不用启用虚拟机模式也不会出现乱码）
            //"┌","┐","└","┘","─","│","┼"
            gate_pos = setCursorPosToMousePos();
            /*setpos(gate_pos.X, gate_pos.Y);
            cout << "\033(0lqqqqqk";
            setpos(gate_pos.X, gate_pos.Y + 1);
            cout << "\033(0n" << "     \033(0x";
            setpos(gate_pos.X, gate_pos.Y + 2);
            cout << "\033(0n " << setw(4) << name << "\033(0n";
            setpos(gate_pos.X, gate_pos.Y + 3);
            cout << "\033(0n" << "     \033(0x";
            setpos(gate_pos.X, gate_pos.Y + 4);
            cout << "\033(0mqqqqqj";*/
            setpos(gate_pos.X, gate_pos.Y);
            cout << "┌─────┐";
            setpos(gate_pos.X, gate_pos.Y + 1);
            cout << "┼" << "     │";
            setpos(gate_pos.X, gate_pos.Y + 2);
            cout << "┼ " << setw(4) << name << "┼";
            setpos(gate_pos.X, gate_pos.Y + 3);
            cout << "┼" << "     │";
            setpos(gate_pos.X, gate_pos.Y + 4);
            cout << "└─────┘"; 
            break;
        }
    }
    g.setPos(gate_pos);
    g.setArea();
    gates.push_back(g);
}
//单击鼠标左键删除作图区的gate
void deleteGateByMouse()
{
    for (vector<Gate>::iterator it=gates.begin();it!=gates.end();)
    {
        if (mouseInArea(it->getArea()) && click())
        {
            it->erase();
            resetArea(it->getArea());
            it = gates.erase(it);
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


