#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "body.h"
#include "hub.h"
#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QIODevice>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QString name;

private slots:

    void on_login_inpt_editingFinished();

    void on_pushButton_clicked();

    void on_haslo_inpt_editingFinished();

    void on_sign_in_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
