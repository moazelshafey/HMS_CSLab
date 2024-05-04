#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>
#include <QDialog>
#include "login.h"

namespace Ui {
class doctor;
}

class doctor : public QDialog
{
    Q_OBJECT

    QList<QString> data;
public:
    explicit doctor(QWidget *parent = nullptr, QList<QString> data= QList<QString>());
    ~doctor();

private slots:
    void on_pushButton_clicked();

    void on_AddPatient_pushbutton_clicked();

private:
    Ui::doctor *ui;
    int index;

};

#endif // DOCTOR_H
