#ifndef LOGIN_H
#define LOGIN_H


#include <QString>
#include <QList>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class logIn;
}
QT_END_NAMESPACE

class logIn : public QMainWindow
{
    Q_OBJECT

    QList<QString> data;

public:

    logIn(QWidget *parent = nullptr);
    ~logIn();
private slots:

    void on_LoginButton_clicked();

    void on_SignUpButton_clicked();

private:
    Ui::logIn *ui;
};
#endif // LOGIN_H
