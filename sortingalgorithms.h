#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include <QMainWindow>
#include "array-vector.h"
#include "linechart.h"

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
        bool manualInput();

        //! UI
        /*!
            UI is public so array-vector.h can access it for visualisation.
            Not a good practise if you have more than one UI windows.
        */
        Ui::SortingAlgorithms *ui;

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
        void on_btnRead_clicked();

        //! Click handler on Write file clicked
        /*!
            write file
        */
        void on_btnWrite_clicked();

        //! Click handler on Visualise clicked
        /*!
            visualise algorithms
        */
        void on_visualiseButton_clicked();

        //! Click handler on Compare complexity clicked
        /*!
            creates a line chart,
            that compares complexity of the sorting algorithms

        */

        void on_Compare_clicked();

    private:
        template <typename T> typename ArrayVector<T>::SORTING_ALGO getSortAlgo();
        template <typename T> typename ArrayVector<T>::SORTING_ALGO_VISUAL getSortAlgoVisual();

        int min;
        int max;
        int size;

        ArrayVector<int> int_vector;
        ArrayVector<double> double_vector;
        ArrayVector<string> string_vector;
        QString sequence;
        QStringList list;
        LineChart *lchart;

};
#endif // SORTINGALGORITHMS_H
