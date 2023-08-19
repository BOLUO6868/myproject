#pragma once
#include"Tools.h"
#include"Mouse.h"
#include"globals.h"
#include"Gate.h"
#include"Line.h"
//�����ַ�(�������������ģʽҲ����������룩
//"��","��","��","��","��","��","��"

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
    string name;//ѡ������
    SMALL_RECT area;//ѡ��ͼ�귶Χ
};

vector<Option>options;//��������ѡ��ؼ�������

Option::Option(string s, SMALL_RECT a)
{
    name = s;
    area = a;
    isHighLight = false;
}

void Option::setName(string s)
{
    //������Ÿ��ַ�
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
    //�����ַ�(�������������ģʽҲ����������룩
    //"��","��","��","��","��","��","��"
    setpos(area.Left, area.Top);
    cout << "��";
    for (int i = area.Left; i <= area.Right - 3; i++)
    {
        cout << "��";
    }
    cout << "��";
    setpos(area.Left, area.Top + 1);
    cout << "�� " << left << setw(area.Right - area.Left - 3) << name << "��";
    setpos(area.Left, area.Top + 2);
    cout << "��";
    for (int i = area.Left; i <= area.Right - 3; i++)
    {
        cout << "��";
    }
    cout << "��";
}


//��������ͼ��
void drawOptions()
{
    for (int i = 0; i < options.size(); i++)
    {
        options[i].draw();
    }
}



//��������ѡ��ͼ�꣬�������λ����ͼ�����򣬾�highlight��ͼ��
void highLightOptions()
{
    for (int i = 0; i < options.size(); i++)
    {
        //�������λ����ͼ�������Ҹ�ͼ��δ��highlight����highlight��ͼ��
        if (mouseInArea(options[i].getArea()) && !options[i].isHighLight)
        {
            highLightArea(options[i].getArea());
            options[i].isHighLight = true;
        }
        //�������λ�ò���ͼ�������Ҹ�ͼ���ѱ�highlight����resetArea��ͼ��
        else if (!mouseInArea(options[i].getArea()) && options[i].isHighLight)
        {
            resetArea(options[i].getArea());
            options[i].isHighLight = false;
        }
    }
}

void deleteGateByMouse();//Ҫ����һ�£���Ȼ�������ڱ���˳���ԭ������chooseOption�����deleteGateByMouse�ᱨ���Ҳ�����ʶ��
void deleteLineByMouse();//Ҫ����һ�£���Ȼ�������ڱ���˳���ԭ������chooseOption�����deleteLineByMouse�ᱨ���Ҳ�����ʶ��
//�ж�����Ƿ񵥻���ĳ��ѡ�����ǣ����ظ�ѡ��ı��
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