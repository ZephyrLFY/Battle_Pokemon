#include"petcreating.h"
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;

void beat(pokemon &a,pokemon&b,qint32 ran)//攻击函数，攻击者和被攻击者
{
    a.attack();
    b.damagedeal(a.damagecost(),ran);
}

void result(pokemon &a,pokemon &b)
{
    if((!a.alive())&&(!b.alive()))
        qDebug() << "Both of them are dead." << endl;
    else if(a.alive())
    {
        qDebug() << "Congratulations! Your pet wins!" << endl;
        a.expup(b.gain());
        qDebug() << "You gain " << b.gain() << " exp." << endl;
        if(a.upornot())
            a.lvlup();
    }
    else
        qDebug() << "Sorry, your pet is dead." << endl;
}

void battle(pokemon &a,pokemon &b)/*根据时间以及攻击间隔，互相攻击*/
{
    clock_t a_delay = a.atkf() * CLOCKS_PER_SEC;
    clock_t b_delay = b.atkf() * CLOCKS_PER_SEC;
    clock_t a_start = clock();
    clock_t b_start = clock();
    while(a.alive()&&b.alive())
    {
        while((clock()-a_start < a_delay)&&(clock()-b_start < b_delay))
            ;
        if(clock()-a_start >= a_delay)
        {
            beat(a,b,0);
            a_start = clock();
        }
        if(clock()-b_start >= b_delay)
        {
            beat(b,a,1234);
            b_start = clock();
        }
    }
    //result(a,b);
}

pokemon::pokemon()
{
    this->level = 1;
    this->atk = 15;
    this->def = 7;
    this->exp = 0;
    this->hp = 300;
    this->fullhp = 300;
    this->interval = 1;
}

void pokemon::changetype()
{
    if(type == 1)//力量型
    {
        atk += 4;
        def = def - 2;
    }
    else if(type == 2)//肉盾型
    {
        atk = atk - 1;
        def++;
        hp += 20;
        fullhp += 20;
    }
    else if(type == 3)//防御型
    {
        atk = atk - 2;
        def += 3;
    }
    else//敏捷型
    {
        atk = atk + 1;
        def = def - 1;
        interval = interval - 0.1;
    }
}

bool pokemon::alive()
{
    if(hp > 0)
        return 1;
    else
        return 0;
}

double pokemon::atkf()
{
    return interval;
}

double pokemon::damagecost()
{
    return atk;
}

void pokemon::damagedeal(double damage,qint32 ran)
{
    damage = damage - def;
    if(damage < 0)
        damage = 0;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()) + ran);
    int dodge = qrand() % 100;
    bool isDodge = 0;
    if(dodge <= 10)
    {
        if(type == 4)
        {
            damage = 0;
            qDebug() << "被闪避了! ";
            isDodge = 1;
        }
        else
        {
            if(damage <= 5)
            {
                damage = 0;
                qDebug() << "被闪避了! ";
                isDodge = 1;
            }
            else;
        }
    }
    if(!isDodge)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()) + ran + ran);
        int crush = qrand() % 100;
        if(crush > 90)
        {
            damage = damage * 1.5;
            qDebug() << "造成了暴击! ";
        }
    }
    hp = hp - damage;
    qDebug() << "造成了" << damage << "点伤害。" << endl;
    if(hp < 0)
        hp = 0;
}

void pokemon::hpfull()
{
    hp = fullhp;
}

int pokemon::gain()
{
    return 10*level;
}

void pokemon::expup(int bonus)
{
    exp += bonus;
}

bool pokemon::upornot()
{
    if(exp >= 5*level)
        return 1;
    else
        return 0;
}

void pokemon::lvlup()//升级函数，根据精灵类型会有不同
{
    qDebug() << "Level up!" << endl;
    level++;
    exp = 0;
    hpfull();
    if(type == 1)
    {
        atk += 12;
        def += 5;
        hp += 62;
        fullhp += 62;
    }
    else if(type == 2)
    {
        atk += 7;
        def += 6;
        hp += 108;
        fullhp += 108;
    }
    else if(type == 3)
    {
        atk += 7;
        def += 7;
        hp += 60;
        fullhp += 60;
    }
    else
    {
        atk += 8;
        def += 5;
        hp += 50;
        fullhp += 50;
        interval = interval - 0.03;
    }
}

void pokemon::Test()
{
    qDebug() << hp << " " << atk << " " << def << " " << interval << endl;
}

void Hitmonlee::attack()
{
    qDebug() << "Hitmonlee : \"Hit!\"";
}

