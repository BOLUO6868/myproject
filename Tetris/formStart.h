#ifndef FORMSTART_H
#define FORMSTART_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class FormStart;
}

class FormStart : public QWidget
{
    Q_OBJECT

public:
    explicit FormStart(QWidget *parent = nullptr);
    ~FormStart();

private:
    Ui::FormStart *ui;
};

#endif // FORMSTART_H
