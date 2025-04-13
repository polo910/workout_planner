#include "body.h"
#include "ui_body.h"
#include "workout.h"
#include "dialog.h"
#include "mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include "history.h"


Body::Body(QWidget *parent, QString title, QString login, Note note)
    : QMainWindow(parent)
    , ui(new Ui::Body)
{
    ui->setupUi(this);
    ui->body_alert->setText(note.picked_excercises[0]);
    ui->user_welcome->setText("Witaj, " + MainWindow::name);

    if(note.date != "" && note.title != ""){
    QString historyfilename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\"+MainWindow::name+"history.txt";
    QFile historyFile(historyfilename);
    if(historyFile.open(QIODevice::Append | QIODevice::Text)){
        QTextStream out(&historyFile);
        out << note.date << "\n" << note.title << "\n";
    }
    historyFile.close();
    }

    QList<QString> excercises;
    QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\excercises.txt";
    QFile excercisesFile(filename);
    if(excercisesFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&excercisesFile);
        while(!in.atEnd()){
            excercises.append(in.readLine());
        }
    }
    for(int i = 0; i < excercises.size();i++){
        ui->comboBox->addItem(excercises.at(i));
    }

    QString start = note.start;
    QString end = note.end;

    QString startH1 = start.at(0);
    QString startH2 = start.at(1);
    QString startH = startH1 + startH2;

    QString startM1 = start.at(3);
    QString startM2 = start.at(4);
    QString startM = startM1 + startM2;

    QString endH1 = end.at(0);
    QString endH2 = end.at(1);
    QString endH = endH1 + endH2;

    QString endM1 = end.at(3);
    QString endM2 = end.at(4);
    QString endM = endM1 + endM2;

    int Int_startH = startH.toInt();
    int Int_startM = startM.toInt();

    int Int_endH = endH.toInt();
    int Int_endM = endM.toInt();

    int resultH = Int_endH - Int_startH;
    int resultM = Int_endM - Int_startM;
    if(resultM<0){
        resultM+=60;
        resultH--;
    }
    QString tab[4];
    QString userName = MainWindow::name;
    QString filename2 = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\" + userName+ ".txt";
    QFile userFile(filename2);
    if(userFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&userFile);
        for(int i = 0; i < 4; i++){
            tab[i] = in.readLine();
        }
    }
    userFile.close();

    int totalHours = tab[2].toInt();
    int totalMinutes = tab[3].toInt();
    totalHours += resultH;
    totalMinutes += resultM;
    if(totalMinutes>=60){
        totalMinutes-=60;
        totalHours++;
    }
    tab[2] = QString::number(totalHours);
    tab[3] = QString::number(totalMinutes);


    ui->timer_label->setText("Czas na siłowni:\n\n  " + QString::number(totalHours)+"h:"+QString::number(totalMinutes)+"m");

    QFile userFile2(filename2);
    if(userFile2.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&userFile2);
        for(int i = 0; i < 4; i++){
            if(i!=3)
                out<<tab[i]<<"\n";
            else
                out<<tab[i];
        }
    }
    userFile2.close();

}

Body::~Body()
{
    delete ui;
}



void Body::on_add_workout_btn_clicked()
{

    this->hide();
    Workout *workout = new Workout();
    workout->show();

}

int counter = 0;
void Body::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString login = MainWindow::name;
    QList<QString> data;

    QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\" + login+arg1+ ".txt";
    QFile userFile(filename);
    if(userFile.open(QIODevice::ReadOnly| QIODevice::Text)){
        QTextStream in(&userFile);
        while(!in.atEnd()){
            data.append(in.readLine());
        }
    }

    if(!data.isEmpty()){
        //ui->body_alert->setText(data.at(5));

        QLineSeries *series = new QLineSeries();
        int indeS = 0;
        for(int i = 2; i < data.length(); i+=3){
            series->append(indeS, data.at(i).toInt());
            indeS++;
        }

        QLineSeries *series2 = new QLineSeries();
        int indeS2 = 0;
        for(int i = 1; i < data.length(); i+=3){
            series2->append(indeS2, data.at(i).toInt());
            indeS2++;
        }

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();

        QChart *chart2 = new QChart();
        chart2->legend()->hide();
        chart2->addSeries(series2);
        chart2->createDefaultAxes();

        QPen pen(QRgb(0x0bb3a7));
        pen.setWidth(4);
        series->setPen(pen);

        QPen pen2(QRgb(0x8a65f0));
        pen2.setWidth(4);
        series2->setPen(pen2);

        chart->setAnimationOptions(QChart::AllAnimations);
        chart2->setAnimationOptions(QChart::AllAnimations);

        QCategoryAxis *axisX = new QCategoryAxis();
        //axisX->append("",0);
        int indeX = 0;
        for(int i = 0; i < data.length(); i+=3){
            axisX->append(data.at(i),indeX);
            indeX++;
        }

        QCategoryAxis *axisX2 = new QCategoryAxis();
        //axisX2->append("",0);
        int indeX2 = 0;
        for(int i = 0; i < data.length(); i+=3){
            axisX2->append(data.at(i),indeX2);
            indeX2++;
        }

        chart->setAxisX(axisX, series);
        chart2->setAxisX(axisX2, series2);

        //chart->show();


        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QChartView *chartView2 = new QChartView(chart2);
        chartView2->setRenderHint(QPainter::Antialiasing);
       // if(counter && ui->verticalLayout->isEmpty()==false && ui->wykres2->isEmpty()==false){
        ui->verticalLayout->takeAt(0);
        ui->wykres2->takeAt(0);

        //}
        ui->verticalLayout->addWidget(chartView);
        ui->wykres2->addWidget(chartView2);
        counter++;
    }
    else{
        QLineSeries *series = new QLineSeries();
        series->append(0, 0);
        series->append(1, 0);

        QLineSeries *series2 = new QLineSeries();
        series2->append(0, 0);
        series2->append(1, 0);

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();

        QChart *chart2 = new QChart();
        chart2->legend()->hide();
        chart2->addSeries(series2);
        chart2->createDefaultAxes();

        QPen pen(QRgb(0x0bb3a7));
        pen.setWidth(4);
        series->setPen(pen);

        QPen pen2(QRgb(0x8a65f0));
        pen2.setWidth(4);
        series2->setPen(pen2);

        chart->setAnimationOptions(QChart::AllAnimations);
        chart2->setAnimationOptions(QChart::AllAnimations);

        QCategoryAxis *axisX = new QCategoryAxis();
        axisX->append("",0);
        axisX->append("",1);
        QCategoryAxis *axisX2 = new QCategoryAxis();
        axisX2->append("",0);
        axisX2->append("",1);

        chart->setAxisX(axisX, series);
        chart->setAxisX(axisX2, series2);


        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QChartView *chartView2 = new QChartView(chart2);
        chartView2->setRenderHint(QPainter::Antialiasing);

        ui->verticalLayout->takeAt(0);
        ui->verticalLayout->addWidget(chartView);

        ui->wykres2->takeAt(0);
        ui->wykres2->addWidget(chartView2);

    }
}


void Body::on_actionWyloguj_triggered()
{
    this->hide();
    MainWindow *mw = new MainWindow();
    mw->show();
}


void Body::on_actionDodaj_niestandardowe_wiczenie_triggered()
{
    Dialog *dialog = new Dialog();
    dialog->show();
}


void Body::on_actionHistoria_Trening_w_triggered()
{
    history *his = new history();
    his->show();
}

