#include "sortingalgorithms.h"
#include "ui_sortingalgorithms.h"
#include "linechart.h"

#include <QRadioButton>
#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QGroupBox>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include <cstdlib> //RAND_MAX
#include <string>
#include <iomanip>

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QValueAxis>


#include <chrono>

using namespace std::chrono;

//constructor
SortingAlgorithms::SortingAlgorithms(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SortingAlgorithms)
{
    ui->setupUi(this);

    min = 0;
    max = 0;
    size = 0;
} // SortingAlgorithms

//destructor
SortingAlgorithms::~SortingAlgorithms()
{
    delete ui;
} // ~SortingAlgorithms

//radio button type String - rbStr
void SortingAlgorithms::on_rbStr_clicked()
{
    //a message that informs the user to know that string type only supports the value of Size and Min
    QMessageBox::warning(this,tr("Note"),tr("Note: If you choose way 1:Random,\nyou can only set Size and Length of the string,\n"
                                            "Min value won't be taken \nwhen you press Generate!"),QMessageBox::Cancel);
    if(ui->rbRandom->isChecked())
    {
       //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button String from types
       ui->spinBox_Min->setEnabled(false);
    }
    ui->max_Label->setText("Length:");
} // on_rbStr_clicked

//radio button type Integer
void SortingAlgorithms::on_rbInt_clicked()
{
    if(ui->rbRandom->isChecked())
    {
        //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button Int from types
        ui->spinBox_Min->setEnabled(true);
    }
    ui->max_Label->setText("Max:");
} // on_rbInt_clicked

//radio button type Double
void SortingAlgorithms::on_rbDouble_clicked()
{
    if(ui->rbRandom->isChecked())
    {
        //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button Double from types
        ui->spinBox_Min->setEnabled(true);
        ui->max_Label->setText("Max:");
    }
} // on_rbDouble_clicked

//radio button Minput - Manual Input
void SortingAlgorithms::on_rbMinput_clicked()
{
    //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button Manual Input
    ui->textE_Minput->setEnabled(true);
    ui->spinBox_Min->setEnabled(false);
    ui->spinBox_Max->setEnabled(false);
    ui->spinBox_Size->setEnabled(false);
    ui->btnGenerate_randSeq->setEnabled(false);
    ui->textBrowser_randSeq->setEnabled(false);
} // on_rbMinput_clicked

//radio button rbRandom - Random
void SortingAlgorithms::on_rbRandom_clicked()
{
    //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button Random
    ui->spinBox_Size->setEnabled(true);
    ui->btnGenerate_randSeq->setEnabled(true);
    ui->textBrowser_randSeq->setEnabled(true);
    ui->textE_Minput->setEnabled(false);
    ui->spinBox_Min->setEnabled(true);
    ui->spinBox_Max->setEnabled(true);
    //if the user checks the radio button of String type the spinboxes Min and Max will be unabled
    if(ui->rbStr->isChecked())
    {
       ui->spinBox_Min->setEnabled(false);
    }
} // on_rbRandom_clicked

