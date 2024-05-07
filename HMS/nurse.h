#ifndef NURSE_H
#define NURSE_H

#include <QWidget>
#include <QDialog>
#include "login.h"
#include "admin.h"
#include <QFile>
#include <QTextStream>
#include <QString>
namespace Ui {
class nurse;
}

class nurse : public QDialog
{
    Q_OBJECT

public:
    explicit nurse(QWidget *parent = nullptr);
    ~nurse();
    QList<QString>* data_ptr;
    QList<QList<QString>>* usersRecords_ptr;
private slots:
    void on_pushButton_clicked();

    void on_getdoctorbutton_clicked();

private:
    Ui::nurse *ui;
    QFile file;
    void InitializeList();
};

#endif // NURSE_H
