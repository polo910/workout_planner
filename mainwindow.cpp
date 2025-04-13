#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "hub.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::name;
QString password;

int loging_login_check(QString userLogin){
    QString fileName = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\logins.txt";
    QFile loginsDB(fileName);
    QList<QString> logins;
    if(loginsDB.open(QIODevice::ReadOnly | QIODevice::Text)){

        QTextStream in(&loginsDB);
        while(!in.atEnd()){
            logins.append(in.readLine());
        }
    }
    loginsDB.close();

    for(int i = 0; i < logins.size(); i++){
        if(userLogin == logins[i])
            return 0;
    }
    return 1;

}

int loging_password_check(QString login, QString password){
    Hub h;
    QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\" + login + ".txt";
    QFile userFile = (filename);
    if(userFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&userFile);
        if(in.readLine() == h.cipher(password)){
            userFile.close();
            return 0;
        }else{
            userFile.close();
            return 1;
        }
    }
}

void MainWindow::on_login_inpt_editingFinished()
{
    name = ui->login_inpt->text();
}
void MainWindow::on_haslo_inpt_editingFinished()
{
    password = ui->haslo_inpt->text();
}


void MainWindow::on_pushButton_clicked()
{

    if(name == "admin" && password == "admin"){
        this->hide();
        Body *body = new Body();
        body->show();
    }else{
        if(loging_login_check(name) == 1){
            ui->login_alert->setText("Taki użytkownik nie istnieje.\nSprawdź poprawność lub załóż konto");
        }else{
            if(loging_password_check(name, password) == 1){
                ui->login_alert->setText("");
                ui->password_alert->setText("Niepoprawne hasło");
            }else{
                ui->login_alert->setText("");
                ui->password_alert->setText("");                
                this->hide();
                Body *body = new Body(nullptr,"",name);
                body->show();
            }
        }
    }
}

void MainWindow::on_sign_in_clicked()
{
    this->hide();
    Hub *hub = new Hub();
    hub->show();


}


