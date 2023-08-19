#include "formStart.h"
#include "ui_formStart.h"

#include "mainwindow.h"
#include "formGame.h"

#include <QDebug>

FormStart::FormStart(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FormStart)
{
    ui->setupUi(this);
    this->setWindowTitle("开始");                                            // 标题
    this->setFixedSize(800, 600);                                            // 固定大小窗口
    this->setAttribute(Qt::WA_StyledBackground, true);
    //this->setStyleSheet("#FormStart{border-image: url(:/assets/bg4.jpg);}"); // 背景图片
    //#FormStart{border-image: url(:/assets/bg4.jpg);}

    // 组件事件
    connect(ui->buttonOk, &QToolButton::clicked, [=] { // 确定
        int speed;
        int w, h;
        // int style;

        switch (ui->comboBoxSpeed->currentIndex()) {
        case 0:
            speed = 1000;
            break;
        case 1:
            speed = 750;
            break;
        case 2:
            speed = 500;
            break;
        default:
            speed = 1000;
            break;
        }

        switch (ui->comboBoxSize->currentIndex()) {
        case 0:
            w = 10;
            h = 20;
            break;
        case 1:
            w = 12;
            h = 20;
            break;
        case 2:
            w = 15;
            h = 20;
            break;
        default:
            w = 10;
            h = 20;
            break;
        }

        switch (ui->comboBoxStyle->currentIndex()) {
        }

        FormGame* form = new FormGame();
        form->start(w, h, speed);
        form->show();
        close();
    });

    connect(ui->buttonBack, &QToolButton::clicked, [=] { // 返回
        MainWindow* form = new MainWindow();
        form->show();
        close();
    });
}

FormStart::~FormStart()
{
    delete ui;
}
