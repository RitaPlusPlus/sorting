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

    QLineSeries *series = new QLineSeries();
    series->setName("SelectionSort");

    int size = 100;
    const int d = 100;
    int i = 0;
    while(i++ < 10) {
        // generate random sequence with size size
        ArrayVector<int> vectorInsertionSort;
        for (int i = 0; i < size; i++) {
            int num = min + rand() % (max - min + 1);
            vectorInsertionSort.insert_back(num);
        }
        // Insertion sort
        auto startInsertion = high_resolution_clock::now();
        vectorInsertionSort.insertionSort();
        auto stopInsertion = high_resolution_clock::now();
        auto durationInsertionSort = duration_cast<microseconds>(stopInsertion - startInsertion);
        *series << QPointF(size, durationInsertionSort);

        // other algorithms
        size += d;
    }



    //*series << QPointF(0, 0) << QPointF(startingX, 200) << QPointF(100000, 500)
            //<< QPointF(500000, 800) << QPointF(700000, 2000);

    QLineSeries *series1 = new QLineSeries();
    series1->setName("InsertionSort");


    QLineSeries *series2 = new QLineSeries();
    series2->setName("BubbleSort");


    QLineSeries *series3 = new QLineSeries();
    series3->setName("MergeSort");


    QLineSeries *series4 = new QLineSeries();
    series4->setName("QuickSort");


    QChart *chart = new QChart();
    //chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);
    chart->createDefaultAxes();
    chart->setTitle("Line Chart");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Elements");
    axisX->setRange(0,100000);
    axisX->setTickCount(11);//how much sectors example 1000/2-0,1000
    axisX->setLabelFormat("%.0f");//how many numbers after decimal point
    chartView->chart()->setAxisX(axisX,series);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Time");
    axisY->setRange(0,10);
    axisY->setTickCount(11);
    axisY->setLabelFormat("%.0f");
    chartView->chart()->setAxisY(axisY,series);
}

LineChart::~LineChart()
{
    delete ui;
}

