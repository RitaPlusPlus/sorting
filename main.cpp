#include "sortingalgorithms.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QTextStream>
#include <iostream>
//<QIODevice>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortingAlgorithms w;
    w.show();


    return a.exec();
}//main
