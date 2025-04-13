#ifndef WORKOUT_H
#define WORKOUT_H

#include <QDialog>

namespace Ui {
class Workout;
}

class Workout : public QDialog
{
    Q_OBJECT

public:
    explicit Workout(QWidget *parent = nullptr, QString login = "");
    ~Workout();
private slots:
    void on_save_button_clicked();

    void on_workout_title_editingFinished();

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_timeEdit_editingFinished();

    void on_reps_input_editingFinished();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_timeEdit_2_editingFinished();

    void on_weight_input_editingFinished();

    void on_pushButton_3_clicked();

    void on_cancel_button_clicked();

private:
    Ui::Workout *ui;
};

class Note
{
public:
    QString title;
    QString date;
    QString start;
    QString end;
    QString picked_excercises[30];
};

#endif // WORKOUT_H
