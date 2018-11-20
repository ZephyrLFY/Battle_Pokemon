#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QWidget>
#include <QtNetwork>

class udpReceiver : public QObject
{
    Q_OBJECT

public:
    explicit udpReceiver(QObject *parent = nullptr);
    ~udpReceiver();
    QUdpSocket *sender;

public slots:
    int updating();
    void whatToDo(int flag);
    void sendMsg(QString msg);

private slots:
    void processPendingDatagram();

private:
    //QUdpSocket *sender;
    QUdpSocket *receiver;
    bool tOrF;
};

#endif // UDPRECEIVER_H
