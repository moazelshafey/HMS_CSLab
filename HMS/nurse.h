#ifndef NURSE_H
#define NURSE_H

#include <QWidget>
#include <QDialog>
#include "login.h"
namespace Ui {
class nurse;
}

class nurse : public QDialog
{
    Q_OBJECT

public:
    explicit nurse(QWidget *parent = nullptr);
    ~nurse();

private slots:
    void on_pushButton_clicked();

private:
    Ui::nurse *ui;
};

#endif // NURSE_H
