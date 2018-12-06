#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>
#include <QMessageBox>
#include <QtNetwork>
#include <unistd.h>

namespace Ui {
class Newuser;
}

class Newuser : public QDialog
{
    Q_OBJECT

public:
    explicit Newuser(QWidget *parent = nullptr);
    ~Newuser();

private slots:
    void on_loginBtn_clicked();

    void dealDatagram();

private:
    Ui::Newuser *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    bool flag;
    quint16 rcv1Port;
    quint16 sendPort;
};

#endif // NEWUSER_H
