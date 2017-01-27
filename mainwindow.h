#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <QSlider>
#include <QFont>
#include <QSound>
#include <QMediaPlayer>
#include <QLabel>
#include "controller.h"

namespace Ui
{
    class MainWindow;
}

/*implements program main window*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        qreal m_width;
        qreal m_height;
        QString m_source_path;
        QGraphicsView *m_view;
        QGraphicsScene *m_scene;
        BoardFigure *m_white_horse;                                 //white horse
        BoardFigure *m_black_horse;                                 //black horse
        BoardFigure *m_flag;                                        //flag
        array<array<BoardSquare*, BOARDSIZE>, BOARDSIZE > m_board;  //chess board
        vector<pair<int,int>> m_figure_path1;                       //white horse path on the board
        vector<pair<int,int>> m_figure_path2;                       //black horse path on the board
        int m_state;                                                //level state
        int m_level;                                                //program level
        pair<int,int> m_wh_moving_position;                         //white horse moving destination
        pair<int,int> m_bh_moving_position;                         //black .............
        pair<int,int> m_flag_moving_position;                       //flag  .............
        pair<int,int> m_source1_position;                           //first notified items position on the board
        pair<int,int> m_source2_position;                           //second .......................
        vector<pair<int,int>>::iterator m_it1;                      //iterator on the white horse shortest path cells vector
        vector<pair<int,int>>::iterator m_it2;                      //......................black .........................
        vector<QTimer*> m_timers;
        array<QPushButton*,7> m_buttons;                            //buttons on the screen
        array<QGraphicsTextItem*,16> m_texts;                       //board row and columns values on the scene
        QSound *m_sound;
        pair<QPushButton*,QSlider*> m_md_ctrl;                      //music sound controller
        QWidget *m_about;                                           //there is writen about program on this widget
        array<QWidget*,2> m_messages;
        pair<QLabel*,QLabel*> m_labels;                             //there are writen horses paths

        void scene_maker();
        void items_maker();
        void buttons_maker();
        void media_maker();
        void message_maker();
        void about_maker();
        void labels_maker();
        void restore();

    protected:
        void mousePressEvent(QMouseEvent*);

    private slots:
        void BoardFigure_move(BoardFigure*, pair<int,int>);
        void white_horse_move_helper();
        void white_horse_move();
        void black_horse_move_helper();
        void black_horse_move();
        void flag_move();
        void levels_start_helper();
        void level1_start();
        void level2_start();
        void new_slot();
        void back_slot();
        void run_slot();
        void media_slot();
};

#endif // MAINWINDOW_H
