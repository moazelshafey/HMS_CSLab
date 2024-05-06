#include "nurse.h"
#include "ui_nurse.h"

nurse::nurse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::nurse)
{
    ui->setupUi(this);
    QPixmap b1(":/Images/nurse.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);
}

nurse::~nurse()
{
    delete ui;
}

void nurse::on_pushButton_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete this;

}

