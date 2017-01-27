#ifndef BOARDFIGURE_H
#define BOARDFIGURE_H

#include "boarditem.h"

/*implements chess horse and flag
 * as a 2-D graphic object.
  inherited from BoardItem*/

class BoardFigure :public BoardItem
{
    public:
        BoardFigure(QPointF = QPointF(0, 0), qreal = 0, qreal = 0, QString = NULL);
        void change_location(QPointF);
        void move(qreal x, qreal k);
    private:
        QImage m_source;    //image
        QString m_path;     //image path
    protected:
        void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // BOARDFIGURE_H
