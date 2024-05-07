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

    InitializeList();
}

nurse::~nurse()
{
    delete ui;
}

void nurse::InitializeList()
{
    QList<QString> data = *data_ptr;
    for (int i = 0; i < data.count(); i++)
    {
        QTextStream input(&data[i]);
        QString name, id, role;
        input >> name >> role >> role >> id;
        qDebug() << role;
        if (role == "admin") continue;
        int rowIndex = ui->usersList->rowCount();
        ui->patientslabel->insertRow(rowIndex);
        ui->patientslabel->setItem(rowIndex,0,new QTableWidgetItem(name));
        ui->patientslabel->setItem(rowIndex,1,new QTableWidgetItem(id));
        ui->patientslabel->setItem(rowIndex,2,new QTableWidgetItem(role));
    }

    ui->PatientDetailsTable->setColumnCount(3);
    ui->PatientDetailsTable->setColumnWidth(0, 150);
    ui->PatientDetailsTable->setColumnWidth(1, 50);
    ui->PatientDetailsTable->setColumnWidth(2, 300);
    QStringList headerLabels;
    headerLabels << "Name" << "ID" << "Diagnosis and Treatment";
    ui->PatientDetailsTable->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->PatientDetailsTable->setHorizontalHeaderLabels(headerLabels);

    for (int i = 0; i < data.count(); i++)
    {
        QTextStream input(&data[i]);
        QString name, role, id;

        input >> name >> role >> role >> id;

        if (role != "patient") continue;

        AddPatientRecord(id);
    }
}


void nurse::on_pushButton_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete this;

}


void nurse::on_getdoctorbutton_clicked()
{
    QFile file("C:\\Users\\kouss\\Desktop\\Hospital Management System\\HMS_CSLab\\HMS\\Data\\nursesData.txt");
    QString nursename = this->ui->nursename->text().trimmed(); // Trimmed to remove any leading/trailing spaces

    // Convert nurse's name to QByteArray
    QByteArray ba = nursename.toUtf8(); // Convert QString to QByteArray

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine().trimmed(); // Trimmed to remove any leading/trailing spaces


            if (line.contains(ba)) {
                ui->doctoroutput->setText(QString("The Nurse and the Assigned Doctor : ")+ QString(line));
                qDebug() << "read output - " << line;
                break; // If you only want to display the first match, you can break here
            }
        }
        file.close();
    } else {
        qDebug() << "Failed to open file";
    }



}

