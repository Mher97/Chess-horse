#include "boarditem.h"

//default constructor
BoardItem::BoardItem(QPointF point, qreal w, qreal h)
{
    m_location = point;
    m_width = w;
    m_height = h;
    setPos(m_location);
}

//returns item bounding rectangle for item location
QRectF BoardItem::get_location()const
{
    return QRectF(m_location,QSize(m_width,m_height));
}

QRectF BoardItem::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}


