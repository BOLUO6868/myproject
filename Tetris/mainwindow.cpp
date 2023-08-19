#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "formStart.h"
#include "formGame.h"
#include "formHelp.h"
#include "formHistory.h"
#include "formSetting.h"

#include "audio.h"

#include "database/users.h"
#include "database/history.h"
#include "database/logindialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);

    this->setWindowTitle("俄罗斯方块");                                       // 标题
    this->setFixedSize(800, 600);                                             // 固定大小窗口
    this->setStyleSheet("#widgetMenu{border-image: url(:/assets/bg4.jpg);}"); // 背景图片

    ui->labelUser->setText("");

    // 初始化
    musicPlay(":/assets/bg_mainmenu.mp3");

    // 按钮事件
    connect(ui->buttonStart, &QToolButton::clicked, [=] {
        FormStart* form = new FormStart();
        // FormGame* form = new FormGame();
        // form->start(12, 20, 500);
        form->show();
        close();
    });

    connect(ui->buttonHelp, &QToolButton::clicked, [=] {
        FormHelp form(this);
        form.exec();
    });

    connect(ui->buttonHistory, &QToolButton::clicked, [=] {
        FormHistory form(this);
        form.exec();
    });

    connect(ui->buttonSetting, &QToolButton::clicked, [=] {
        FormSetting form(this);
        form.exec();
    });

    connect(ui->buttonExit, &QToolButton::clicked, [=] {
        QApplication::exit();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 显示登陆
bool MainWindow::login()
{
    // 显示登陆对话框
    LoginDialog login(this);
    login.exec();

    if (login.result() == QDialog::Rejected) {
        qDebug() << "quit";

        return false;
    }

    ui->labelUser->setText(login.userName());
    FormSetting::currentSetting().user = login.userName();

    return true;
}
