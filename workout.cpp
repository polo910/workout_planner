#include "workout.h"
#include "ui_workout.h"
#include "mainwindow.h"
#include "body.h"
#include "QFile"
#include "QList"

Workout::Workout(QWidget *parent, QString login)
    : QDialog(parent)
    , ui(new Ui::Workout)
{
    QList<QString> excercises;
    QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\excercises.txt";
    QFile excercisesFile(filename);
    if(excercisesFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&excercisesFile);
        while(!in.atEnd()){
            excercises.append(in.readLine());
        }
    }

    ui->setupUi(this);
    for(int i = 0; i < excercises.size();i++){
        ui->comboBox->addItem(excercises.at(i));
    }
    ui->excercise_label->setText("Ćwiczenie 1");
    ui->workout_alert->setText("");

}
int num = 0;
Note note;
Workout::~Workout()
{
    delete ui;
}
QString workoutTitle;
void Workout::on_workout_title_editingFinished()
{
    workoutTitle = ui->workout_title->text();

}

QString workoutDate;
void Workout::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    workoutDate = ui->dateTimeEdit->text();

}

QString workoutStart;
void Workout::on_timeEdit_editingFinished()
{
    workoutStart = ui->timeEdit->text();
}

QString workoutEnd;
void Workout::on_timeEdit_2_editingFinished()
{
    workoutEnd = ui->timeEdit_2->text();
}

int reps = 0;
void Workout::on_reps_input_editingFinished()
{
    reps = ui->reps_input->text().toInt();
}

int weight = 0;
void Workout::on_weight_input_editingFinished()
{
    weight = ui->weight_input->text().toInt();
}



QString pickedName;
void Workout::on_comboBox_currentTextChanged(const QString &arg1)
{
    pickedName = ui->comboBox->currentText();
}

void Workout::on_pushButton_3_clicked()
{
    QString login = MainWindow::name;
    QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\" + login+pickedName + ".txt";
    QFile userFile(filename);
    if(userFile.open(QIODevice::Append| QIODevice::Text)){
        QTextStream out(&userFile);
        out << workoutDate << "\n"<<reps << "\n" <<weight<<"\n";
    }
    num++;
    int exNum = num+1;
    ui->reps_input->setText("");
    ui->weight_input->setText("");
    ui->excercise_label->setText("Ćwiczenie " + QString::number(exNum));

    ui->workout_alert->setText("Dodano ćwiczenie nr" + QString::number(num) + " do bazy");

}
void Workout::on_cancel_button_clicked()
{
    this->hide();
    Body *body = new Body();
    body->show();
}

void Workout::on_save_button_clicked()
{
    if((workoutTitle == "") || (workoutDate == "") || (workoutStart == "") || (workoutEnd == "")){
        ui->workout_alert->setText("Uzupełnij wszystkie pola!");
    }else if(num == 0){
        ui->workout_alert->setText("Dodaj co najmniej jedno ćwiczenie :)");
    }else{

        //workout data
        note.title = workoutTitle;
        note.date  = workoutDate;
        note.start = workoutStart;
        note.end   = workoutEnd;


        num = 0;
        this->hide();
        Body *body = new Body(nullptr,note.title,"",note);
        body->show();
    }
}






























