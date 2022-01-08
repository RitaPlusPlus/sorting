#include "sortingalgorithms.h"
#include "ui_sortingalgorithms.h"

#include <QRadioButton>
#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QGroupBox>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <iostream>
#include <cstdlib> //RAND_MAX
#include <string>
#include <iomanip>



//constructor
SortingAlgorithms::SortingAlgorithms(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SortingAlgorithms)
{
    ui->setupUi(this);

    min = 0;
    max = 0;
    size = 0;
    integers_sequence = 0;
    doubles_sequence = 0;
}//SortingAlgorithms

//destructor
SortingAlgorithms::~SortingAlgorithms()
{
    delete ui;
}//~SortingAlgorithms


//radio button type String - rbStr
void SortingAlgorithms::on_rbStr_clicked()
{
    //a message that informs the user to know that string type only supports the value of Size
    QMessageBox::warning(this,tr("Note"),tr("Note: If you choose way 1:Random,\nyou can only set Size of the string,\n"
                                            "Min and Max values won't be taken \nwhen you press Generate!"),QMessageBox::Cancel);
    if(ui->rbRandom->isChecked())
    {
       //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button String from types
       ui->spinBox_Min->setEnabled(false);
       ui->spinBox_Max->setEnabled(false);
    }
}//on_rbStr_clicked

//radio button type Integer
void SortingAlgorithms::on_rbInt_clicked()
{
    if(ui->rbRandom->isChecked())
    {
        //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button Int from types
        ui->spinBox_Min->setEnabled(true);
        ui->spinBox_Max->setEnabled(true);
    }
}//on_rbInt_clicked

//radio button type Double
void SortingAlgorithms::on_rbDouble_clicked()
{
    if(ui->rbRandom->isChecked())
    {
        //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button Double from types
        ui->spinBox_Min->setEnabled(true);
        ui->spinBox_Max->setEnabled(true);
    }
}//on_rbDouble_clicked


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
}//on_rbMinput_clicked

//radio button rbRandom - Random
void SortingAlgorithms::on_rbRandom_clicked()
{
    //shows which parts of the ui are enabled(true) or unenabled(false) if the user clicks radio button Random
    ui->spinBox_Size->setEnabled(true);
    ui->btnGenerate_randSeq->setEnabled(true);
    ui->textBrowser_randSeq->setEnabled(true);
    ui->textE_Minput->setEnabled(false);
    //if the user checks the radio button of String type the spinboxes Min and Max will be unabled
    if(ui->rbStr->isChecked())
    {
       ui->spinBox_Min->setEnabled(false);
       ui->spinBox_Max->setEnabled(false);
    }
}//on_rbRandom_clicked

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
                 {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"}; //numbers,capital and small letters

                for (int i = 0; i < size; ++i)
                {
                    char ch = alphanum[rand() % (sizeof(alphanum) - 1)];
//                    string_vector.insert_back(ch);
                    sequence = sequence + ch + " ";
                }
                ui->textBrowser_randSeq->setText(sequence);
        }
    }

}//on_btnGenerate_clicked

//push button Clear All
void SortingAlgorithms::on_btnClear_clicked()
{
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

}//on_btnClear_clicked

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
        QMessageBox::warning(this,tr("Missing"),tr("You don't have sorting algo selected"), QMessageBox::Cancel);
        return ArrayVector<T>::NONE;
    }
}

//push button Sort
void SortingAlgorithms::on_btnSort_clicked()
{
    if(ui->rbInt->isChecked())
    {
        int_vector.sort(getSortAlgo<int>());
        sequence = int_vector.toString();
    }
    //else if type is DOUBLE
    else if(ui->rbDouble->isChecked())
    {
        //double_vector = sequence.toDouble();
        double_vector.sort(getSortAlgo<double>());
        sequence = double_vector.toString();
    }
    //else if type is STRING
    else if(ui->rbStr->isChecked())
    {
//        string_vector.sort(getSortAlgo<string>());
    }
        ui->textBrowser_sortedSeq->setText(sequence); //print the result in textBrowser_sortedSeq
}//on_btnSort_clicked



void SortingAlgorithms::on_pushButton_2_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QMessageBox::information(this, "..", file_name);
    QFile file(file_name);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit_File_Name->setPlainText(text);

    file.close();
}



