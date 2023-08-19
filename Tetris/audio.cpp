#include "audio.h"

// 播放器对象
QMediaPlayer musicPlayer;
// 播放列表
QMediaPlaylist playList;

// 循环播放一个mp3
void musicPlay(QString filename)
{
    // 清空播放列表
    playList.clear();

    // 把音乐文件添加进列表
    if (filename[0] == ':') {
        playList.addMedia(QMediaContent("qrc" + (filename)));
    }
    else {
        playList.addMedia(QUrl(filename));
    }

    // 设置播放模式为循环
    playList.setPlaybackMode(QMediaPlaylist::Loop);

    // 设置播放器的播放列表，并播放
    musicPlayer.setPlaylist(&playList);
    musicPlayer.play();
}

void musicStop()
{
    // 直接停止
    // if(musicPlayer.state() == QMediaPlayer::State::PlayingState){
    musicPlayer.stop();
    // }
}
