#include "sortingalgorithms.h"
#include "ui_sortingalgorithms.h"

#include <QRadioButton>
#include <QMessageBox>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QTextStream>


#include <iostream>
#include <cstdlib>

//constructor
SortingAlgorithms::SortingAlgorithms(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SortingAlgorithms)
{
    ui->setupUi(this);

    //Combo Box Type content
    ui->cbType->addItem("int");
    ui->cbType->addItem("double");
    ui->cbType->addItem("string");

    //Radio buttons by default are set to false/not to be clicked/
    ui->rbSequence->setChecked(false);
    ui->rbRandom->setChecked(false);

}//SortingAlgorithms

//destructor
SortingAlgorithms::~SortingAlgorithms()
{
    delete ui;
}//~SortingAlgorithms


//push button Generate
void SortingAlgorithms::on_btnGenerate_clicked()
{

    if(ui->rbSequence->isChecked())
    {
        for (int i = 0; i < 20; i++) //starts from 0
        {
            qDebug() << "Number " << i << ": " << i;
        }
    }
    else if (ui->rbRandom->isChecked())
    {
        QString sequence = " ";
        for (int i = rand_min; i < SIZE; i++) //for int i = rand_min; i is smaller than SIZE (will stop when i is SIZE-1), i + 1
        {
           //print random_number in the terminal section
           //qDebug() << "Random number " << i << ": " << rand() % rand_max + 1; //random_number is now => 1 - rand_max (0 - (rand_max-1) + 1)
            sequence += QString::number(rand() % rand_max + 1)+ " ";
        }
        ui->lbGenerate->setText(sequence);
    }
}//on_btnGenerate_clicked

//push button Clear All
void SortingAlgorithms::on_btnClear_clicked()
{
    ui->lbGenerate->setText("");
    ui->leSize->setText("");
    ui->lbSortedSeq->setText("");
}//on_btnClear_clicked


//push button Sort
void SortingAlgorithms::on_btnSort_clicked()
{

}//on_btnSort_clicked

