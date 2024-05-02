#include "registration.h"
#include "ui_registration.h"
#include "login.h"
#include <QTimer>
#include <QFile>
//#include "admin.h"

Registration::Registration(QWidget *parent, QList<QString>* data)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->data = data;

    ui->background->lower(); //Decreases zIndex of this UI element

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    int roleIndex = this->ui->comboBox->currentIndex();

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

    QString role;
    switch(roleIndex)
    {
    case 0: role = "patient";
    case 1: role = "nurse";
    case 2: role = "doctor";
    }

    QString usernameAndPassword = hisUsername + " " + hisPassword + " " + role;
    data->push_back(usernameAndPassword);
}

