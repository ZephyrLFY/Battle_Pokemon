#ifndef MYMAP_H
#define MYMAP_H
#include <QGraphicsItem>
#include <QPainter>

class Man : public QGraphicsItem
{
public:
    Man();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
};

class House : public QGraphicsItem
{
public:
    House(qreal x,qreal y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
};

#endif // MYMAP_H
