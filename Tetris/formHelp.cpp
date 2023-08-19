#include "formHelp.h"
#include "ui_formHelp.h"

#include <QDebug>

FormHelp::FormHelp(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::FormHelp)
{
    ui->setupUi(this);
    this->setWindowTitle("帮助");                                           // 标题
    this->setFixedSize(800, 600);                                           // 固定大小窗口
    this->setStyleSheet("#FormHelp{border-image: url(:/assets/bg4.jpg);}"); // 背景图片

    // 组件事件
    connect(ui->buttonOk, &QToolButton::clicked, [=] { // 确定
        close();
    });
}

FormHelp::~FormHelp()
{
    delete ui;
}