//push button Generate works only when whant to generate a Random sequence (i.e. when we checked radio button Random)
void SortingAlgorithms::on_btnGenerate_randSeq_clicked()
{
    //set the variables (size,min and max) to have a connection to the spinBox-es from the user interface
    min = ui->spinBox_Min->value();
    max = ui->spinBox_Max->value();
    size = ui->spinBox_Size->value();

    if(min > max)
    {
        QMessageBox::critical(this,"Title","Error: Min value should be smaller than Max value!\nChange the values where it's needed!",QMessageBox::Ok);
    }
    else
    {
        //if type is INTEGER
        if(ui->rbInt->isChecked())
        {
            sequence = "";
            int_vector.clear();
            int_vector.reserve(size);
            for (int i = 0; i < size; i++)
            {
                int num = min + rand() % (max - min + 1);
                int_vector.insert_back(num);
                sequence += QString::number(num) + " ";
            }
            ui->textBrowser_randSeq->setText(sequence);
        }
        //else if type is DOUBLE
        else if(ui->rbDouble->isChecked())
        {
            sequence = "";
            double_vector.clear();
            double_vector.reserve(size);
            for (int i = 0; i < size; i++)
            {
                double num = min + rand() / (float)RAND_MAX * (max - min + 1);
                double_vector.insert_back(num);
                sequence += QString::number(num) + " ";
            }
            ui->textBrowser_randSeq->setText(sequence);
        }
        //else if type is STRING
        else if(ui->rbStr->isChecked())
        {
            sequence = "";

            const char alphanum[] =
                 {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"}; // numbers,capital and small letters

            string_vector.clear();
            string_vector.reserve(size);
            for (int i = 0; i < size; ++i)
            {
                string temp = "";
                for (int i = 0; i < max; ++i)
                {
                    temp += alphanum[rand() % (sizeof(alphanum) - 1)];
                }
                string_vector.insert_back(temp);
                sequence += QString::fromStdString(temp + " ");
            }
            ui->textBrowser_randSeq->setText(sequence);
        }
    }

} // on_btnGenerate_clicked

//If user has selected manual input radio button or reading text files
bool SortingAlgorithms::manualInput()
{
    int_vector.clear();
    double_vector.clear();
    string_vector.clear();
    //takes users input from manual input textbox
    sequence = ui->textE_Minput->toPlainText();
    bool ok;

    //if type is INT
   if(ui->rbInt->isChecked())
    {
        list = sequence.split(" ");

        foreach(QString num, list)
        {
            int_vector.insert_back(num.toInt(&ok));
            if(!ok)
            {
                QMessageBox::critical(this,tr("Missing"),tr("Input contains a non-numeric value!"), QMessageBox::Cancel);
                return false;
            }
        }
    }
    //else if type is DOUBLE
    else if(ui->rbDouble->isChecked())
    {
        list = sequence.split(" ");

        foreach(QString num, list)
        {
            double_vector.insert_back(num.toDouble(&ok));
            if(!ok)
            {
                QMessageBox::critical(this,tr("Missing"),tr("Input contains a non-numeric value!"), QMessageBox::Cancel);
                return false;
            }
        }
    }
    //else if type is STRING
    else if(ui->rbStr->isChecked())
    {
        list = sequence.split(" ");

        foreach(QString num, list)
        {
            string_vector.insert_back(num.toStdString());
        }
    }
    else
    {
        QMessageBox::warning(this,tr("Missing"),tr("You don't have a variable type selected!"), QMessageBox::Cancel);
    }

    return true;
} // manualInput

//push button Clear All
void SortingAlgorithms::on_btnClear_clicked()
{
    //clears the vectors
    int_vector.clear();
    double_vector.clear();
    string_vector.clear();

    //sets the textEdit and the two textBrowsers values to null
    ui->textE_Minput->setText("");
    ui->textBrowser_randSeq->setText("");
    ui->textBrowser_sortedSeq->setText("");

    //sets the spinBoxes values to null
    ui->spinBox_Min->setValue(0);
    ui->spinBox_Max->setValue(0);
    ui->spinBox_Size->setValue(0);

    //set them to be enabled
    ui->textE_Minput->setEnabled(true);
    ui->spinBox_Min->setEnabled(true);
    ui->spinBox_Max->setEnabled(true);
    ui->spinBox_Size->setEnabled(true);
    ui->btnGenerate_randSeq->setEnabled(true);
    ui->textBrowser_randSeq->setEnabled(true);

    //set the different groups of Radio buttons for Types,Random/Manual input and Sorting Algorithms - to null
    if(ui->Types_int_double_str_RbGroup->checkedButton() != 0)
    {
        ui->Types_int_double_str_RbGroup->setExclusive(false);
        ui->Types_int_double_str_RbGroup->checkedButton()->setChecked(false);
        ui->Types_int_double_str_RbGroup->setExclusive(true);
    }
    if(ui->Rand_or_Input_RbGroup->checkedButton() != 0)
    {
        ui->Rand_or_Input_RbGroup->setExclusive(false);
        ui->Rand_or_Input_RbGroup->checkedButton()->setChecked(false);
        ui->Rand_or_Input_RbGroup->setExclusive(true);
    }
    if(ui->Sorting_algos_RbGroup->checkedButton() != 0)
    {
        ui->Sorting_algos_RbGroup->setExclusive(false);
        ui->Sorting_algos_RbGroup->checkedButton()->setChecked(false);
        ui->Sorting_algos_RbGroup->setExclusive(true);
    }

} // on_btnClear_clicked

template <typename T>
typename ArrayVector<T>::SORTING_ALGO SortingAlgorithms::getSortAlgo() {
    if(ui->rbSelectionS->isChecked())
    {
        return ArrayVector<T>::SELECTION_SORT;
    }
    else if(ui->rbInsertionS->isChecked())
    {
        return ArrayVector<T>::INSERTION_SORT;
    }
    else if(ui->rbBubbleS->isChecked())
    {
        return ArrayVector<T>::BUBBLE_SORT;
    }
    else if(ui->rbQuickS->isChecked())
    {
        return ArrayVector<T>::QUICK_SORT;
    }
    else if(ui->rbMergeS->isChecked())
    {
        return ArrayVector<T>::MERGE_SORT;
    }
    else
    {
        QMessageBox::warning(this,tr("Missing"),tr("You don't have a sorting algorithm selected."), QMessageBox::Cancel);
        return ArrayVector<T>::NONE;
    }
} // getSortAlgo

//push button Sort
void SortingAlgorithms::on_btnSort_clicked()
{
    //if manual input button is selected and manual is false, returns the function
    //but if manual input button is selected and its true it will use the manual input
    if(ui->rbMinput->isChecked() && manualInput() == false)
    {
        return;
    }

    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    if(ui->rbInt->isChecked())
    {
      int_vector.sort(getSortAlgo<int>());
      stop = high_resolution_clock::now();
      sequence = int_vector.toString();
    }
    //else if type is DOUBLE
    else if(ui->rbDouble->isChecked())
    {
        double_vector.sort(getSortAlgo<double>());
        stop = high_resolution_clock::now();
        sequence = double_vector.toString();
    }
    //else if type is STRING
    else if(ui->rbStr->isChecked())
    {
        string_vector.sort(getSortAlgo<string>());
        stop = high_resolution_clock::now();
        sequence = string_vector.join(' ');
    }
    else
    {
        QMessageBox::warning(this,tr("Missing"),tr("You don't have variable type selected!"), QMessageBox::Cancel);
    }

    auto duration = duration_cast<microseconds>(stop - start);
    ui->timeTaken_Label->setText(QString::fromStdString("Time taken in microseconds: " + to_string(duration.count())));
    ui->textBrowser_sortedSeq->setText(sequence); //print the result in textBrowser_sortedSeq

} // on_btnSort_clicked

//push button to read a text file
void SortingAlgorithms::on_btnRead_clicked()
{
    if(ui->rbMinput->isChecked())
    {
        QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
        QFile file(file_name);

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "title", "file not open");
        }
        else
        {
            QMessageBox::information(this, "..", file_name);
        }
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textE_Minput->setPlainText(text);

        file.close();
    }
    else
    {
        QMessageBox::warning(this,tr("Missing"),tr("Select Manual Input before opening a text file!"), QMessageBox::Ok);
    }
} // on_btnRead_clicked

