#include "doctor.h"
#include "ui_doctor.h"

doctor::doctor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::doctor)
{
    ui->setupUi(this);
    QPixmap b1(":/Images/doctor.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);
}

doctor::~doctor()
{
    delete ui;
}

void doctor::on_pushButton_clicked()
{
    this->hide();
    logIn* loginWindow = new logIn(this);
    loginWindow->show();
}

