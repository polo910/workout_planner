#ifndef BODY_H
#define BODY_H

#include <QMainWindow>
#include "workout.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

namespace Ui {
class Body;
}



class Body : public QMainWindow
{
    Q_OBJECT

public:
    explicit Body(QWidget *parent = nullptr, QString title = "", QString login = "", Note note = {"","","00:00","00:00"});
    ~Body();


private slots:
    void on_add_workout_btn_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);


    void on_actionWyloguj_triggered();

    void on_actionDodaj_niestandardowe_wiczenie_triggered();

    void on_actionHistoria_Trening_w_triggered();

private:
    Ui::Body *ui;
};

#endif // BODY_H

