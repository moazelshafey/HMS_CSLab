#ifndef LOGININFO_H
#define LOGININFO_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QList>

namespace Ui {
class loginInfo;
}

class loginInfo : public QDialog
{
    Q_OBJECT

    bool processing = false;

    QList<QString> data;

public:
    explicit loginInfo(QWidget *parent, QList<QString> data);
    ~loginInfo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::loginInfo *ui;
};

#endif // LOGININFO_H
