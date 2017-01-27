#include "boardsquare.h"

//default constructor
BoardSquare::BoardSquare(QPointF p, qreal w, qreal h, int c) : BoardItem(p, w, h)
{
    m_empty = true;
    m_color = c;
    m_mark = NONMARKED;
    setPos(m_location);
}

bool BoardSquare::is_empty()
{
    return m_empty;
}

//cleans square
void BoardSquare::set_empty(bool f)
{
    m_empty = f;
}

//marks square(blue or green)
void BoardSquare::set_mark(int m)
{
    m_mark = m;
}

//paints rectangle
void BoardSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QBrush brush(Qt::SolidPattern);
    if (m_color == WHITE)
        brush.setColor(Qt::white);
    else brush.setColor(Qt::black);
    painter->setBrush(brush);
    painter->drawRect(boundingRect());
    if (m_mark)
    {
        brush.setStyle(Qt::DiagCrossPattern);
        if (m_mark == GREEN)
            brush.setColor(Qt::green);
        else if (m_mark == BLUE)
            brush.setColor(Qt::blue);
        painter->fillRect(boundingRect(), brush);
    }
}


