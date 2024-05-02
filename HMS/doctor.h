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

public:
    explicit doctor(QWidget *parent = nullptr);
    ~doctor();

private slots:
    void on_pushButton_clicked();

private:
    Ui::doctor *ui;
};

#endif // DOCTOR_H
