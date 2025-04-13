#ifndef HUB_H
#define HUB_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QDir>

namespace Ui {
class Hub;
}

class Hub : public QDialog
{
    Q_OBJECT

public:
    explicit Hub(QWidget *parent = nullptr);
    ~Hub();
    QString cipher(QString password);

private slots:
    void on_login_acc_editingFinished();

    void on_haslo_acc_editingFinished();

    void on_age_acc_valueChanged(int arg1);

    void on_create_acc_btn_clicked();


private:
    Ui::Hub *ui;
};

#endif // HUB_H
