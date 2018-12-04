#include "database.h"

Log::Log()
{
    createConnection();
    if (!db.open())
        QMessageBox::critical(nullptr, qApp->tr("无法打开数据库"),qApp->tr("未能与数据库建立连接。"), QMessageBox::Cancel);
    usrQuery = new QSqlQuery(db);
    pokeQuery = new QSqlQuery(db);
    initDatabase();
}

Log::~Log()
{
    delete usrQuery;
    delete pokeQuery;
}

void Log::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/zephyr/mywork/dataBase.db");
}

bool Log::freeConnection(QString name)
{
    usrQuery->prepare("update player set alive=0 where ID = ?");
    usrQuery->addBindValue(name);
    usrQuery->exec();
    return true;
}

void Log::initDatabase()
{
    usrQuery->exec("create table player (ID varchar primary key,password varchar,"
                "alive bool,ratio float,number int,"
                "pokemon1 varchar(20),level1 int,"
                "pokemon2 varchar(20),level2 int,"
                "pokemon3 varchar(20),level3 int,"
                "pokemon4 varchar(20),level4 int,"
                "pokemon5 varchar(20),level5 int,"
                "pokemon6 varchar(20),level6 int,"
                "pokemon7 varchar(20),level7 int,"
                "end int)");
    usrQuery->exec("insert into player (ID,password,alive,ratio,number,pokemon1,level1,pokemon2,level2)"
                "values('test','123',0,0.5,2,'Pikachu',15,'Charmander',13)");
    usrQuery->exec("insert into player (ID,password,alive,ratio,number,pokemon1,level1,pokemon2,level2)"
                "values('Zephyr','lifuyang',0,1,2,'Squirtle',15,'Muk',13)");
    usrQuery->exec("insert into player (ID,password,alive,ratio,number,pokemon1,level1,pokemon2,level2)"
                "values('god','777',0,0.3,2,'Licktung',2,'Krabby',7)");
    pokeQuery->exec("create table pokemon (ID varchar primary key,name varchar(20),"
                    "level qint32,exp qint32)");
}

QString Log::searchPwd(QString name)
{
    QString pwd;
    usrQuery->exec(QString("select password from player where (ID = '%1')").arg(name));
    if(usrQuery->next())
        pwd = usrQuery->value(0).toString();
    else
        pwd = "NULL";
    return pwd;
}

bool Log::aliveOrNot(QString name)
{
    usrQuery->exec(QString("select alive from player where (ID = '%1')").arg(name));
    usrQuery->next();
    bool which = usrQuery->value(0).toBool();
    return which;
}

void Log::linkStart(QString name)
{
    usrQuery->prepare("update player set alive = ? where ID = ?");
    usrQuery->addBindValue(1);
    usrQuery->addBindValue(name);
    usrQuery->exec();
}

bool Log::addNewusr(QString name,QString pwd)
{
    usrQuery->exec(QString("select password from player where (ID = '%1')").arg(name));
    if(usrQuery->next())
        return false;
    else
    {
        usrQuery->last();
        usrQuery->prepare("insert into player(ID,password,alive,ratio,number)"
                         "values (?,?,0,0,0)");
        usrQuery->addBindValue(name);
        usrQuery->addBindValue(pwd);
        usrQuery->exec();
        return true;
    }
}

void Log::addPokemon(QString name)
{
    usrQuery->prepare("update player set pokemon1=?,level1=? where ID = ?");
    usrQuery->addBindValue("Charmander");
    usrQuery->addBindValue(1);
    usrQuery->addBindValue(name);
    usrQuery->exec();
}

QList<QString>& Log::getUsr()
{
    usrQuery->exec("select * from player");
    QList<QString> *usr = new QList<QString>;
    qint32 i = 0;
    qint32 count = 0;
    for(usrQuery->first();usrQuery->seek(count);usrQuery->next())
    {
        while(usrQuery->value(i).toString() != "")
        {
            if(i == 1)
            {
                i++;
                continue;
            }
            usr->append(usrQuery->value(i).toString());
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

