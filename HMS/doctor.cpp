#include "doctor.h"
#include "ui_doctor.h"
#include<QTimer>
doctor::doctor(QWidget *parent, QList<QString> data)
    : QDialog(parent)
    , ui(new Ui::doctor)
{
    index=0;
    this->data= data;
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


void doctor::on_AddPatient_pushbutton_clicked()
{

    for(int i=0;i<data.count();i++)
    {
        QTextStream input(&data[i]);

        QString id, username, role;
        input >> username >> id >> role>> id;
        QString PatientName=ui->PatientName_lineedit->text();
        if(id==ui->PatientID_lineedit->text()&& username==ui->PatientName_lineedit->text()&&role=="patient")
        {
            ui->PatientList->addItem(QString::number(index + 1)+" " + PatientName );
            QStringList headerLabels;
           headerLabels << "Name" << "ID" << "Diagnosis" << "Treatment" << "Prescription";
            ui->PatientDetailsTable->setColumnCount(5);
            ui->PatientDetailsTable->insertRow(index);
            ui->PatientDetailsTable->setHorizontalHeaderLabels(headerLabels);
            ui->PatientDetailsTable->setItem(index,0,new QTableWidgetItem(ui->PatientName_lineedit->text()));
            ui->PatientDetailsTable->setItem(index,1,new QTableWidgetItem(ui->PatientID_lineedit->text()));
            ui->PatientDetailsTable->setItem(index,2,new QTableWidgetItem(ui->Diagnosis_lineedit->text()));
            ui->PatientDetailsTable->setItem(index,3,new QTableWidgetItem(ui->Treatment_lineedit->text()));
            ui->PatientDetailsTable->setItem(index,4,new QTableWidgetItem(ui->Prescription_lineedit->text()));
            index++;
            ui->PatientName_lineedit->clear();
            ui->PatientID_lineedit->clear();

            return;
        }


    }
    this->ui->AddPatient_pushbutton->setText("Invalid Details");
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, &QEventLoop::quit);
    loop.exec();
    this->ui->AddPatient_pushbutton->setText("Add Patient");
    return;
}

