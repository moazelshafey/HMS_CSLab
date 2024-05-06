#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::user)
{
    ui->setupUi(this);

    QPixmap b1(":/Images/user.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);

}

user::~user()
{

    delete ui;
}

void user::on_pushButton_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete this;
}

