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
    QString executablePath = QCoreApplication::applicationDirPath();

    // Construct the path relative to the executable
    qDebug()<< executablePath ;
    loginInfoPath ="Data/loginData.txt";
    userRecordsPath ="Data/usersData.txt";

    ExtractData();
}

void logIn::ExtractData()
{
    QFile file(loginInfoPath);

    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "Failed to open file" << "\n";
        return;
    }

    QFile recordsFile(userRecordsPath);

    if (!recordsFile.open(QFile::ReadOnly))
    {
        qDebug() << "Failed to open file" << "\n";
        return;
    }


    QTextStream stream(&file);
    QTextStream recordsStream(&recordsFile);

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        data.push_back(line);

        QTextStream loginInfo(&line);
        QString role;
        loginInfo >> role >> role >> role;
        if (role == "nurse" || role == "admin") continue;

        if (role == "doctor")
        {
            QString userInfo = recordsStream.readLine();
            int recordsNumber;
            recordsStream >> recordsNumber;
            recordsStream.readLine();
            QList<QString> userInfoAndRecords;
            userInfoAndRecords.push_back(userInfo);
            userInfoAndRecords.push_back(QString::number(recordsNumber));
            for (int i = 0; i < recordsNumber; i++)
            {
                QString date = recordsStream.readLine();
                QString reservee = recordsStream.readLine();
                if (date != "") userInfoAndRecords.push_back(date);
                if (reservee != "") userInfoAndRecords.push_back(reservee);
            }
            usersRecords.push_back(userInfoAndRecords);
        }
        else
        {
            QString userInfo = recordsStream.readLine();
            int recordsNumber;
            recordsStream >> recordsNumber;
            recordsStream.readLine();
            QList<QString> userInfoAndRecords;
            userInfoAndRecords.push_back(userInfo);
            userInfoAndRecords.push_back(QString::number(recordsNumber));
            for (int i = 0; i < recordsNumber; i++)
            {
                QString diagnosis = recordsStream.readLine();
                userInfoAndRecords.push_back(diagnosis);
            }
            usersRecords.push_back(userInfoAndRecords);
        }
    }

    file.close();
    recordsFile.close();
}

logIn::~logIn()
{
    QFile file(loginInfoPath);

    file.open(QFile::WriteOnly);

    QTextStream stream(&file);
    for (int i = 0; i < data.count(); i++)
    {
        stream << data[i] << "\n";
    }
    file.close();

    QFile recordsFile(userRecordsPath);

    if (!recordsFile.open(QFile::WriteOnly))
    {
        qDebug() << "Failed to open file" << "\n";
        return;
    }

    QTextStream recordsStream(&recordsFile);

    for (int i = 0; i < usersRecords.count(); i++)
    {
        for (int j = 0; j < usersRecords[i].count(); j++)
        {
            recordsStream << usersRecords[i][j] << "\n";
        }
    }

    recordsFile.close();
    delete ui;
}

void logIn::on_LoginButton_clicked()
{
    this->hide();
    loginInfo* login = new loginInfo(this, &data, &usersRecords);
    login->show();
}

void logIn::on_SignUpButton_clicked()
{
    this->hide();
    Registration* registration = new Registration(this, &data, &usersRecords);
    registration->show();
}
