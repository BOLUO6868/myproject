#include "formSetting.h"
#include "ui_formSetting.h"

#include "audio.h"
#include "formGame.h"

#include <QMessageBox>
#include <QDebug>

// 音乐列表
const QStringList Music = {
    ":/assets/Background_HighBattle.mp3",
    ":/assets/Background_NormalBattle.mp3",
    ":/assets/Background_World.mp3",
};

// 默认设置
static GameSetting _m_defaultSetting = {
    "none user",
    ":/assets/bg1.jpg",
    Music[0],
    Qt::Key_Up,
    Qt::Key_Down,
    Qt::Key_Left,
    Qt::Key_Right,
    Qt::Key_P,
};

// 当前设置
static GameSetting _m_currentSetting = _m_defaultSetting;

// 快捷键转 key
Qt::Key getKey(QKeySequence ks)
{
    if (ks.count() == 0) {
        return Qt::Key(0);
    }
    else {
        return (Qt::Key) ks[0];
    }
}

FormSetting::FormSetting(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::FormSetting)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");                                              // 标题
    this->setFixedSize(800, 600);                                              // 固定大小窗口
    this->setStyleSheet("#FormSetting{border-image: url(:/assets/bg4.jpg);}"); // 背景图片

    // 音乐列表
    int id;
    for (int i = 0; i < Music.size(); ++i) {
        QString str = Music[i];
        id          = str.lastIndexOf('/');
        ui->listMusic->addItem(str.right(str.length() - id - 1));
    }
    id = Music.indexOf(_m_currentSetting.bgm);
    if (id != -1) {
        ui->listMusic->setCurrentItem(ui->listMusic->item(id));
    }
    // ui->listMusic->setSelectionRectVisible(true);

    // 按键设置
    ui->keyEditRotate->setKeySequence(_m_currentSetting.keyUp);
    ui->keyEditMoveLeft->setKeySequence(_m_currentSetting.keyLeft);
    ui->keyEditMoveRight->setKeySequence(_m_currentSetting.keyRight);
    ui->keyEditDown->setKeySequence(_m_currentSetting.keyDown);
    ui->keyEditPause->setKeySequence(_m_currentSetting.keyPause);

    // 只能接受一个按键
    connect(ui->keyEditRotate, &QKeySequenceEdit::keySequenceChanged, [=]() {
        QKeySequence ks = ui->keyEditRotate->keySequence();
        if (ks.count() > 1) {
            ui->keyEditRotate->setKeySequence(ks[ks.count() - 1]);
        }
    });

    connect(ui->keyEditMoveLeft, &QKeySequenceEdit::keySequenceChanged, [=]() {
        QKeySequence ks = ui->keyEditMoveLeft->keySequence();
        if (ks.count() > 1) {
            ui->keyEditMoveLeft->setKeySequence(ks[ks.count() - 1]);
        }
    });

    connect(ui->keyEditMoveRight, &QKeySequenceEdit::keySequenceChanged, [=]() {
        QKeySequence ks = ui->keyEditMoveRight->keySequence();
        if (ks.count() > 1) {
            ui->keyEditMoveRight->setKeySequence(ks[ks.count() - 1]);
        }
    });

    connect(ui->keyEditDown, &QKeySequenceEdit::keySequenceChanged, [=]() {
        QKeySequence ks = ui->keyEditDown->keySequence();
        if (ks.count() > 1) {
            ui->keyEditDown->setKeySequence(ks[ks.count() - 1]);
        }
    });

    connect(ui->keyEditPause, &QKeySequenceEdit::keySequenceChanged, [=]() {
        QKeySequence ks = ui->keyEditPause->keySequence();
        if (ks.count() > 1) {
            ui->keyEditPause->setKeySequence(ks[ks.count() - 1]);
        }
    });

    // 界面按钮
    connect(ui->buttonOk, &QToolButton::clicked, [=] { // 确定
        // 音乐
        int id = ui->listMusic->currentRow();
        if (id != -1) {
            _m_currentSetting.bgm = Music[id];
        }

        // 如果正在游戏，更改音乐
        FormGame* game = dynamic_cast<FormGame*>(this->parentWidget());
        if (game) {
            musicPlay(_m_currentSetting.bgm);
        }

        // 按键
        _m_currentSetting.keyUp    = getKey(ui->keyEditRotate->keySequence());
        _m_currentSetting.keyLeft  = getKey(ui->keyEditMoveLeft->keySequence());
        _m_currentSetting.keyRight = getKey(ui->keyEditMoveRight->keySequence());
        _m_currentSetting.keyDown  = getKey(ui->keyEditDown->keySequence());
        _m_currentSetting.keyPause = getKey(ui->keyEditPause->keySequence());

        close();
    });

    connect(ui->buttonCancel, &QToolButton::clicked, [=] { // 取消
        close();
    });


    // 背景图片
    connect(ui->btnBg1, &QToolButton::clicked, [=] {
        _m_currentSetting.background = ":/assets/bg1.jpg";
    });
    connect(ui->btnBg2, &QToolButton::clicked, [=] {
        _m_currentSetting.background = ":/assets/bg2.jpg";
    });
    connect(ui->btnBg3, &QToolButton::clicked, [=] {
        _m_currentSetting.background = ":/assets/bg3.jpg";
    });
    connect(ui->btnBg4, &QToolButton::clicked, [=] {
        _m_currentSetting.background = ":/assets/bg4.jpg";
    });
}

FormSetting::~FormSetting()
{
    delete ui;
}

// 返回默认设置
GameSetting FormSetting::defaultSetting()
{
    return _m_defaultSetting;
}

// 返回当前设置
GameSetting FormSetting::currentSetting()
{
    return _m_currentSetting;
}
