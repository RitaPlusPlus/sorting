#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include <QMainWindow>
#include "array-vector.h"

QT_BEGIN_NAMESPACE namespace Ui { class SortingAlgorithms; } QT_END_NAMESPACE

class SortingAlgorithms : public QMainWindow
{
    Q_OBJECT

    public:
        SortingAlgorithms(QWidget *parent = nullptr); //  constructor
        ~SortingAlgorithms(); //  destructor
        void manualInput();


    private slots:

        void on_btnGenerate_randSeq_clicked(); // push button to Generate a random sequence
        void on_btnClear_clicked(); // push button Clear
        void on_btnSort_clicked(); // push button Sort

        void on_rbMinput_clicked(); // radio button Minput - manual input
        void on_rbRandom_clicked(); // radio button Random

        void on_rbStr_clicked(); // radio button String
        void on_rbInt_clicked(); // radio button Integer
        void on_rbDouble_clicked(); // radio button Double

        void on_pushButton_2_clicked();//read file button

    private:
        template <typename T> typename ArrayVector<T>::SORTING_ALGO getSortAlgo();
        Ui::SortingAlgorithms *ui;

        int min;
        int max;
        int size;

        ArrayVector<int> int_vector;
        ArrayVector<double> double_vector;
        ArrayVector<string> string_vector;
        QString sequence;
        QStringList list;

};
#endif // SORTINGALGORITHMS_H
