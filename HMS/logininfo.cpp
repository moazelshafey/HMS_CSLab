#include "logininfo.h"
#include "ui_logininfo.h"
#include "login.h"
#include <QTimer>

loginInfo::loginInfo(QWidget *parent, QList<QString> data)
    : QDialog(parent)
    , ui(new Ui::loginInfo)
{
    ui->setupUi(this);
    this->data = data;
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

    int index = -1;
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
    }
}


void loginInfo::on_pushButton_2_clicked()
{
    delete this;
}

