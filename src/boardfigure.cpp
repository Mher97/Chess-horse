#include "boardfigure.h"

BoardFigure::BoardFigure(QPointF point, qreal w, qreal h, QString str) : BoardItem(point, w, h)
{
    m_path = str;
    m_source = QImage(m_path);
    setPos(m_location);
}

//changes item location on the screen
void BoardFigure::change_location(QPointF p)
{
    m_location = p;
    setPos(m_location);
}

//moves item on the screen changing its position
void BoardFigure::move(qreal d, qreal k)
{
    m_location.rx() += d;
    m_location.ry() += (d*k);
    change_location(m_location);
}

//paints item image into rectangle
void BoardFigure::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   painter->drawImage(boundingRect(), m_source);
}

