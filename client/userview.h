#ifndef USERVIEW_H
#define USERVIEW_H

#include <QDialog>
#include <QtNetwork>
#include <QStandardItemModel>

namespace Ui {
class userView;
}

class userView : public QDialog
{
    Q_OBJECT

public:
    explicit userView(QWidget *parent = nullptr);
    ~userView();

    void getUsr();

    void updateTable(QList<QString> &usrInfo);

public slots:

    void processPendingDatagram();

private:
    Ui::userView *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
};

#endif // USERVIEW_H
