#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include <QMainWindow>
#include "array-vector.h"

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

    void on_btnGenerate_randSeq_clicked(); //push button to Generate a random sequence
    void on_btnClear_clicked();  //push button Clear
    void on_btnSort_clicked();  //push button Sort

    void on_rbMinput_clicked(); //push button Minput - manual input
    void on_rbRandom_clicked(); //push button Random


    void on_rbStr_clicked();
    void on_rbInt_clicked();
    void on_rbDouble_clicked();


private:
    template <typename T> typename ArrayVector<T>::SORTING_ALGO getSortAlgo();
    Ui::SortingAlgorithms *ui;

    int min;
    int max;
    int size;

    ArrayVector<int> int_vector;
    ArrayVector<double> double_vector;
//    ArrayVector<string> string_vector;
     QString sequence;
     int integers_sequence;
     double doubles_sequence;
    //const char alphanum[63] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"}; //numbers,capital and small letters

};
#endif // SORTINGALGORITHMS_H
