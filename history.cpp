#include "history.h"
#include "ui_history.h"
#include <QFile>
#include "mainwindow.h"

history::history(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::history)
{
    ui->setupUi(this);
    ui->label->setText("");

    QList<QString> historyList;
    QString login = MainWindow::name;
    QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\"+login+"history.txt";
    QFile historyFile(filename);
    if(historyFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&historyFile);
        while(!in.atEnd()){
            historyList.append(in.readLine());
        }
    }
    QString text;
    for(int i = 0 ; i <historyList.length();i++){
        if(i%2==0)
            text.append("<p><b>"+historyList.at(i)+"</b></p></br>");
        else
            text.append(historyList.at(i)+"</br>");
    }
    ui->label->setText(text);

}

history::~history()
{
    delete ui;
}
