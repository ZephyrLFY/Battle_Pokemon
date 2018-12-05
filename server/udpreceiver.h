#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDebug>
#include "database.h"

namespace Ui {
class udpReceiver;
}

class udpReceiver : public QMainWindow
{
    Q_OBJECT

public:
    explicit udpReceiver(QWidget *parent = nullptr);
    ~udpReceiver();

private slots:
    void on_sendBtn_clicked();

    void dealDatagram();

    void usrs(int inOrNew,QString name,QString pwd,QHostAddress address);

    qint32 userIn(QString name,QString pwd);

    bool newUsr(QString name,QString pwd);

    void txShow(QString text);

    void linkOver(QString name,QHostAddress address);

    void userInfo(QString name,QHostAddress address);

    void pokeInfo(QHostAddress address);

private:
    Ui::udpReceiver *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    Log *loger;
};

#endif // UDPRECEIVER_H
