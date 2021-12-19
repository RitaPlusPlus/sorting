#include "sortingalgorithms.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QTextStream>
#include <iostream>


int main(int argc, char *argv[])
{
    /*
    ArrayVector<int> b;
    b.insert(0, 5);
    b.insert(0, 6);
    b.insert_back(9);

    cout << b.at(2) << endl;
    b.erase_back();
    cout << b.at(0) << endl;
    b[0] = 5;
    cout << b.at(0) << endl;

    b.sort(ArrayVector<int>::SELECTION_SORT);
    */
    QApplication a(argc, argv);
    SortingAlgorithms w;
    w.show();


    return a.exec();
}//main
