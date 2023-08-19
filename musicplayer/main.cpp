#include "ui_widget.h"
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();




    return a.exec();//放置了一个死循环避免闪退
}
