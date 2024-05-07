#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QDialog>
#include "login.h"
#include <QFile>
#include <QTextStream>
#include <QDateTimeEdit>
namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent, QList<QString> data, QList<QList<QString>>* usersRecordData, QString ownID, QString ownName);
    ~user();


private slots:
    void on_pushButton_clicked();

    void on_appointments_cellClicked(int row, int column);

private:

    int Find(QString id);
    QList<QString> Retrieve(QString id);

    QString ownName;

    QList<QList<QString>>* usersRecord_ptr;
    QList<QString> data;
    QString ownID;
    Ui::user *ui;
};

#endif // USER_H