//push button to write a text file
void SortingAlgorithms::on_btnWrite_clicked()
{
    // open a window to name and save the file
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save As"), "",
            tr("Text Documents (*.txt);;All Files (*)"));

    // if no name is given and you try to save nothing happens
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) // if we cant save on the selected file an error message pops
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream out(&file); // reference
        QString text = ui->textBrowser_sortedSeq->toPlainText(); // sets the text as plain text
        out << text; // writes the text
        file.close(); // close the file after saving
    }
} // on_btnWrite_clicked

//Gets the sorting algorithm to visualise it
template <typename T>
typename ArrayVector<T>::SORTING_ALGO_VISUAL SortingAlgorithms::getSortAlgoVisual()
{
    if(ui->rbSelectionS->isChecked())
    {
        return ArrayVector<T>::SELECTION_SORT_VISUAL;
    }
    else if(ui->rbInsertionS->isChecked())
    {
        return ArrayVector<T>::INSERTION_SORT_VISUAL;
    }
    else if(ui->rbBubbleS->isChecked())
    {
        return ArrayVector<T>::BUBBLE_SORT_VISUAL;
    }
    else if(ui->rbQuickS->isChecked())
    {
        return ArrayVector<T>::QUICK_SORT_VISUAL;
    }
    else if(ui->rbMergeS->isChecked())
    {
        return ArrayVector<T>::MERGE_SORT_VISUAL;
    }
    else
    {
        QMessageBox::warning(this,tr("Missing"),tr("You don't have a sorting algorithm selected."), QMessageBox::Cancel);
        return ArrayVector<T>::NONE_VISUAL;
    }
} // getSortAlgoVisual

//Push button to visualise the algorithms
void SortingAlgorithms::on_visualiseButton_clicked()
{
    //if manual input button is selected and manual is false, returns the function
    //but if manual input button is selected and its true it will use the manual input
    if(ui->rbMinput->isChecked() && manualInput() == false)
    {
        return;
    }
    //if type is INT
    if(ui->rbInt->isChecked())
    {
      int_vector.sortVisual(getSortAlgoVisual<int>(), ui);
      sequence = int_vector.toString();
    }
    //else if type is DOUBLE
    else if(ui->rbDouble->isChecked())
    {
        double_vector.sortVisual(getSortAlgoVisual<double>(), ui);
        sequence = double_vector.toString();
    }
    else
    {
        QMessageBox::warning(this,tr("Missing"),tr("For visualisation select INT or DOUBLE!"), QMessageBox::Cancel);
    }
}// on_visualiseButton_clicked

// push button to display line chart
void SortingAlgorithms::on_Compare_clicked()
{
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
    //chartView->resizeEvent

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

    QDialog* dialog = new QDialog();// create new dialog window
    dialog->resize(800, 600);// set size for dialog
    dialog->setWindowTitle("Line chart comparison");// set name for dialog
    QVBoxLayout* layoutDialog = new QVBoxLayout(dialog);// add layout to the dialog

    QWidget* widget = new QWidget();// create new widget
    QVBoxLayout* layoutWidget = new QVBoxLayout(widget);// add layout to the widget

    layoutDialog->addWidget(widget);// insert the widget in the dialog
    layoutWidget->addWidget(chartView);// insert the cahrt in the widget

    dialog->exec();
}// on_Compare_clicked
