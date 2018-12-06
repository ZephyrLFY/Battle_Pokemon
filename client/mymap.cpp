#include "mymap.h"

Man::Man()
{
    setPos(290, 120);
}

QRectF Man::boundingRect() const
{
    return QRectF(-25,-25,50, 50 );
}

void Man::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), Qt::red);

    painter->restore();
}

QPainterPath Man::shape() const
{
    QPainterPath p;
    p.addEllipse(QPointF(25 / 2, 25 / 2), 10, 10);
    return p;
}

House::House(qreal x,qreal y)
{
    setPos(x,y);
}

QRectF House::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void House::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), Qt::blue);

    painter->restore();
}

QPainterPath House::shape() const
{
    QPainterPath p;
    p.addRect(QRectF(-30,-30,60,60));
    return p;
}
