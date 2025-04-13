#include "dialog.h"
#include "ui_dialog.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QFile>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    this->hide();
}

QString userExcercise;

void Dialog::on_excer_inpt_editingFinished()
{
    userExcercise = ui->excer_inpt->text();
}

void Dialog::on_pushButton_clicked()
{
    QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\excercises.txt";
    QFile excercisesFile(filename);
    if(excercisesFile.open(QIODevice::Append | QIODevice::Text)){
        QTextStream out(&excercisesFile);
        out <<"\n"<< userExcercise;
    }
    excercisesFile.close();
    this->hide();
}




