#include "admin.h"
#include "ui_admin.h"


admin::admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);

    QPixmap b1(":/Images/admin.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);
}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_clicked()
{
    this->hide();
    logIn* loginWindow = new logIn(this);
    loginWindow->show();
}

