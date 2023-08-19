#ifndef MUSIC_H
#define MUSIC_H

#include <QMediaPlayer>   // 播放器
#include <QMediaPlaylist> // 播放列表
#include <QSound>

// QT += multimedia

// 循环播放一个音乐文件
void musicPlay(QString filename);

// 停止播放音乐
void musicStop();

// QSound::play(":/sound/alarm.wav");

#endif // MUSIC_H
