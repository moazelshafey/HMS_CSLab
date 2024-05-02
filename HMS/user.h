#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QDialog>
#include "login.h"
namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();

private slots:
    void on_pushButton_clicked();

private:
    Ui::user *ui;
};

#endif // USER_H
