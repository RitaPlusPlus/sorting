#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SortingAlgorithms; }
QT_END_NAMESPACE

class SortingAlgorithms : public QMainWindow
{
    Q_OBJECT

public:
    SortingAlgorithms(QWidget *parent = nullptr); //constructor
    ~SortingAlgorithms(); //destructor

private slots:
    void on_btnGenerate_clicked(); //push button Generate
    void on_btnClear_clicked();  //push button Clear All
    void on_btnSort_clicked();  //push button Sort

private:
    Ui::SortingAlgorithms *ui;

    const int SIZE = 10;
    const int rand_min = 0;
    const int rand_max = 40;
    int random_number;
};
#endif // SORTINGALGORITHMS_H
