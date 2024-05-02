#include "login.h"
#include "ui_login.h"
#include "logininfo.h"
#include "registration.h"
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "admin.h"


logIn::logIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::logIn)
{
    ui->setupUi(this);
    QPixmap b(":/Images/Login2.png");
    b = b.scaled(ui->BackgroundLabel->size());
    ui->BackgroundLabel->setPixmap(b);

    QString filePath = "../HMS/Data/data.txt";
    qDebug() << filePath;
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "Failed to open file" << "\n";
        return;
    }

    QTextStream stream(&file);

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        data.push_back(line);
    }

    file.close();
}

logIn::~logIn()
{
    QString filePath = "./Data/data.txt";
    QFile file(filePath);

    file.open(QFile::WriteOnly);

    QTextStream stream(&file);
    for (int i = 0; i < data.count(); i++)
    {
        qDebug() << "doing it" << "\n";
        stream << data[i] << "\n";
    }
    file.close();

    qDebug() << "closing";
    delete ui;
}

void logIn::on_LoginButton_clicked()
{
    this->hide();
    loginInfo* login = new loginInfo(this ,data);
    login->show();

}


void logIn::on_SignUpButton_clicked()
{
    this->hide();
    Registration* registration = new Registration(this, &data);
    registration->show();
}
