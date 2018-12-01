#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>

class Log : public QObject
{
    Q_OBJECT
public:
    Log();
    virtual ~Log();
public slots:
    void createConnection();
    bool freeConnection(QString name);
    void initDatabase();
    QString searchPwd(QString name);
    bool addNewusr(QString name,QString pwd);
    void addPokemon(QString name);
    bool aliveOrNot(QString name);
    void linkStart(QString name);
private:
    QSqlDatabase db;
    QSqlQuery *query;
};


#endif // DATABASE_H
