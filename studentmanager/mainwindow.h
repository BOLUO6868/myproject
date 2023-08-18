#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include"dlg_addstu.h"
#include <QMainWindow>
#include<QKeyEvent>
#include<QFile>
#include"page_login.h"
#include"stusql.h"
#include"sign_up.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    virtual void keyPressEvent(QKeyEvent *event);

    void on_btn_sim_clicked();

    void on_pushButton_3_clicked();

    void on_btn_clear_clicked();

    void on_btn_delete_clicked();

    void on_pushButton_4_clicked();

    void on_btn_search_clicked();

    void showpage(const QString &username);

    void setaut(const QString &aut);

private:
    Ui::MainWindow *ui;
    page_login my_login;
    stusql *my_ptrstusql;
    dlg_addstu my_dlgaddstu;
    sign_up my_sign;

    void updatetable();

};
#endif // MAINWINDOW_H
