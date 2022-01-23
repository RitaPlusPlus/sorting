#ifndef LINECHART_H
#define LINECHART_H

#include <QDialog>

namespace Ui {
class LineChart;
}

class LineChart : public QDialog
{
    Q_OBJECT

public:
    explicit LineChart(QWidget *parent = nullptr);
    ~LineChart();

private:
    Ui::LineChart *ui;
};

#endif // LINECHART_H
