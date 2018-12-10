#include "localusr.h"
#include "wideuse.h"

localUsr::localUsr(QString name)
{
    this->usrName = name;
}

localUsr::~localUsr()
{
    for(int i = 0; i < 7; i++)
    {
        delete poke[i];
    }
    delete *poke;
}

void localUsr::initUsr(QList<QString> &poke)
{
    qint32 num = poke.at(0).toInt();
    poke.removeFirst();
    if(poke.at(0) != "over")
    {
        QString pokeName;
        qint32 lvl = 0;;
        qint32 exp = 0;
        for(int i = 0; i < num; i++)
        {
            pokeName = poke.at(0);
            poke.removeFirst();
            lvl = poke.at(0).toInt();
            poke.removeFirst();
            exp = poke.at(0).toInt();
            poke.removeFirst();
            poke.removeFirst();
            addPoke(pokeName,lvl,exp,i);
        }
    }

}

void localUsr::addPoke(QString name,qint32 level,qint32 exp,qint32 index)
{
    if(name == "Hitmonlee")
        poke[index] = new Hitmonlee(level,exp);
    else if(name == "Charmander")
        poke[index] = new Charmander(level,exp);
    else if(name == "Squirtle")
        poke[index] = new Squirtle(level,exp);
    else if(name == "Licktung")
        poke[index] = new Licktung(level,exp);
    else if(name == "Muk")
        poke[index] = new Muk(level,exp);
    else if(name == "Krabby")
        poke[index] = new Krabby(level,exp);
    else if(name == "Shellder")
        poke[index] = new Shellder(level,exp);
    else if(name == "Onix")
        poke[index] = new Onix(level,exp);
    else if(name == "Geodude")
        poke[index] = new Geodude(level,exp);
    else if(name == "Bulbasaur")
        poke[index] = new Bulbasaur(level,exp);
    else if(name == "Pidgeotto")
        poke[index] = new Pidgeotto(level,exp);
    else if(name == "Pikachu")
        poke[index] = new Pikachu(level,exp);

}

void localUsr::dltPoke(QString name,qint32 level,qint32 exp,qint32 index)
{
    ;
}

pokemon* localUsr::chosePoke()
{
    return poke[chosenPoke];
}

pokemon* localUsr::getEnm()
{
    return enmPoke;
}

void localUsr::choseToBattle(qint32 which)
{
    this->chosenPoke = which;
}

void localUsr::createEnm(QList<QString> &enm)
{
    QString pokeName = enm.at(0);
    qint32 pokeLvl = enm.at(1).toInt();
    qint32 pokeExp = enm.at(2).toInt();
    if(pokeName == "Hitmonlee")
        enmPoke = new Hitmonlee(pokeLvl,pokeExp);
    else if(pokeName == "Charmander")
        enmPoke = new Charmander(pokeLvl,pokeExp);
    else if(pokeName == "Squirtle")
        enmPoke = new Squirtle(pokeLvl,pokeExp);
    else if(pokeName == "Licktung")
        enmPoke = new Licktung(pokeLvl,pokeExp);
    else if(pokeName == "Muk")
        enmPoke = new Muk(pokeLvl,pokeExp);
    else if(pokeName == "Krabby")
        enmPoke = new Krabby(pokeLvl,pokeExp);
    else if(pokeName == "Shellder")
        enmPoke = new Shellder(pokeLvl,pokeExp);
    else if(pokeName == "Onix")
        enmPoke = new Onix(pokeLvl,pokeExp);
    else if(pokeName == "Geodude")
        enmPoke = new Geodude(pokeLvl,pokeExp);
    else if(pokeName == "Bulbasaur")
        enmPoke = new Bulbasaur(pokeLvl,pokeExp);
    else if(pokeName == "Pidgeotto")
        enmPoke = new Pidgeotto(pokeLvl,pokeExp);
    else
        enmPoke = new Pikachu(pokeLvl,pokeExp);
}

QString localUsr::getName()
{
    return usrName;
}

void localUsr::whichBattle(bool flag)
{
    this->whichBtl = flag;
}

void localUsr::autoBattle(bool flag)
{
    this->autoBtl = flag;
}

bool localUsr::getBattle()
{
    return whichBtl;
}

bool localUsr::getAuto()
{
    return autoBtl;
}
