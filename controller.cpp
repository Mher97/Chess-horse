#include "controller.h"

//array of chess horse all possible ways.it is used for BFS
array<pair<int,int>, 8> Controller::m_ways =array<pair<int,int> ,8>({{make_pair(-1, -2), make_pair(1, -2),
                                                                      make_pair(-2,- 1), make_pair(2, -1),
                                                                      make_pair(-2, 1), make_pair(2, 1),


                                                                      make_pair(-1, 2), make_pair(1,2)}});
//single instance initialize
Controller* Controller::m_instance = new Controller();

//private constructor
Controller::Controller()
{
    ;
}

//returns pointer on the private single instance
Controller* Controller::get_instance()
{
    return m_instance;
}

//checks is the click on board and returns board square number
pair<int,int> Controller::click_handler(array<array<BoardSquare*,BOARDSIZE>,BOARDSIZE> &B, QPointF p)
{
    pair<int,int> answer=make_pair(-1, -1);
    int i, j;
    for (i = 0; i < BOARDSIZE; ++i)
    {
        for (j = 0; j < BOARDSIZE; ++j)
        {
            if (belong(B[i][j]->get_location(),p) && B[i][j]->is_empty())
            {
                B[i][j]->set_empty(false);
                return answer = make_pair(i, j);
            }
        }
    }
    return answer;
}

//checks is the point belong in rectangle
bool Controller::belong(QRectF r, QPointF p)
{
    if (p.x() >= r.topLeft().x() && p.x() <= r.topRight().x())
    {
        if (p.y() >= r.topLeft().y() && p.y() <= r.bottomLeft().y())
        {
            return true;
        }
    }
    return false;
}

//finds connecting two points line equation gradient
double Controller::linear_equation(QPointF p1, QPointF p2)
{
    return atan(abs((p1.ry() - p2.ry()) / (p1.rx() - p2.rx())));
}

//implements run of first level
void Controller::run1(pair<int, int> from, pair<int, int> to, vector<pair<int,int>> &path)
{
    BFS(from, to, make_pair(-1,-1));
    path_finder(to, path);
}

//implements run of second level
void Controller::run2(pair<int, int> v1, pair<int, int> v2, vector<pair<int, int> > &path1, vector<pair<int, int> > &path2)
{
    int i, j;
    vector<vector<int>> marked_helper = vector<vector<int>>(BOARDSIZE,vector<int>(BOARDSIZE, INF));
    vector<vector<pair<int,int>>>parent_helper = vector<vector<pair<int,int>>>
            (BOARDSIZE, vector<pair<int,int>>(BOARDSIZE, make_pair(-1,-1)));
    for (i = 0; i < BOARDSIZE; ++i)
    {
        for (j = 0; j < BOARDSIZE; ++j)
        {
            BFS(make_pair(i,j), v1, v2);
            if (m_marked[v1.first][v1.second] == m_marked[v2.first][v2.second]
                    && m_marked[v1.first][v1.second] < marked_helper[v1.first][v1.second])
            {
                marked_helper = m_marked;
                parent_helper = m_parent;
            }
        }
    }
    if (marked_helper[v1.first][v1.second] == marked_helper[v2.first][v2.second])
    {
        if (marked_helper[v1.first][v1.second]!=INF)
        {
             m_parent = parent_helper;
             path_finder(v1, path1);
             path_finder(v2, path2);
        }
    }
}

//breadth first search on rectangular field of a connected cells
void Controller::BFS(pair<int, int> from, pair<int, int> dest1, pair<int,int> dest2 = (make_pair(-1,-1)))
{
    list<pair<int,int>> fringe;
    pair<int,int> to;
    m_marked = vector<vector<int>>(BOARDSIZE,vector<int>(BOARDSIZE, INF));
    m_parent = vector<vector<pair<int,int>>>(BOARDSIZE, vector<pair<int,int>>(BOARDSIZE, make_pair(-1,-1)));
    fringe.push_back(from);
    m_marked[from.first][from.second] = 0;
    while(!fringe.empty())
    {
        from = fringe.front();
        fringe.pop_front();
        if (dest2==make_pair(-1, -1))
        {
            if (from == dest1)
                break;
        }
        else
        {
            if(from == dest2 || from == dest1)
            {
                if(m_marked[dest2.first][dest2.second] == m_marked[dest1.first][dest1.second])
                    break;
            }
        }
        for (int i = 0;i <8 ;++i)
        {
            to = make_pair(from.first + m_ways[i].first, from.second + m_ways[i].second);
            if (check(to) && m_marked[to.first][to.second] > m_marked[from.first][from.second] + 1)
            {
                m_marked[to.first][to.second] = m_marked[from.first][from.second] + 1;
                m_parent[to.first][to.second] = from;
                fringe.push_back(to);
            }
        }
    }
}

//finds shrtes path between 2 squares on the board
void Controller::path_finder(pair<int, int> pt, vector<pair<int, int> > &path)
{
    while(pt != (make_pair(-1,-1)))
    {
        path.push_back(pt);
        pt=m_parent[pt.first][pt.second];
    }
    reverse(path.begin(),path.end());
}

//checks whether square in the board range or no
bool Controller::check(pair<int,int> p)
{
    if (p.first >= 0 && p.first < BOARDSIZE)
        if (p.second >= 0 && p.second <= BOARDSIZE)
            return true;
    return false;
}



