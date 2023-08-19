#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUrl>
#include<QMediaPlayer>
#include <QMediaPlaylist>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


public slots:
    void onTimer();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void timerEvent(QTimerEvent* event);
private:
    Ui::Widget *ui;
    QList<QUrl>PLayList;
    QMediaPlayer player;
    QMediaPlaylist playlist;
    int mode;
    QTimer m_timer; // 计时器
};
#endif // WIDGET_H
