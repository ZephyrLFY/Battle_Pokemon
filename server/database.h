#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QList>
#include <QDebug>

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log();
    virtual ~Log();
    void initDatabase();
    void setOnlineOff();
    QString searchPwd(QString name);
    bool addNewusr(QString name,QString pwd);
    void addPokemon(QString name);
    bool aliveOrNot(QString name);
    void linkStart(QString name);
    QList<QString>& getUsr();
    QList<QString>& getPoke();
    QList<QString>& getUsrPoke(QString name);
public slots:
    void createConnection();
    bool freeConnection(QString name);
private:
    QSqlDatabase db;
    QSqlQuery *usrQuery;
    QSqlQuery *pokeQuery;
};


#endif // DATABASE_H
