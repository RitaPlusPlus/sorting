#include "linechart.h"
#include "ui_linechart.h"
#include "array-vector.h"
#include "sortingalgorithms.h"

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QValueAxis>

#include <chrono>

using namespace std::chrono;
//time form sorthingalg.cpp 310
LineChart::LineChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineChart)
{
    ui->setupUi(this);

    QChart *chart = new QChart();
    chart->setTitle("Execution time comparison");

    QFont tfont;
    tfont.setBold(true);
    tfont.setPixelSize(18);
    chart->setTitleFont(tfont);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QLineSeries *series = new QLineSeries();
    series->setName("SelectionSort");

    QLineSeries *series1 = new QLineSeries();
    series1->setName("InsertionSort");

    QLineSeries *series2 = new QLineSeries();
    series2->setName("BubbleSort");

    QLineSeries *series3 = new QLineSeries();
    series3->setName("MergeSort");

    QLineSeries *series4 = new QLineSeries();
    series4->setName("QuickSort");

    int size = 100;
    const int d = 100;
    const int min = 0;
    const int max = 10;
    int i = 0;
    while(i++ < 11) {
        // generate random sequence with size size
        ArrayVector<int> vectorSelectionSort;
        ArrayVector<int> vectorInsertionSort;
        ArrayVector<int> vectorBubbleSort;
        ArrayVector<int> vectorMergeSort;
        ArrayVector<int> vectorQuickSort;

        for (int j = 0; j < size; j++) {
            int num = min + rand() % (max - min + 1);
            vectorSelectionSort.insert_back(num);
            vectorInsertionSort.insert_back(num);
            vectorBubbleSort.insert_back(num);
            vectorMergeSort.insert_back(num);
            vectorQuickSort.insert_back(num);

        }

        // Selection sort
        auto startSelection = high_resolution_clock::now();
        vectorSelectionSort.selectionSort();
        auto stopSelection = high_resolution_clock::now();
        auto durationSelectionSort = duration_cast<microseconds>(stopSelection - startSelection);
        *series << QPointF(size-d, durationSelectionSort.count());

        // Insertion sort
        auto startInsertion = high_resolution_clock::now();
        vectorInsertionSort.insertionSort();
        auto stopInsertion = high_resolution_clock::now();
        auto durationInsertionSort = duration_cast<microseconds>(stopInsertion - startInsertion);
        *series1 << QPointF(size-d, durationInsertionSort.count());

        // Bubble sort
        auto startBubble = high_resolution_clock::now();
        vectorBubbleSort.bubbleSort();
        auto stopBubble = high_resolution_clock::now();
        auto durationBubbleSort = duration_cast<microseconds>(stopBubble - startBubble);
        *series2 << QPointF(size-d, durationBubbleSort.count());

        // Merge sort
        auto startMerge = high_resolution_clock::now();
        vectorMergeSort.mergeSort();
        auto stopMerge = high_resolution_clock::now();
        auto durationMergeSort = duration_cast<microseconds>(stopMerge - startMerge);
        *series3 << QPointF(size-d, durationMergeSort.count());

        // Quick sort
        auto startQuick = high_resolution_clock::now();
        vectorQuickSort.mergeSort();
        auto stopQuick = high_resolution_clock::now();
        auto durationQuickSort = duration_cast<microseconds>(stopQuick - startQuick);
        *series4 << QPointF(size-d, durationQuickSort.count());


        size += d;
    }


    chart->addSeries(series);
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Number of elements");
    axisX->setRange(0,size-2*d);
    axisX->setTickCount(11);//how much sectors example 1000/2-0,1000
    axisX->setLabelFormat("%.0f");//how many numbers after decimal point
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    series1->attachAxis(axisX);
    series2->attachAxis(axisX);
    series3->attachAxis(axisX);
    series4->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Time in microseconds");
    axisY->setRange(0,1000);
    axisY->setTickCount(11);
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    series1->attachAxis(axisY);
    series2->attachAxis(axisY);
    series3->attachAxis(axisY);
    series4->attachAxis(axisY);

}

LineChart::~LineChart()
{
    delete ui;
}

