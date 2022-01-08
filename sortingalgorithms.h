#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include <QMainWindow>
#include "array-vector.h"

QT_BEGIN_NAMESPACE namespace Ui { class SortingAlgorithms; } QT_END_NAMESPACE

class SortingAlgorithms : public QMainWindow
{
    Q_OBJECT

    public:
        //! Default constructor
        /*!
            Default constructor
            \param parent    parent widget
        */
        SortingAlgorithms(QWidget *parent = nullptr);

        //! Destructor
        /*!
            Destructor
        */
        ~SortingAlgorithms();

        //! Manual input
        /*!
            Manual input parsing
        */
        void manualInput();


    private slots:

        //! Click handler on Generate clicked
        /*!
            Generate a random sequence
        */
        void on_btnGenerate_randSeq_clicked();

        //! Click handler on Clear clicked
        /*!
            Clear the forms
        */
        void on_btnClear_clicked();

        //! Click handler on Sort clicked
        /*!
            Sort the elements
        */
        void on_btnSort_clicked();

        //! Click handler on Manual input selected
        /*!
            Manual inputted elements
        */
        void on_rbMinput_clicked();

        //! Click handler on Random clicked
        /*!
            Rondomly generated elements
        */
        void on_rbRandom_clicked();

        //! Click handler on String selected
        /*!
            elements of type string
        */
        void on_rbStr_clicked();

        //! Click handler on Integer selected
        /*!
            elements of type integer
        */
        void on_rbInt_clicked();

        //! Click handler on Double selected
        /*!
            elements of type double
        */
        void on_rbDouble_clicked();

        //! Click handler on Read file clicked
        /*!
            read file
        */
        void on_pushButton_2_clicked();

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
