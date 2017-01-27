#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QGraphicsItem>
#include <QPainter>
#include "boarditem.h"

/*implements board square
 * as a 2-D graphic object.
 * Derived from BoardItem abstract class*/

class BoardSquare : public BoardItem
{
    public:
        BoardSquare(QPointF = QPointF(0, 0), qreal = 0, qreal = 0, int = 0);
        bool is_empty();
        void set_empty(bool);
        void set_mark(int);
    private:
        int m_color;        //black or white
        int m_mark;         //blue, green or nonmarked
        bool m_empty;
    protected:
        void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // BOARDSQUARE_H
