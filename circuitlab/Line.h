#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"globals.h"
#include"Interface.h"
//�����ַ�(�������������ģʽҲ����������룩
//"��","��","��","��","��","��","��"

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
    void show();//��ʾ
    void erase();//����

private:
    COORD start_pos;
    COORD end_pos;
    SMALL_RECT area;
    int direction = 0;//0Ϊ���ߣ�1Ϊ����
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
    //����Ǻ���
    if (getDirection() == 0)
    {
        //������յ����
        if (getStart_pos().X < getEnd_pos().X)
        {
            setpos(getStart_pos().X, getStart_pos().Y);
            for (int i = 0; i < abs(getStart_pos().X - getEnd_pos().X); i++)
            {
                cout << "��";
            }
        }
        else
        {
            setpos(getEnd_pos().X, getEnd_pos().Y);
            for (int i = 0; i < abs(getStart_pos().X - getEnd_pos().X); i++)
            {
                cout << "��";
            }
        }
    }
    //���������
    else if (getDirection() == 1)
    {
        //������յ�����
        if (getStart_pos().Y < getEnd_pos().Y)
        {
            for (int i = 0; i < abs(getStart_pos().Y - getEnd_pos().Y); i++)
            {
                setpos(getStart_pos().X, getStart_pos().Y + i);
                cout << "��";
            }
        }
        else
        {
            for (int i = 0; i < abs(getStart_pos().Y - getEnd_pos().Y); i++)
            {
                setpos(getEnd_pos().X, getEnd_pos().Y + i);
                cout << "��";
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

//��T�ͺ�L���ߵĽ����ػ����Ӧ��ת����
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
                    //"��","��","��","��","��","��","��","��","��","��","��"
                    if (lines[i].getStart_pos().Y == lines[j].getStart_pos().Y)
                    {
                        if (lines[i].getEnd_pos().Y > lines[j].getStart_pos().Y)
                        {
                            //"��"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "��";
                        }
                        else if (lines[i].getEnd_pos().Y < lines[j].getStart_pos().Y)
                        {
                            //"��"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "��";
                        }
                    }
                }
                else if (lines[j].getDirection() == 1)
                {
                    //"��","��","��","��","��","��","��","��","��","��","��"
                    if (lines[i].getStart_pos().X == lines[j].getStart_pos().X)
                    {
                        if (lines[i].getEnd_pos().X > lines[j].getStart_pos().X)
                        {
                            //"��"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "��";
                        }
                        else if (lines[i].getEnd_pos().X < lines[j].getStart_pos().X)
                        {
                            //"��"
                            setpos(lines[i].getStart_pos().X, lines[i].getStart_pos().Y);
                            cout << "��";
                        }
                    }
                }
            }
        }
    }
}

//��ÿ�λ��߲�������ã��������»����������Ȼ����ߣ��ٻ����ߣ�������ߴ�������ʱ���ߵ�ȱʧ����
void updateLines()
{
    for (int i = 0; i < lines.size(); i++)
    {
        //���ػ����к���
        if (lines[i].getDirection() == 0)
        {
            lines[i].show();
        }
    }
    for (int i = 0; i < lines.size(); i++)
    {
        //���ػ���������
        if (lines[i].getDirection() == 1)
        {
            lines[i].show();
        }
    }
    changeBoundaryPoint();
}

