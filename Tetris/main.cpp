#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "database/users.h"
#include "database/history.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    /* 测试
    users.add("小明", "123456");
    users.save("users.xml");

    users.clear();
    */
    users.load("users.xml");

    /*
    for (int i = 0; i < 20; ++i) {
        history.add("aaa", rand() % 1000);
    }
    history.save("scores.xml");
    //*/
    history.load("scores.xml");

    MainWindow w;
    w.show();

    //*
    // 如果登陆点了取消，直接返回
    if (w.login() == false) {
        return 0;
    }
    //*/

    return a.exec();
}
