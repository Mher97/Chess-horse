#ifndef HORSE_H
#define HORSE_H

#include <QGraphicsItem>
#include <QPainter>
#include "const.h"

/*board items base.
  Derived from QGraphicsitem*/

class BoardItem : public QGraphicsItem
{
    public:
        BoardItem(QPointF = QPointF(0, 0), qreal = 0, qreal = 0);
        QRectF get_location()const;
    protected:
        QPointF m_location; //location
        qreal m_width;      //bounding rectangle width
        qreal m_height;     //.................. height
        virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) = 0;
        QRectF boundingRect()const;
};

#endif // HORSE_H
