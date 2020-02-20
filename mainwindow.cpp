#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcVal=0.0;
bool plusTrigger = false;
bool minusTrigger = false;
bool multiplyTrigger = false;
bool divisionTrigger = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButton[10];

    for(int i=0;i<10;i++)
    {
        QString butName = "Button"+QString::number(i);
        numButton[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButton[i],SIGNAL(released()),this,SLOT(numberPressed()));
    }
    connect(ui->plusButton,SIGNAL(released()),this,SLOT(operationPressed()));
    connect(ui->minusButton,SIGNAL(released()),this,SLOT(operationPressed()));
    connect(ui->multiplyButton,SIGNAL(released()),this,SLOT(operationPressed()));
    connect(ui->divideButton,SIGNAL(released()),this,SLOT(operationPressed()));

    connect(ui->equalButton,SIGNAL(released()),this,SLOT(equalPressed()));

    connect(ui->clearButton,SIGNAL(released()),this,SLOT(clearPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue=button->text();
    QString displayValue = ui->Display->text();

    if((displayValue.toDouble()==0) || (displayValue.toDouble()==0.0))
    {
        ui->Display->setText(buttonValue);
    }
    else
    {
        QString newValue = displayValue + buttonValue;
        double dblNewValue = newValue.toDouble();
        ui->Display->setText(QString::number(dblNewValue,'g',16));
    }

}

void MainWindow::equalPressed()
{
    QString currentValue = ui->Display->text();
    double currentValuetoDbl = currentValue.toDouble();
    double solution=0;
    if(plusTrigger)
    {
        solution=calcVal+currentValuetoDbl;
    }
    else if(minusTrigger)
    {
        solution=calcVal-currentValuetoDbl;
    }
    else if(multiplyTrigger)
    {
        solution=calcVal*currentValuetoDbl;
    }
    else
    {
        solution=calcVal/currentValuetoDbl;
    }
    ui->Display->setText(QString::number(solution));
}

void MainWindow::operationPressed()
{
    plusTrigger = false;
    minusTrigger = false;
    multiplyTrigger = false;
    divisionTrigger = false;
    QPushButton *button = (QPushButton *) sender();
    QString buttonValue=button->text();
    QString currentValue = ui->Display->text();
    calcVal = currentValue.toDouble();
    QString displayValue = ui->Display->text();
    if(buttonValue=="+")
    {
        QString newValue = displayValue+buttonValue;
        ui->Display->setText(newValue);
        plusTrigger = true;
    }
    else if(buttonValue=="-")
    {
        QString newValue = displayValue+buttonValue;
        ui->Display->setText(newValue);
        minusTrigger = true;
    }
    else if(buttonValue=="*")
    {
        QString newValue = displayValue+buttonValue;
        ui->Display->setText(newValue);
        multiplyTrigger = true;
    }
    else
    {
        QString newValue = displayValue+buttonValue;
        ui->Display->setText(newValue);
        divisionTrigger = true;
    }


}

void MainWindow::clearPressed()
{
    calcVal = 0.0;
    ui->Display->setText(QString::number(calcVal));
}

