#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets/QMessageBox>
#include<QDebug>
#include<QFileDialog>
#include<QDir>
//QDir类用来操作路径名及底层文件系统，获取关于目录路径及文件的相关信息，也可以用来获取Qt资源系统的文件信息。
#include<QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include <QHBoxLayout>
#include<QTime>
#include<QTimer>




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->verticalSlider->setVisible(false);

    mode=0;


    //测试代码-保证暂停播放显示正常
    //if(player.state()==QMediaPlayer::PlayingState)
      //  ui->pushButton_4->setStyleSheet("border-image: url(:/assets/pause.png);");
    m_timer.start(500);
    connect(&m_timer, &QTimer::timeout, this, &Widget::onTimer);


    //对音乐的时间进行关联
    connect(&player, &QMediaPlayer::durationChanged, this,[=](qint64 duration) {
        ui->label2->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
        ui->horizontalSlider->setRange(0,duration);
    });

    connect(&player,&QMediaPlayer::positionChanged,this,[=](qint64 pos)
    {
        ui->label->setText(QString("%1:%2").arg(pos/1000/60,2,10,QChar('0')).arg(pos/1000%60,2,10,QChar('0')));
        ui->horizontalSlider->setValue(pos);
    });



    //当移动滑块的时候，进行播放进度的改变
    connect(ui->horizontalSlider, &QSlider::sliderReleased, this,[=]() {
        player.setPosition(ui->horizontalSlider->value());
        player.play();
    });



    //先设置好音量
    ui->verticalSlider->setValue(player.volume());


    ui->verticalSlider->setRange(0,100);
    connect(ui->verticalSlider, &QSlider::sliderReleased,[=](){
        int value=ui->verticalSlider->value();
        player.setVolume(value);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{

    qInfo()<<"Hello";
    auto path=QFileDialog::getExistingDirectory(this,"请选择音乐所在的目录","D:\\QTproject\\musicplayer\\music");
    //其中，第一个参数是对话框的父窗口；第二个参数是对话框标题；第三个参数是对话框打开的初始目录。

    //根据该目录来进行操作
    QDir dir(path);
    auto musiclist=dir.entryList(QStringList()<<"*.mp3"<<"*.wav");
    //在其中传入了MP3和wav两种匹配模式

    qInfo()<<musiclist;
    ui->musicwidget->addItems(musiclist);

    //默认选中第一个文件
    ui->musicwidget->setCurrentRow(0);


    //把音乐的路径进行保存
    for(auto file:musiclist)
    {
        PLayList.append(QUrl::fromLocalFile(path+"/"+file));
    }

    qInfo()<<PLayList;




}




void Widget::on_pushButton_4_clicked()
{

    QMediaPlayer::State state=player.state();

    //播放当前选中的音乐
    //用下标访问到对应的音乐


    for(auto file:PLayList)
    {
        playlist.addMedia(file);
    }
    int index=ui->musicwidget->currentRow();
    int currentindex=playlist.currentIndex();

    if(index!=currentindex){
        player.setPlaylist(&playlist);

        if (!playlist.isEmpty()) {
            playlist.setCurrentIndex(index);
            player.play();
            ui->pushButton_4->setStyleSheet("border-image: url(:/assets/pause.png);");
        }


        //测试代码
        /*QObject::connect(&player, &QMediaPlayer::durationChanged, this,[=](qint64 duration) {
            ui->label2->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
        });
*/
    }

    else{
    switch(state){

    case QMediaPlayer::PlayingState:
    {
        player.pause();
        ui->pushButton_4->setStyleSheet("border-image: url(:/assets/play.png);");
        break;
    }

    case QMediaPlayer::StoppedState:
    {

        //播放对应下标的音乐
        player.setPlaylist(&playlist);

        if (!playlist.isEmpty()) {
            playlist.setCurrentIndex(index);
            player.play();
            ui->pushButton_4->setStyleSheet("border-image: url(:/assets/pause.png);");
        }


        break;
    }

    case QMediaPlayer::PausedState:
    {
        player.play();
        ui->pushButton_4->setStyleSheet("border-image: url(:/assets/pause.png);");
        break;
    }

    }
    }
}



void Widget::on_pushButton_5_clicked()
{
    int currentindex=playlist.currentIndex();
    int index;

    if(currentindex+1>PLayList.size()-1)
    {
        index=0;
    }

    else {
        index=currentindex+1;
    }

    player.setPlaylist(&playlist);

    if (!playlist.isEmpty()) {
        playlist.setCurrentIndex(index);
        player.play();
        ui->pushButton_4->setStyleSheet("border-image: url(:/assets/pause.png);");
    }
    ui->musicwidget->setCurrentRow(index);
}


void Widget::on_pushButton_3_clicked()
{
    int currentindex=playlist.currentIndex();
    int index;

    if(currentindex-1<0)
    {
        index=PLayList.size()-1;
    }

    else {
        index=currentindex-1;
    }

    player.setPlaylist(&playlist);

    if (!playlist.isEmpty()) {
        playlist.setCurrentIndex(index);
        player.play();
        ui->pushButton_4->setStyleSheet("border-image: url(:/assets/pause.png);");
    }
    ui->musicwidget->setCurrentRow(index);
}








void Widget::on_pushButton_7_clicked()
{
    if(ui->verticalSlider->isVisible()==true)
    ui->verticalSlider->setVisible(false);

    else
    ui->verticalSlider->setVisible(true);
}


void Widget::on_pushButton_2_clicked()
{
    if(mode==0){
        mode++;
    playlist.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        //player.setPlaylist(&playlist);

        ui->pushButton_2->setStyleSheet("border-image: url(:/assets/cycle.png);");
    }

    else if(mode==1){
        mode++;
        playlist.setPlaybackMode(QMediaPlaylist::Random);
        //player.setPlaylist(&playlist);

        ui->pushButton_2->setStyleSheet("border-image: url(:/assets/random.png);");
    }

    else{
        mode=0;
        playlist.setPlaybackMode(QMediaPlaylist::Sequential);
        //player.setPlaylist(&playlist);

        ui->pushButton_2->setStyleSheet("border-image: url(:/assets/list.png);");
    }
}

void Widget::timerEvent(QTimerEvent*)
{
}

void Widget::onTimer()
{
    ui->musicwidget->setCurrentRow(playlist.currentIndex());
}
