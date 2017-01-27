#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "boardsquare.h"
#include "boardfigure.h"

/*Mathematical and algorithmic problems are solved with the help of this class.
 *Class is implemented through singleton design pattern*/

class Controller
{
    public:
        static Controller* get_instance();
        pair<int,int> click_handler(array<array<BoardSquare*,BOARDSIZE>,BOARDSIZE>&, QPointF);
        bool belong(QRectF R, QPointF p);
        double linear_equation(QPointF, QPointF);
        void run1(pair<int, int>, pair<int, int>, vector<pair<int, int>>&);
        void run2(pair<int, int>, pair<int, int>, vector<pair<int, int>>&, vector<pair<int,int>>&);
    private:
        Controller();
        static Controller *m_instance;
        bool check(pair<int,int>);
        void BFS(pair<int, int>, pair<int, int>, pair<int,int>);
        void path_finder(pair<int, int>, vector<pair<int,int>>&);
        vector<vector<pair<int,int>>> m_parent;                 //matrix of squares parents(BFS)
        vector<vector<int>> m_marked;                           //squares distance matrix(BFS)
        static array<pair<int,int>, 8> m_ways;
};

#endif // CONTROLLER_H