void displayMessage(string);//Ҫ�������£���Ȼ������Ϊ����˳��ԭ�򣬵�������drawLineByMouse()����displayMessage()ʱ�����Ҳ�����ʶ��
//����һ��Line����ͨ�����Ͱ������ȷ�������յ㣬����Ļ�ϻ���������������lines�����й���
void drawLineByMouse()
{
    Line line;
    /*setpos(0, 0);
    cout << "                                                             ";
    setpos(0, 0);
    cout << "��ʾ���뵥��������ȷ�����";*/
    displayMessage("��ʾ���뵥��������ȷ�����");
    COORD start;//�������
    COORD end;//�յ�����
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
        //ע��click()һ��Ҫ���ں��棬����&&�Ķ�·�ԣ�����ÿ�ε���click�������static������£����µڶ��εĵ���ж�������Ч
        if (flag1 == false && click() && mouseInDrawingArea)
        {
            start = setCursorPosToMousePos();
            //��һ��С������һ�����
            setpos(start.X, start.Y);
            //cout << "\033(0n";//�����ַ����еĽ�����
            cout << "��";
            //setpos(70, 0);
            //cout << "������꣺" << start.X << "," << start.Y;
            /*setpos(0, 0);
            cout << "��ʾ���뵥��������ȷ���յ�";*/
            displayMessage("��ʾ���뵥��������ȷ���յ�");
            flag1 = true;
        }
        else if (flag1 == true && flag2 == false && click() && mouseInDrawingArea)
        {
            end = setCursorPosToMousePos();
            //��һ��С������һ���յ�
            //setpos(end.X, end.Y);
            //cout << "\033(0n";//�����ַ����еĽ�����
            flag2 = true;
            //setpos(70, 1);
           ///cout << "�յ����꣺" << end.X << "," << end.Y;
        }
        //����յ㶼ȷ���ú�ſ�ʼ��ֱ��
        if (flag1 == true && flag2 == true)
        {
            //б��С�ڵ���1�����������ߣ���2����Ϊ������������߶ȵ�һ�룩
            if (fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 < 1)
            {
                line.setDirection(0);
                if (end.X >= start.X)//������յ����
                {
                    setpos(start.X, start.Y);
                    for (int i = 0; i < abs(start.X - end.X); i++)
                    {
                        setpos(start.X + i, start.Y);
                        //cout << "\033(0q";//�����ַ����е�С����
                        cout << "��";
                        //cout << "\033(0n";//�����ַ����еĽ�����
                    }
                }
                else//������յ��ұ�
                {
                    for (int i = 0; i < abs(start.X - end.X); i++)
                    {
                        setpos(start.X - i, start.Y);
                        //cout << "\033(0q";//�����ַ����е�С����
                        cout << "��";
                        //cout << "\033(0n";//�����ַ����еĽ�����
                    }
                }
                end.Y = start.Y;
            }
            //������û���б�ʴ���1��ֱ�ӻ����ߣ���ֹ��ĸΪ��������д������Ա����һ���жϣ�
            //������||�߼��ж϶�·�ԣ�ֻҪ����ǰһ�������Ͳ������һ��������
            //����2����Ϊ������������߶ȵ�һ�룩
            else if (start.X == end.X || fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 > 1)
            {
                line.setDirection(1);
                if (end.Y > start.Y)//������յ�����
                {
                    for (int i = 0; i < abs(start.Y - end.Y); i++)
                    {
                        setpos(start.X, start.Y + i);
                        //cout << "\033(0x" << endl;//�����ַ����е�����
                        cout << "��";
                        //cout << "\033(0n";//�����ַ����еĽ�����
                    }
                }
                else//������յ�����
                {
                    for (int i = 0; i < abs(start.Y - end.Y); i++)
                    {
                        setpos(start.X, start.Y - i);
                        //cout << "\033(0x" << endl;//�����ַ����е�����
                        cout << "��";
                        //cout << "\033(0n";//�����ַ����еĽ�����
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
//����������ɾ����ͼ����line
void deleteLineByMouse()
{
    for (vector<Line>::iterator it = lines.begin(); it != lines.end();)
    {
        if (mouseInArea(it->getArea()) && click())
        {
            it->erase();
            resetArea(it->getArea());
            it = lines.erase(it);
            updateLines();//��ȥ�Լ�ʱ���������ߵĽ���Ҳ�����ˣ�����Ҫ�ػ���������
            updateGates(); //��ȥ�Լ�ʱ���������ŵĽ���Ҳ�����ˣ�����Ҫ�ػ�������
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




//-------------------------------ר�Ÿ���Դggд�Ļ��ߺ���--------------------------------
//�����������start���յ�����end������Դ���㵽�յ㻭һ����
//��ֻ���Ǵ�ֱ�Ļ���ֱ�ģ����start��end�����㴹ֱ��ϵ����tan��<45�Ȼ����ߣ�����45�Ȼ����ߣ�
// COORD��<windows.h>�ж���Ľṹ�壬������short���͵ĳ�Ա X �� Y ���ɣ����Ա�ʾһ���������
void drawLine(COORD start, COORD end)
{
    Line line;
    //б��С�ڵ���1�����������ߣ���2����Ϊ������������߶ȵ�һ�룩
    if (fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 < 1)
    {
        line.setDirection(0);
        if (end.X >= start.X)//������յ����
        {
            setpos(start.X, start.Y);
            for (int i = 0; i < abs(start.X - end.X); i++)
            {
                setpos(start.X + i, start.Y);
                //cout << "\033(0q";//�����ַ����е�С����
                cout << "��";
                //cout << "\033(0n";//�����ַ����еĽ�����
            }
        }
        else//������յ��ұ�
        {
            for (int i = 0; i < abs(start.X - end.X); i++)
            {
                setpos(start.X - i, start.Y);
                //cout << "\033(0q";//�����ַ����е�С����
                cout << "��";
                //cout << "\033(0n";//�����ַ����еĽ�����
            }
        }
    }
    //������û���б�ʴ���1��ֱ�ӻ����ߣ���ֹ��ĸΪ��������д������Ա����һ���жϣ�
    //������||�߼��ж϶�·�ԣ�ֻҪ����ǰһ�������Ͳ������һ��������
    //����2����Ϊ������������߶ȵ�һ�룩
    else if (start.X == end.X || fabs((start.Y - end.Y) * 1.0 / (start.X - end.X)) / 2 > 1)
    {
        line.setDirection(1);
        if (end.Y > start.Y)//������յ�����
        {
            for (int i = 0; i < abs(start.Y - end.Y); i++)
            {
                setpos(start.X, start.Y + i);
                cout << "��";
            }
        }
        else//������յ�����
        {
            for (int i = 0; i < abs(start.Y - end.Y); i++)
            {
                setpos(start.X, start.Y - i);
                cout << "��";
            }
        }
    }
    line.setStart_pos(start);
    line.setEnd_pos(end);
    line.setArea();
    lines.push_back(line);
    updateLines();
}