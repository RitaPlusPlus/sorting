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
LineChart::LineChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineChart)
{
    ui->setupUi(this);

    // create chart and set title for it
    QChart *chart = new QChart();
    chart->setTitle("Execution time comparison");

    // customise the chart title
    QFont tfont;
    tfont.setBold(true); // bold or not
    tfont.setPixelSize(18); // font size
    chart->setTitleFont(tfont);

    // create and set legend at the bottom of the chart
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // create different lines for the chart
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

    int size = 100; // size of the horizontal axis X at the start
    const int d = 100; // difference by which the size is increased after every cycle of the loop
    const int min = 0; // minimum size of the elements in the vector
    const int max = 10; // maximum size of the elements in the vector
    int i = 0;
    while(i++ < 11) {
        // create vectors for every algorithm
        ArrayVector<int> vectorSelectionSort;
        ArrayVector<int> vectorInsertionSort;
        ArrayVector<int> vectorBubbleSort;
        ArrayVector<int> vectorMergeSort;
        ArrayVector<int> vectorQuickSort;

        // generate random sequences
        for (int j = 0; j < size; j++) {
            int num = min + rand() % (max - min + 1);
            vectorSelectionSort.insert_back(num);
            vectorInsertionSort.insert_back(num);
            vectorBubbleSort.insert_back(num);
            vectorMergeSort.insert_back(num);
            vectorQuickSort.insert_back(num);
            // insert_back to replace the new elemnt at index
        }

        // Selection sort
        auto startSelection = high_resolution_clock::now(); // start the timer
        vectorSelectionSort.selectionSort(); // uses selectionSort to sort the vector
        auto stopSelection = high_resolution_clock::now(); // stops the timer
        auto durationSelectionSort = duration_cast<microseconds>(stopSelection - startSelection); // calculates the duration
        *series << QPointF(size-d, durationSelectionSort.count()); // adds value to the lineseries

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


        size += d; // add the difference to the size
    }

    // add every lineseries to the chart
    chart->addSeries(series);
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);

    // display the chart on the window
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // makes the lines in the chart more smooth visualy
    chartView->setParent(ui->horizontalFrame); // where to display the chart

    // customise the horizontal axis X
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Number of elements"); // gives name to the horizontal axis X
    axisX->setRange(0,size-2*d); // range of the horizontal axis X
    axisX->setTickCount(11);// how much sectors example range:0-1000  ticks(5) - 0, 250, 500, 750, 1000
    axisX->setLabelFormat("%.0f");// how many numbers after decimal point
    chart->addAxis(axisX, Qt::AlignBottom); // add a horizontal axis at the bottom of the chart
    // attach all the lines to the horizontal axis X
    series->attachAxis(axisX);
    series1->attachAxis(axisX);
    series2->attachAxis(axisX);
    series3->attachAxis(axisX);
    series4->attachAxis(axisX);

    // customise the vertical axis Y
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Time in microseconds");
    axisY->setRange(0,1000);
    axisY->setTickCount(11);
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY, Qt::AlignLeft); // add a vertical axis at the left of the chart
    // attach all the lines to the vertical axis Y
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


