#include "formHistory.h"
#include "ui_formHistory.h"

#include "database/history.h"

FormHistory::FormHistory(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::FormHistory)
{
    ui->setupUi(this);
    this->setWindowTitle("排行榜");                                            // 标题
    this->setFixedSize(800, 600);                                              // 固定大小窗口
    this->setStyleSheet("#FormHistory{border-image: url(:/assets/bg4.jpg);}"); // 背景图片

    QTableWidget* tab = ui->tableWidget;

    tab->setColumnWidth(0, 300);                        // 列宽度
    tab->setColumnWidth(1, 300);
    tab->setEditTriggers(QTableWidget::NoEditTriggers); // 不可编辑
    tab->setGridStyle(Qt::PenStyle::NoPen);             // 不显示网格线
    tab->setSelectionMode(QTableWidget::NoSelection);   // 不可选择
    tab->verticalHeader()->setVisible(false);           // 不显示竖向表头

    // 读取记录
    QTableWidgetItem* item;

    qDebug() << "history: " << history.size();
    tab->setRowCount(history.size());
    for (int i = 0; i < history.size(); ++i) {
        ScoreData data = history.getData(i);

        item = new QTableWidgetItem(data.name);
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        tab->setItem(i, 0, item);

        item = new QTableWidgetItem(QString::number(data.score));
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        tab->setItem(i, 1, item);
    }

    // 按钮
    connect(ui->buttonClear, &QToolButton::clicked, [=] { // 清空
        history.clear();
        history.save("scores.xml");
        ui->tableWidget->setRowCount(0);
    });

    connect(ui->buttonBack, &QToolButton::clicked, [=] { // 返回
        close();
    });
}

FormHistory::~FormHistory()
{
    delete ui;
}
