#ifndef FORMSETTING_H
#define FORMSETTING_H

#include <QDialog>
#include "mainwindow.h"
#include "database/users.h"

namespace Ui {
class FormSetting;
}

class FormSetting : public QDialog
{
    Q_OBJECT

public:
    explicit FormSetting(QWidget* parent = nullptr);
    ~FormSetting();

    // 返回默认设置
    static GameSetting defaultSetting();

    // 返回当前设置
    static GameSetting currentSetting();

private:
    Ui::FormSetting* ui;
};

#endif // FORMSETTING_H
