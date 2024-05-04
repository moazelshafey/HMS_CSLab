#include "logininfo.h"
#include "ui_logininfo.h"
#include "login.h"
#include "registration.h"
#include "admin.h"
#include "nurse.h"
#include "doctor.h"
#include "user.h"

#include <QTimer>

loginInfo::loginInfo(QWidget *parent, QList<QString> data)
    : QDialog(parent)
    , ui(new Ui::loginInfo)
{
    ui->setupUi(this);
    this->data = data;

    ui->background->lower(); //Decreases zIndex of this UI element

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}


loginInfo::~loginInfo()
{
    static_cast<logIn*>(parent())->show();
    delete ui;
}

void loginInfo::on_pushButton_clicked()
{
    QString hisUsername = this->ui->textEdit->toPlainText();
    QString hisPassword = this->ui->textEdit_2->toPlainText();

    hisUsername = hisUsername.trimmed(); // Trims any spaces at the end
    hisPassword = hisPassword.trimmed(); // Trims any spaces at the end
    index = -1;
    for (int i = 0; i < data.count(); i++)
    {
        QString username, password;
        QTextStream input(&data[i]);
        input >> username >> password;
        if (hisUsername == username && hisPassword == password)
        {
            index = i;
            qDebug() << "found";
        }
    }

    if (index == -1)
    {
        this->ui->pushButton->setText("Invalid Details");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        this->ui->pushButton->setText("Login");
        return;
    }

    QTextStream input(&data[index]);

    QString role;
    input >> role >> role >> role; // First 2 to ignore name and password;


    //The username variable is hisUsername;

    //Deals with role accordingly
    if (role == "admin")
    {
        this->hide();
        admin* adminWindow = new admin(this);
        adminWindow->show();
    }

    if (role == "patient")
    {
        this->hide();
        user* userWindow = new user(this);
        userWindow->show();
    }

    if (role == "doctor")
    {
        this->hide();
        doctor* doctorWindow = new doctor(this, data);
        doctorWindow->show();
    }

    if (role == "nurse")
    {
        this->hide();
        nurse* nurseWindow = new nurse(this);
        nurseWindow->show();
    }
}


void loginInfo::on_pushButton_2_clicked()
{
    delete this;
}

