#ifndef FORMHISTORY_H
#define FORMHISTORY_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class FormHistory;
}

class FormHistory : public QDialog
{
    Q_OBJECT

public:
    explicit FormHistory(QWidget* parent = nullptr);
    ~FormHistory();

private:
    Ui::FormHistory* ui;
};

#endif // FORMHISTORY_H