void Charmander::attack()
{
    qDebug() << "Charmander : \"Fire!\"";
}

void Squirtle::attack()
{
    qDebug() << "Squirtle : \"Taste my water!\"";
}

void Licktung::attack()
{
    qDebug() << "Licktung : \"Lick, lick!\"";
}

void Muk::attack()
{
    qDebug() << "Muk : \"Eat my gross muk!\"";
}

void Krabby::attack()
{
    qDebug() << "Krabby : \"No one can live under my claw!\"";
}

void Geodude::attack()
{
    qDebug() << "Geodude : \"Stone power!\"";
}

void Shellder::attack()
{
    qDebug() << "Shellder : \"Shield smash!\"";
}

void Onix::attack()
{
    qDebug() << "Onix : \"You will die for your arrogance!\"";
}

void Bulbasaur::attack()
{
    qDebug() << "Bulbasaur : \"Eat my seed!\"";
}

void Pidgeotto::attack()
{
    qDebug() << "Pidgeotto : \"Can you defend my air attack?\"";
}

void Pikachu::attack()
{
    qDebug() << "Pikachu : \"Pika pika!\"";
}
/*
pokemon* chooseyourpet()
{
    int type = 0;
    int specy = 0;
    pokemon *born;
    while(((type != 1)&&(type != 2)&&(type != 3)&&(type != 4))||(specy == 4))
    {
        qDebug() << "Now you can choose one pokemon." << endl << "Which type do you want?" << endl << "Press 1 for strong type, 2 for fat type, 3 for defence type, and 4 for agile type: " ;
        cin >> type;
        qDebug() << "I got it!" << endl;
        if(type == 1)
        {
            while((specy != 1)&&(specy != 2)&&(specy != 3)&&(specy != 4))
            {
                qDebug() << "Which pokemon do you want? Press 1 for Hitmonlee, 2 for Charmander, 3 for Squirtle, 4 to re-choose the type: " ;
                cin >> specy;
                if(specy == 1)
                    born = new Hitmonlee;
                else if(specy == 2)
                    born = new Charmander;
                else if(specy == 3)
                    born = new Squirtle;
                else if(specy == 4)
                    type = 0;
                else;
                if((specy == 1)||(specy == 2)||(specy == 3))
                    born->type = 1;
            }
        }
        else if(type == 2)
        {
            while((specy != 1)&&(specy != 2)&&(specy != 3)&&(specy != 4))
            {
                qDebug() << "Which pokemon do you want? Press 1 for Licktung, 2 for Muk, 3 for Krabby, 4 to re-choose the type: " ;
                cin >> specy;
                if(specy == 1)
                    born = new Licktung;
                else if(specy == 2)
                    born = new Muk;
                else if(specy == 3)
                    born = new Krabby;
                else if(specy == 4)
                    type = 0;
                if((specy == 1)||(specy == 2)||(specy == 3))
                    born->type = 2;
            }
        }
        else if(type == 3)
        {
            while((specy != 1)&&(specy != 2)&&(specy != 3)&&(specy != 4))
            {
                qDebug() << "Which pokemon do you want? Press 1 for Geodude, 2 for Shellder, 3 for Onix, 4 to re-choose the type: " ;
                cin >> specy;
                if(specy == 1)
                    born = new Geodude;
                else if(specy == 2)
                    born = new Shellder;
                else if(specy == 3)
                    born = new Onix;
                else if(specy == 4)
                    type = 0;
                if((specy == 1)||(specy == 2)||(specy == 3))
                    born->type = 3;
            }
        }
        else if(type == 4)
        {
            while((specy != 1)&&(specy != 2)&&(specy != 3)&&(specy != 4))
            {
                qDebug() << "Which pokemon do you want? Press 1 for Bulbarsaur, 2 for Pidgeotto, 3 for Pikachu, 4 to re-choose the type: " ;
                cin >> specy;
                if(specy == 1)
                    born = new Bulbasaur;
                else if(specy == 2)
                    born = new Pidgeotto;
                else if(specy == 3)
                    born = new Pikachu;
                else if(specy == 4)
                    type = 0;
                if((specy == 1)||(specy == 2)||(specy == 3))
                    born->type = 4;
            }
        }
        specy = 0;
    }
    born->changetype();
    return born;
}

int main()
{
    qDebug() << "This is the test version 0.0.1" << endl;
    pokemon *a,*b;
    a = chooseyourpet();
    b = chooseyourpet();
    for(int i = 0;i<14;i++)
    {
        a->lvlup();
        b->lvlup();
    }
    battle(*a,*b);
    a->Test();
    b->Test();
    return 0;
}*/
