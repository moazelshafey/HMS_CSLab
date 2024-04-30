#include "registration.h"
#include "ui_registration.h"
#include "login.h"
#include <QTimer>
#include <QFile>

Registration::Registration(QWidget *parent, QList<QString>* data)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->data = data;
}

Registration::~Registration()
{
    static_cast<logIn*>(parent())->show();
    delete ui;
}

void Registration::on_pushButton_2_clicked()
{
    delete this;
}


void Registration::on_pushButton_clicked()
{
    QString hisUsername = this->ui->textEdit->toPlainText();
    QString hisPassword = this->ui->textEdit_2->toPlainText();


    if (hisUsername.isEmpty() || hisPassword.isEmpty())
    {
        this->ui->pushButton->setText("Please provide a username and a password");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        this->ui->pushButton->setText("Register");
        return;
    }
    if (hisUsername.contains(" "))
    {
        this->ui->pushButton->setText("No spaces allowed in username");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        this->ui->pushButton->setText("Register");
        return;
    }

    int isTaken = false;
    for (int i = 0; i < data->count(); i++)
    {
        QString username;
        QList<QString> dataValue = *data;
        QTextStream input(&dataValue[i]);
        input >> username;
        if (hisUsername == username)
        {
            isTaken = true;
        }
    }
    if (isTaken)
    {
        this->ui->pushButton->setText("Username already taken");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        this->ui->pushButton->setText("Register");
        return;
    }
    QString usernameAndPassword = hisUsername + " " + hisPassword + " " + "patient";
    data->push_back(usernameAndPassword);
    qDebug() << data->count();

}

