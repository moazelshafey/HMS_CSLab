#include "user.h"
#include "ui_user.h"
#include <QStandardItem>

user::user(QWidget *parent, QList<QString> data, QList<QList<QString>>* usersRecordData, QString ownID, QString ownName)
    : QDialog(parent)
    , ui(new Ui::user)
{
    ui->setupUi(this);

    AppointmentReserved=false;
    QPixmap b1(":/Images/user.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);

    this->usersRecord_ptr = usersRecordData;
    this->data = data;
    this->ownName = ownName;

    int patientRecordIndex = Find(ownName);
    ui->recordlabel->setText(usersRecordData->at(patientRecordIndex).value(2));

    ui->appointments->setColumnCount(3);
    ui->appointments->setColumnWidth(0, 200);
    ui->appointments->setColumnWidth(1, 200);
    ui->appointments->setColumnWidth(2, 200);
    QStringList headerLabels;
    headerLabels << "Doctor"<< "Date" << "Available";
    ui->appointments->setEditTriggers(QTableWidget::DoubleClicked);
    ui->appointments->setHorizontalHeaderLabels(headerLabels);


    for (int i = 0; i < data.count(); i++)
    {
        QTextStream input(&data[i]);
        QString name, role, id;

        input >> name >> role >> role >> id;

        if (role != "doctor") continue;

        QList<QString> doctorRecord = Retrieve(id);

        int recordNumber = doctorRecord[1].toInt();

        for (int j = 0; j < recordNumber; j++)
        {
            int recordIndex = j * 2 + 2;
            QString reservee = doctorRecord.at(recordIndex + 1);
            QString date = doctorRecord.at(recordIndex);

            int rowIndex = ui->appointments->rowCount();
            ui->appointments->insertRow(rowIndex);
            ui->appointments->setItem(rowIndex,0,new QTableWidgetItem(name));
            ui->appointments->setItem(rowIndex,1,new QTableWidgetItem(date));
            if (reservee == "No Reservee") ui->appointments->setItem(rowIndex,2,new QTableWidgetItem("Available"));
            else ui->appointments->setItem(rowIndex,2,new QTableWidgetItem("Unavailable"));
        }
    }
}

QList<QString> user::Retrieve(QString toBeFoundID)
{
    QList<QList<QString>> usersRecords = *usersRecord_ptr;
    for (int i = 0; i < usersRecords.count(); i++)
    {
        QString userInfo = usersRecords[i][0];
        QTextStream input(&userInfo);
        QString id;
        input >> id >> id;

        if (id == toBeFoundID)
        {
            return (usersRecords[i]);
        }
    }
}

user::~user()
{
    delete ui;
}



void user::on_appointments_cellClicked(int row, int column)
{
    qDebug() << "clicked";
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->appointments->model());
    QModelIndex index = model->index(row,0);
    QVariant name = model->data(index, Qt::DisplayRole);
    index = model->index(row,1);
    QVariant appointmentDate = model->data(index, Qt::DisplayRole);

    int dataIndex = Find(name.toString());
    int recordNumber = (*usersRecord_ptr)[dataIndex].value(1).toInt();
    for (int j = 0; j < recordNumber; j++)
    {
        int recordIndex = j * 2 + 2;
        QString date = (*usersRecord_ptr)[dataIndex][recordIndex];
        if (appointmentDate == date)

        {
            if((*usersRecord_ptr)[dataIndex][recordIndex + 1]=="No Reservee")

            {
                (*usersRecord_ptr)[dataIndex][recordIndex + 1] = ownName;
                AppointmentReserved=true;
            }
            else
            {
                (*usersRecord_ptr)[dataIndex][recordIndex + 1]="No Reservee";
                AppointmentReserved= false;
            }

            break;
        }
    }

    index = model->index(row, 2);
    if(AppointmentReserved)
    {model->setData(index, "Unavailable");}
    else
    {
        model->setData(index, "Available");
    }
}

int user::Find(QString toBeFoundName)
{
    QList<QList<QString>> usersRecords = *usersRecord_ptr;
    for (int i = 0; i < usersRecords.count(); i++)
    {
        QString userInfo = usersRecords[i][0];
        QTextStream input(&userInfo);
        QString name;
        input >> name;
        if (name == toBeFoundName)
        {
            return i;
        }
    }
}

void user::on_Exit_Button_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete this;
}

