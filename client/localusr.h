#ifndef LOCALUSR_H
#define LOCALUSR_H
#include <QApplication>
#include "petcreating.h"

class localUsr
{
public:
    localUsr(QString name);
    ~localUsr();

    QString getName();

    void initUsr(QList<QString> &usr);

    void addPoke(QString name,qint32 level,qint32 exp,qint32 index);

    void dltPoke(QString name,qint32 level,qint32 exp,qint32 index);

    void dealBadge(qint32 num,qint32 high);

    pokemon* chosePoke();

    pokemon* getEnm();

    void whichBattle(bool flag);

    void autoBattle(bool flag);

    bool getBattle();

    bool getAuto();

    void choseToBattle(qint32 which);

    void createEnm(QList<QString> &enm);

private:
    QString usrName;
    pokemon* poke[7];
    bool whichBtl;
    bool autoBtl;
    qint32 chosenPoke;
    pokemon* enmPoke;
};

#endif // LOCALUSR_H
