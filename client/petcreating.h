#ifndef PETCREATING_H
#define PETCREATING_H
#include <iostream>
#include <ctime>
#include <QApplication>
#include <QtGlobal>
#include <QTime>

class pokemon : public QObject
{
    Q_OBJECT
public:
    pokemon();//构造函数，初始化一个默认小精灵
    bool alive();//存活情况
    virtual void attack() = 0;//攻击函数，根据类型有不同
    double atkf();//攻击频率
    double damagecost();//造成伤害
    void damagedeal(double damage,uint ran);//计算伤害，修改血量
    void changetype();//实例化精灵时根据类型而调节属性
    void expup(int bonus);//获得经验值
    int gain();//对方会获得多少经验值
    bool upornot();//经验是否满足升级
    void lvlup();//升级
    void hpfull();//回满血
    int type = 0;//小精灵类型
    void Test();//测试函数
private:
    int level;//等级
    int exp;//经验
    double atk;//攻击力
    int def;//防御力
    double hp;//血量
    int fullhp;//满血量
    double interval;//攻击间隔
};

class str_pkm : public pokemon//力量型
{};

class fat_pkm : public pokemon//肉盾型
{};

class def_pkm : public pokemon//防御型
{};

class agi_pkm : public pokemon//敏捷型
{};

class Hitmonlee : public str_pkm//沙瓦朗
{
public:
    void attack();
private:
    std::string name = "Hitmonlee";
};

class Charmander : public str_pkm//小火龙
{
public:
    void attack();
private:
    std::string name = "Charmander";
};

class Squirtle : public str_pkm//杰尼龟
{
public:
    void attack();
private:
    std::string name = "Squirtle";
};

class Licktung : public fat_pkm//大舌头
{
public:
    void attack();
private:
    std::string name = "Licktung";
};

class Muk : public fat_pkm//臭臭泥
{
public:
    void attack();
private:
    std::string name = "Muk";
};

class Krabby : public fat_pkm//大钳蟹
{
public:
    void attack();
private:
    std::string name = "Krabby";
};

class Geodude : public def_pkm//小拳石
{
public:
    void attack();
private:
    std::string name = "Geodude";
};

class Shellder :public def_pkm//大舌贝
{
public:
    void attack();
private:
    std::string name = "Shellder";
};

class Onix : public def_pkm//大岩蛇
{
public:
    void attack();
private:
    std::string name = "Onix";
};

class Bulbasaur : public agi_pkm//妙蛙种子
{
public:
    void attack();
private:
    std::string name = "Bulbasaur";
};

class Pidgeotto : public agi_pkm//比比鸟
{
public:
    void attack();
private:
    std::string name = "Pidgeotto";
};

class Pikachu : public agi_pkm//皮卡丘
{
public:
    void attack();
private:
    std::string name = "Pikachu";
};

pokemon* chooseyourpet();

void beat(pokemon &a,pokemon&b,int ran);

void result(pokemon &a,pokemon &b);

void battle(pokemon &a,pokemon &b);

#endif // PETCREATING_H
