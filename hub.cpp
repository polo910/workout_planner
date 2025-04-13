#include "hub.h"
#include "ui_hub.h"
#include "mainwindow.h"

using namespace std;

Hub::Hub(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Hub)
{
    ui->setupUi(this);


}

Hub::~Hub()
{
    delete ui;
}
QString login;
QString passwordAcc;
int age;

int login_check(QString userLogin){

    QString fileName = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\logins.txt";
    QFile loginsDB(fileName);

    QList<QString> logins;
    if(loginsDB.open(QIODevice::ReadOnly | QIODevice::Text)){

        QTextStream in(&loginsDB);
        while(!in.atEnd()){
            logins.append(in.readLine());
        }
    }

    for(int i = 0; i < logins.size(); i++){
        if(userLogin == logins[i])
            return 1;
    }
    return 0;

}
void Hub::on_login_acc_editingFinished()
{
    login = ui->login_acc->text();
    if(login_check(login) == 1){
        ui->alert->setText("Uzytkownik o takim loginie już istnieje");
        ui->login_acc->setText("");
    }else{
        ui->alert->setText("");
    }


}

void Hub::on_haslo_acc_editingFinished()
{
    passwordAcc = ui->haslo_acc->text();
}

QString Hub::cipher(QString password){
    QString passwordCph;
    for(int i = 0; i < password.length();i++){
        int num = password.at(i).toLatin1()+13;
        passwordCph.append(QChar(num));
    }

    return passwordCph;
}


void Hub::on_age_acc_valueChanged(int arg1)
{
    age = ui->age_acc->value();
}

int password_check(){
    int hasNum = 0;

    for(int i = 0; i < passwordAcc.length(); i++){
        if(passwordAcc.at(i).isDigit())
            hasNum++;
    }

    if(passwordAcc.length()<6 || hasNum == 0){
        return 1;
    }else{
        return 0;
    }
}



void Hub::on_create_acc_btn_clicked()
{
    if(passwordAcc == "" || login == "" || age == 0){
        ui->alert->setText("Uzupełnij wszystkie pola");
    }else{
        if(password_check()==1)
            ui->alert->setText("Hasło musi składać się z co najmniej 6 znaków (w tym co najmniej 1 cyfra)");
        else if(age < 13)
            ui->alert->setText("Musisz mieć co najmniej 13 lat aby korzystać z aplikacji");
        else if(password_check()==0){

            //pusty alert
            ui->alert->setText("");

            //zapisywanie loginu do bazy loginów
            QString loginsSrc = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\logins.txt";
            QFile loginsFile(loginsSrc);
            if(loginsFile.open(QIODevice::Append | QIODevice::Text)){
                QTextStream out(&loginsFile);
                out <<login + "\n";
            }
            loginsFile.close();

            //tworzenie pliku uzytkownika z zaszyfrowanym hasłem, wiekiem, liczbą godzin i minut na siłowni
            QString filename = "C:\\Studia\\I Semestr\\Podstawy Informatyki\\Projekt\\build-workout_planner-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\\userData\\" + login + ".txt";
            QFile user(filename);
            if(user.open(QIODevice::WriteOnly | QIODevice::Text)){

                QTextStream out(&user);
                out << cipher(passwordAcc) + "\n";
                out << age <<"\n";
                out << 0 << "\n";
                out << 0;

            }
            user.close();

            //powrót do logowania
            this->hide();
            MainWindow *mw = new MainWindow();
            mw->show();
        }
    }



\
}

