#ifndef PREBTL_H
#define PREBTL_H

#include <QDialog>
#include <QtNetwork>
#include <QStandardItemModel>
#include <QMessageBox>

namespace Ui {
class preBtl;
}

class preBtl : public QDialog
{
    Q_OBJECT

public:
    explicit preBtl(QWidget *parent = nullptr);
    ~preBtl();
    void bindPort();

    void getMy();

    void getEnm();

    void myTable(QList<QString> &poke);

    void enmTable(QList<QString> &poke);

public slots:

    void processPendingDatagram();

    void getMyPoke(const QItemSelection&,const QItemSelection&);

    void getEnmPoke(const QItemSelection&,const QItemSelection&);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::preBtl *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    QStandardItemModel *myPokeModel;
    QStandardItemModel *enmPokeModel;
    qint32 rowNum1;
    qint32 rowNum2;
    quint16 rcv1Port;
    quint16 sendPort;
    qint32 which;
    bool myChosen = 0;
    bool enmChosen = 0;
    QList<QString> *enmChose;
};

#endif // PREBTL_H
