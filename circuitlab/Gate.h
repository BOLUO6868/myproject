#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"globals.h"
#include"Interface.h"
//�����ַ�(�������������ģʽҲ����������룩
//"��","��","��","��","��","��","��"

class Gate
{
public:
    void setName(string s);
    string getName();
    void setPos(COORD p);
    COORD getPos();
    void setArea();
    SMALL_RECT getArea();
    void show();//��ʾ
    void erase();//����

private:
    COORD pos;//���Ͻ�
    SMALL_RECT area;
    bool input1 = 0;//����1
    bool input2 = 0;//����2
    bool input3 = 0;//����3
    bool output = 0;//���
    //string name;
    //�ļ���дʱҪע�ⲻҪʹ��string���͵�����
    //string������һ����Աָ�� char* ����ָ��ָ��洢�ַ����Ŀռ䣬
    //�����ǰ�string������ݴ洢���ļ����ٶ�����ʱ�����ܱ�ָ֤����Ч��
    //������Gate���к���string��readû���⣬��writeʱ������ʱ���󣨷���Ȩ�޳�ͻ��
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
        name[i] = '\0';//���Ͻ�����������cout<<name ʱ���ܲ��Ѻ����������Ҳ�����
    }
    else
    {
        setpos(50, 1);
        cout << "error��do not have a kind of gate called: " << s;
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
    cout << "��������������";
    setpos(gate_pos.X, gate_pos.Y + 1);
    cout << "��" << "     ��";
    setpos(gate_pos.X, gate_pos.Y + 2);
    cout << "�� " << setw(4) << name << "��";
    setpos(gate_pos.X, gate_pos.Y + 3);
    cout << "��" << "     ��";
    setpos(gate_pos.X, gate_pos.Y + 4);
    cout << "��������������";
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


//�ػ�������
void updateGates()
{
    for (int i = 0; i < gates.size(); i++)
    {
        gates[i].show();
    }
}
//��ѡ��ĳ���ź���ȷ���ŵ����Ͻ�����ǰ��һֱ��һ����Ϊname���Ÿ�������ƶ�
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
        //������λ�÷����仯
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
            COORD tempPos = current_cursor_pos;//�ȱ������ڵĹ��λ�ã���Ȼ�ػ��š��ߺ󣬼�ʹ���λ�ò��������λ��Ҳ�ᱻ�ı䣬�����жϲ���
            updateGates();//�����������Ż�����
            updateLines();//�����������߻�����
            drawInterface();//��֪��Ϊʲô�ܻ�ѻ�ͼ���ұ߽�����������߽��ֲ��ᣬ�����ˣ�ֱ�ӱ����ػ��߽���
            current_cursor_pos = tempPos;
            pre_cursor_pos = current_cursor_pos;//ע�����ﲻ����getCursorPos()��ȡ��ǰʱ�̹��λ�ã���Ӧ����Ϊ�ոջ�ȡ���Ĺ��λ��,��������ƶ�̫��ᵼ��ͿĨ����
        }
    }
}

//����һ���Ŷ��������λ����Ϊ�ŵ����Ͻǣ���s��һ���ţ��������ŷ���gates�������ڹ����ŵ����ָ���name����
void drawGateByMouse(string name)
{
    Gate g;
    g.setName(name);
    /*setpos(0, 0);
    cout << "                                                               ";
    setpos(0, 0);
    cout << "��ʾ���뵥��������ȷ�����Ͻ�����";*/
    displayMessage("��ʾ���뵥��������ȷ�����Ͻ�����");
    COORD gate_pos;//�ŵ����Ͻ�����
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
            //�����ַ�(�������������ģʽҲ����������룩
            //"��","��","��","��","��","��","��"
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
            cout << "��������������";
            setpos(gate_pos.X, gate_pos.Y + 1);
            cout << "��" << "     ��";
            setpos(gate_pos.X, gate_pos.Y + 2);
            cout << "�� " << setw(4) << name << "��";
            setpos(gate_pos.X, gate_pos.Y + 3);
            cout << "��" << "     ��";
            setpos(gate_pos.X, gate_pos.Y + 4);
            cout << "��������������"; 
            break;
        }
    }
    g.setPos(gate_pos);
    g.setArea();
    gates.push_back(g);
}
//����������ɾ����ͼ����gate
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


