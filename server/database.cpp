#include "database.h"

Log::Log()
{
    createConnection();
    if (!db.open())
        QMessageBox::critical(nullptr, qApp->tr("无法打开数据库"),qApp->tr("未能与数据库建立连接。"), QMessageBox::Cancel);
    query = new QSqlQuery(db);
    //initDatabase();
}

Log::~Log()
{
    delete query;
}

void Log::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/zephyr/mywork/dataBase.db");
}

bool Log::freeConnection(QString name)
{
    query->prepare("update player set alive=0 where ID = ?");
    query->addBindValue(name);
    query->exec();
    return true;
}

void Log::initDatabase()
{
    query->exec("create table player (ID varchar primary key,password varchar,"
                "alive bool,ratio float,number int,"
                "pokemon1 varchar(20),level1 int,"
                "pokemon2 varchar(20),level2 int,"
                "pokemon3 varchar(20),level3 int,"
                "pokemon4 varchar(20),level4 int,"
                "pokemon5 varchar(20),level5 int,"
                "pokemon6 varchar(20),level6 int,"
                "pokemon7 varchar(20),level7 int,"
                "end int)");
    query->exec("insert into player (ID,password,alive,ratio,number,pokemon1,level1,pokemon2,level2)"
                "values('test','123',0,0.5,2,'Pikachu',15,'Charmander',13)");
    query->exec("insert into player (ID,password,alive,ratio,number,pokemon1,level1,pokemon2,level2)"
                "values('Zephyr','lifuyang',0,1,2,'Squirtle',15,'Muk',13)");
    query->exec("insert into player (ID,password,alive,ratio,number,pokemon1,level1,pokemon2,level2)"
                "values('god','777',0,0.3,2,'Licktung',2,'Krabby',7)");
}

QString Log::searchPwd(QString name)
{
    QString pwd;
    query->exec(QString("select password from player where (ID = '%1')").arg(name));
    if(query->next())
        pwd = query->value(0).toString();
    else
        pwd = "NULL";
    return pwd;
}

bool Log::aliveOrNot(QString name)
{
    query->exec(QString("select alive from player where (ID = '%1')").arg(name));
    query->next();
    bool which = query->value(0).toBool();
    return which;
}

void Log::linkStart(QString name)
{
    query->prepare("update player set alive = ? where ID = ?");
    query->addBindValue(1);
    query->addBindValue(name);
    query->exec();
}

bool Log::addNewusr(QString name,QString pwd)
{
    query->exec(QString("select password from player where (ID = '%1')").arg(name));
    if(query->next())
        return false;
    else
    {
        query->last();
        query->prepare("insert into player(ID,password,alive,ratio,number)"
                         "values (?,?,0,0,0)");
        query->addBindValue(name);
        query->addBindValue(pwd);
        query->exec();
        return true;
    }
}

void Log::addPokemon(QString name)
{
    query->prepare("update player set pokemon1=?,level1=? where ID = ?");
    query->addBindValue("Charmander");
    query->addBindValue(1);
    query->addBindValue(name);
    query->exec();
}

QList<QString>& Log::getUsr()
{
    query->exec("select * from player");
    QList<QString> *usr = new QList<QString>;
    qint32 i = 0;
    qint32 count = 0;
    for(query->first();query->seek(count);query->next())
    {
        while(query->value(i).toString() != "")
        {
            if(i == 1)
            {
                i++;
                continue;
            }
            usr->append(query->value(i).toString());
            i++;
        }
        i = 0;
        count++;
        usr->append("line");
    }
    usr->append("over");
    return *usr;
}

//QList<QString>* Log::getPoke()
//{

//}

