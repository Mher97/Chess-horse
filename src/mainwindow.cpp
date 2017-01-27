#include "mainwindow.h"
#include "ui_mainwindow.h"

//explicit constructor
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene_maker();
    buttons_maker();
    media_maker();
    message_maker();
    about_maker();
    labels_maker();
    m_timers = vector<QTimer*>(5);
    for (int i = 0; i<5; ++i)
        m_timers[i] = new QTimer(this);
    m_sound = new QSound(m_source_path + for_paths[4]);
    m_level = m_state = 0;
    connect(m_timers[0],SIGNAL(timeout()),this,SLOT(white_horse_move_helper()));
    connect(m_timers[1],SIGNAL(timeout()),this,SLOT(white_horse_move()));
    connect(m_timers[2],SIGNAL(timeout()),this,SLOT(black_horse_move_helper()));
    connect(m_timers[3],SIGNAL(timeout()),this,SLOT(black_horse_move()));
    connect(m_timers[4],SIGNAL(timeout()),this,SLOT(flag_move()));
    connect(m_buttons[0], SIGNAL(clicked()),this, SLOT(level1_start()));
    connect(m_buttons[1], SIGNAL(clicked()),this, SLOT(level2_start()));
    connect(m_buttons[2], SIGNAL(clicked()),m_about, SLOT(show()));
    connect(m_buttons[3], SIGNAL(clicked()),this, SLOT(close()));
    connect(m_buttons[4], SIGNAL(clicked()),this, SLOT(new_slot()));
    connect(m_buttons[5], SIGNAL(clicked()),this, SLOT(run_slot()));
    connect(m_buttons[6], SIGNAL(clicked()),this, SLOT(back_slot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//makes 2d scene on the screen
void MainWindow::scene_maker()
{
    m_source_path = QApplication::applicationDirPath() + for_paths[0];
    QPixmap pm(m_source_path + for_paths[3]);
    m_width = QApplication::desktop()->geometry().width();
    m_height = QApplication::desktop()->geometry().height();
    this->setGeometry(0, 0, m_width, m_height);
    m_view = new QGraphicsView(this);
    m_view->setGeometry(0, 0, m_width, m_height);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, m_width, m_height);
    m_scene->setBackgroundBrush(pm.scaled(m_width,m_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    m_view->setScene(m_scene);
    items_maker();
}

//creates 2-d scene items(horses, flag and board)
void MainWindow::items_maker()
{
    qreal x = m_width*for_board[0], y = m_height*for_board[1],
          l1 = m_width* for_board[2], l2 = m_height*for_board[3],
          x2 = m_width*for_texts_pos[0].first, y2 = m_height*for_texts_pos[0].second,
          x3 = m_width*for_texts_pos[1].first, y3 = m_height*for_texts_pos[1].second;
    int color = WHITE, i ,j;
    for (i = 0; i < BOARDSIZE; ++i)
    {
        if (i%2)
            color = BLACK;
        else color = WHITE;
        for (j = 0; j < BOARDSIZE; ++j)
        {
            m_board[i][j] = new BoardSquare(QPointF(x,y), l1, l2, color);
            x+=l1;
            color = 1 -color;
        }
        y += l2;
        x = m_width*for_board[0];
    }
    m_white_horse = new BoardFigure(QPointF(m_width * for_items[0].first, m_height * for_items[0].second),
                             m_width * for_board[2], m_height * for_board[3], m_source_path + for_paths[1]);
    m_flag = new BoardFigure(QPointF(m_width * for_items[1].first, m_height * for_items[1].second),
                             m_width * for_board[2], m_height * for_board[3], m_source_path + for_paths[2]);
    m_black_horse = new BoardFigure(QPointF(m_width * for_items[1].first, m_height * for_items[1].second),
                             m_width * for_board[2], m_height * for_board[3], m_source_path + for_paths[7]);
    for (i = 0; i < BOARDSIZE; ++i)
    {
        m_texts[i]=new QGraphicsTextItem(for_texts[i]);
        m_texts[i + BOARDSIZE] = new QGraphicsTextItem(for_texts[i + BOARDSIZE]);
        m_texts[i]->setFont(QFont("Sans",min(l1, l2)/3.0,QFont::Normal));
        m_texts[i + BOARDSIZE]->setFont(QFont("Sans",min(l1,l2)/3.0,QFont::Normal));
        m_texts[i]->setPos(x2, y2);
        m_texts[i + BOARDSIZE]->setPos(x3, y3);
        y2+=l2, x3+=l1;
    }
}

//makes using buttons
void MainWindow::buttons_maker()
{
    int i;
    QFont f("Times", m_height*0.04, QFont::Normal, true);
    for (i = 0; i < 7; ++i)
    {
        m_buttons[i] = new QPushButton(for_buttons_text[i],this);
        m_buttons[i]->setFont(f);
        m_buttons[i]->setStyleSheet("QPushButton { background-color : transparent; color : white; }");
        m_buttons[i]->setGeometry(m_width*for_buttons[7], m_height*for_buttons[i],
                m_width*for_buttons[8], m_height*for_buttons[9]);
        if (i > 3)
            m_buttons[i]->setVisible(false);
    }
}

//makes music with controller
void MainWindow::media_maker()
{
    QMediaPlayer *pl = new QMediaPlayer(this);
    QTimer *tm;
    pl->setMedia(QUrl::fromLocalFile(m_source_path + for_paths[5]));
    pl->setVolume(15);
    pl->play();
    m_md_ctrl.first = new QPushButton(this);
    m_md_ctrl.first->setGeometry((int)(m_width * for_media[0].first), (int)(m_height * for_media[0].second),
                                   (int)(m_width * for_media[1].first), (int)(m_width * for_media[1].second));
    m_md_ctrl.first->setIcon(QIcon(m_source_path + for_paths[6]));
    m_md_ctrl.first->setStyleSheet("QPushButton { background-color : transparent; color : white; }");
    m_md_ctrl.second = new QSlider(Qt::Vertical, this);
    m_md_ctrl.second->setGeometry((int)(m_width * for_media[2].first),(int)(m_height * for_media[2].second),
                       (int)(m_width * for_media[3].first), (int)(m_height * for_media[3].second));
    m_md_ctrl.second->setValue(15);
    m_md_ctrl.second->setRange(0, 100);
    m_md_ctrl.second->hide();
    tm = new QTimer(this);
    connect(m_md_ctrl.first, SIGNAL(clicked()), this, SLOT(media_slot()));
    connect(m_md_ctrl.second, SIGNAL(valueChanged(int)), pl, SLOT(setVolume(int)));
    connect(tm, SIGNAL(timeout()), pl, SLOT(play()));
    tm->start(150000);
}

//makes messages(finish and impossible to start with this positions in the second level)
void MainWindow::message_maker()
{
    array<QPushButton*, 2> pb;
    array<QLabel*, 2> lb;
    for (int i = 0; i < 2; ++i)
    {
        m_messages[i] = new QWidget(this);
        m_messages[i]->setGeometry(m_width*for_message[0]/100, m_height*for_message[1]/100,
                m_width*for_message[2]/100, m_height*for_message[3]/100);
        m_messages[i]->setStyleSheet("QWidget { background-color : transparent; color : white; }");
        pb[i] = new QPushButton("OK",m_messages[i]);
        pb[i]->setGeometry(m_messages[i]->width()*for_message[4]/100, m_messages[i]->height()*for_message[5]/100,
                m_messages[i]->width()*for_message[6]/100, m_messages[i]->height()*for_message[7]/100);
        pb[i]->setFont(QFont("Sans",pb[i]->height()*50/100,QFont::Normal));
        pb[i]->setStyleSheet("QPushButton { background-color : transparent; color : white; }");
        lb[i] = new QLabel(m_messages[i]);
        lb[i]->setGeometry(m_messages[i]->width()*for_message[8]/100, m_messages[i]->height()*for_message[9]/100,
                m_messages[i]->width()*for_message[10]/100, m_messages[i]->height()*for_message[11]/100);
        lb[i]->setFont(QFont("Sans",lb[i]->height()*15/100,QFont::Normal));
        m_messages[i]->close();
    }
    lb[0]->setText("Work was \ncompleted");
    lb[1]->setText("Impossible to\nstart work");
    connect(pb[0],SIGNAL(clicked()),m_messages[0],SLOT(close()));
    connect(pb[1],SIGNAL(clicked()),m_messages[1],SLOT(close()));
}

//makes widget for about
void MainWindow::about_maker()
{
    QPushButton *pb;
    QLabel *lb;
    m_about = new QWidget(this);
    m_about->setGeometry(m_width*for_about[0]/100, m_height*for_about[1]/100,
            m_width*for_about[2]/100, m_height*for_about[3]/100);
    m_about->setStyleSheet("QWidget { background-color : transparent; color : white; }");
    m_about->hide();
    pb= new QPushButton("X",m_about);
    pb->setGeometry(m_about->width()*for_about[4]/100, m_about->height()*for_about[5]/100,
            m_about->width()*for_about[6]/100, m_about->height()*for_about[7]/100);
    pb->setFont(QFont("Sans", pb->height()/2, QFont::Normal));
    pb->setStyleSheet("QPushButton { background-color : transparent; color : black; }");
    lb = new QLabel("   User must select two different squares.\n"
                    "   Level1 - program will find chess horse \n"
                    "   shortest path between two squares.\n"
                    "   Level2 - program will find shortest\n"
                    "   path between two squares when\n"
                    "   two chess horses simultaneously\n"
                    "   start to move toward each other.\n\n"
                    "   created by Mher Hakobyan", m_about);
    lb->setGeometry(m_about->width()*for_about[8]/100, m_about->height()*for_about[9]/100,
            m_about->width()*for_about[10]/100, m_about->height()*for_about[11]/100);
    lb->setFont(QFont("Times",lb->height()*6/100,QFont::Normal, true));
    lb->setStyleSheet("QLabel { background-color : transparent; color : black; }");
    connect(pb,SIGNAL(clicked()),m_about,SLOT(close()));
}

//makes labels where must be writen horse paths
void MainWindow::labels_maker()
{
    m_labels.first = new QLabel(this);
    m_labels.first->setGeometry(m_width*for_labels[0]/100, m_height*for_labels[1]/100,
            m_width*for_labels[2]/100, m_height*for_labels[3]/100);
    m_labels.first->setStyleSheet("QLabel { background-color : transparent; color : black; }");
    m_labels.first->setFont(QFont("Sans", m_labels.first->height()*40/100, QFont::Normal, true));
    m_labels.second = new QLabel(this);
    m_labels.second->setGeometry(m_width*for_labels[0]/100, m_height*for_labels[4]/100,
            m_width*for_labels[2]/100, m_height*for_labels[3]/100);
    m_labels.second->setStyleSheet("QLabel { background-color : transparent; color : black; }");
    m_labels.second->setFont(QFont("Sans", m_labels.second->height()*40/100, QFont::Normal, true));
}

//click handling
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    pair<int,int> res;
    if (e->button()==Qt::LeftButton)
    {
        res = Controller::get_instance()->click_handler(m_board, e->screenPos());
        if (res!=make_pair(-1,-1))
        {
            if (m_state == 0 && m_level)
            {
                m_wh_moving_position = res;
                ++m_state;
                m_source1_position = res;
                m_timers[0]->start(100);
            }
            else if (m_state ==1)
            {
                if (m_level == 1)
                {
                    m_flag_moving_position = res;
                    m_timers[4]->start(100);
                }
                else if (m_level == 2)
                {
                    m_bh_moving_position = res;
                    m_timers[2]->start(100);
                }
                ++m_state;
                m_source2_position = res;
            }
        }
        m_scene->update();
    }
}

//item moving on the board before two points
void MainWindow::BoardFigure_move(BoardFigure *mv_item, pair<int,int> pos)
{
    QPointF p[5];
    qreal coef,dist;
    int i;
    p[0] = mv_item->get_location().topLeft();
    p[1] = mv_item->get_location().topRight();
    p[2] = mv_item->get_location().bottomLeft();
    p[3] = mv_item->get_location().bottomRight();
    p[4] = m_board[pos.first][pos.second]->get_location().topLeft();
    coef = Controller::get_instance()->linear_equation(p[0],p[4]);
    dist = min(mv_item->get_location().width(),mv_item->get_location().height())/10.0;
    if (p[4].rx()<=p[0].rx())
    {
        dist *= -10;
        if (p[4].ry() >= p[0].ry())
            coef *= -1;
    }
    if (p[4].rx()>=p[0].rx())
    {
        if (p[4].ry() <= p[0].ry())
            coef *= -1;
    }
    for (i = 0; i < 4; ++i)
    {
        if (Controller::get_instance()->belong(m_board[pos.first][pos.second]->get_location(),p[i]))
        {
            if (mv_item == m_white_horse)
                m_timers[0]->stop();
            if (mv_item == m_black_horse)
                m_timers[2]->stop();
            else if (mv_item == m_flag)
                m_timers[4]->stop();
            mv_item->change_location(m_board[pos.first][pos.second]->get_location().topLeft());
            if (m_level == 1 && m_state ==3)
            {
                if( m_it1 == m_figure_path1.end())
                    m_scene->removeItem(m_flag);
            }
            m_sound ->play();
            return;
        }
    }
    mv_item->move(dist,coef);
}

//white horse moving between two points
void MainWindow::white_horse_move_helper()
{
    BoardFigure_move(m_white_horse, m_wh_moving_position);
}

//white horse moving between two board squares(horse single step)
void MainWindow::white_horse_move()
{
    if (m_it1 == m_figure_path1.end())
    {
        m_messages[0]->show();
        m_timers[1]->stop();
    }
    else
    {
        QString helper;
        helper = m_labels.first->text();
        helper+=" -> ";
        helper.push_back(m_it1->second + 'a');
        helper.push_back(BOARDSIZE - m_it1->first + '0');
        m_labels.first->setText(helper);
        m_wh_moving_position = *m_it1;
        m_board[(m_it1 - 1)->first][(m_it1 - 1)->second]->set_mark(GREEN);
        m_timers[0]->start(100);
    }
    ++m_it1;
}

//black horse moving between two points
void MainWindow::black_horse_move_helper()
{
    BoardFigure_move(m_black_horse, m_bh_moving_position);
}

//black horse moving between two board squares(horse single step)
void MainWindow::black_horse_move()
{
    if (m_it2 == m_figure_path2.end())
        m_timers[3]->stop();
    else
    {
        QString helper;
        helper = m_labels.second->text();
        helper+=" -> ";
        helper.push_back(m_it2->second + 'a');
        helper.push_back(BOARDSIZE - m_it2->first + '0');
        m_labels.second->setText(helper);
        m_bh_moving_position = *m_it2;
        m_board[(m_it2 - 1)->first][(m_it2 - 1)->second]->set_mark(BLUE);
        m_timers[2]->start(100);
    }
    ++m_it2;
}

//flag moving between two points
void MainWindow::flag_move()
{
    BoardFigure_move(m_flag, m_flag_moving_position);
}

//helps initializing some variables before runing levels
void MainWindow::levels_start_helper()
{
    int i, j;
    m_state = 0;
    if (m_about->isActiveWindow())
        m_about->close();
    for (i = 0;i <4; ++i)
        m_buttons[i]->setVisible(false);
    for (i = 4; i < 7; ++i)
        m_buttons[i]->setVisible(true);
    for (i = 0; i < BOARDSIZE; ++i)
    {
        for (j = 0; j < BOARDSIZE; ++j)
        {
            m_scene->addItem(m_board[i][j]);
            m_board[i][j]->set_empty(true);
            m_board[i][j]->set_mark(NONMARKED);
        }
    }
    for (i = 0;i <16; ++i)
        m_scene->addItem(m_texts[i]);
    m_scene->addItem(m_white_horse);
}

//starts first level
void MainWindow::level1_start()
{
    m_level = 1;
    levels_start_helper();
    m_scene->addItem(m_flag);
}

//starts second level
void MainWindow::level2_start()
{
    m_level = 2;
    levels_start_helper();
    m_scene->addItem(m_black_horse);
}

//starts level again
void MainWindow::new_slot()
{
    int i ,j;
    restore();
    for (i = 0; i < BOARDSIZE; ++i)
    {
        for (j = 0; j < BOARDSIZE; ++j)
        {
            m_board[i][j]->set_empty(true);
            m_board[i][j]->set_mark(NONMARKED);
        }
    }
    if (m_level == 1)
    {
        if (!m_flag->isActive())
            m_scene->addItem(m_flag);
    }
    else if (m_level ==2)
    {
        if (!m_white_horse->isActive())
            m_scene->addItem(m_white_horse);
        if (!m_black_horse->isActive())
            m_scene->addItem(m_black_horse);
    }
    m_scene->update();
}

//returns program main menu state
void MainWindow::back_slot()
{
    int i, j;
    restore();
    for (i = 0;i < 7; ++i)
    {
        if (i < 4)
            m_buttons[i]->setVisible(true);
        else m_buttons[i]->setVisible(false);
    }
    for (i = 0; i < BOARDSIZE; ++i)
    {
        for (j = 0; j < BOARDSIZE; ++j)
            m_scene->removeItem(m_board[i][j]);
    }
    for (i = 0;i <16; ++i)
        m_scene->removeItem(m_texts[i]);
    m_scene->removeItem(m_white_horse);
    if (m_level == 1)
    {
        if (m_flag->isActive())
            m_scene->removeItem(m_flag);
    }
    else
    {
        if (m_black_horse->isActive())
            m_scene->removeItem(m_black_horse);
    }
    m_level = 0;
}

//restores some variables from new and back
void MainWindow::restore()
{
    int i ,j;
    m_state = 0;
    for (i = 0; i < 2; ++i)
    {
        if (m_messages[i]->isActiveWindow())
            m_messages[i]->close();
    }
    for (i = 0; i < 5; ++i)
    {
        if (m_timers[i]->isActive())
            m_timers[i]->stop();
    }
    m_labels.first->setText("");
    m_labels.second->setText("");
    m_figure_path1.clear();
    m_figure_path2.clear();
    for (i = 0; i < BOARDSIZE; ++i)
    {
        for (j = 0; j < BOARDSIZE; ++j)
        {
            m_board[i][j]->set_empty(true);
            m_board[i][j]->set_mark(NONMARKED);
        }
    }
    m_white_horse->change_location(QPointF(m_width * for_items[0].first, m_height * for_items[0].second));
    m_flag ->change_location(QPointF(m_width * for_items[1].first, m_height * for_items[1].second));
    m_black_horse ->change_location(QPointF(m_width * for_items[1].first, m_height * for_items[1].second));
}

//runs algorithms
void MainWindow::run_slot()
{
    if (m_level == 1 && m_state == 2)
    {
        QString helper("Path : ");
        m_state = 3;
        Controller::get_instance()->run1(m_source1_position, m_source2_position, m_figure_path1);
        m_it1 = m_figure_path1.begin() + 1;
        m_timers[1]->start(5000);
        helper.push_back(m_figure_path1[0].second + 'a');
        helper.push_back(BOARDSIZE - m_figure_path1[0].first + '0');
        m_labels.first->setText(helper);
    }
    else if (m_level == 2 && m_state == 2)
    {
        QString helper1("White horse : "), helper2("Black horse : ");
        m_state = 3;
        Controller::get_instance()->run2(m_source1_position, m_source2_position, m_figure_path1, m_figure_path2);
        if (!m_figure_path1.empty() && !m_figure_path2.empty())
        {
            reverse(m_figure_path1.begin(),m_figure_path1.end());
            reverse(m_figure_path2.begin(),m_figure_path2.end());
            m_it1 = m_figure_path1.begin() + 1;
            m_it2 = m_figure_path2.begin() + 1;
            helper1.push_back(m_figure_path1[0].second + 'a');
            helper1.push_back(BOARDSIZE - m_figure_path1[0].first + '0');
            helper2.push_back(m_figure_path2[0].second + 'a');
            helper2.push_back(BOARDSIZE - m_figure_path2[0].first + '0');
            m_labels.first->setText(helper1);
            m_labels.second->setText(helper2);
            m_timers[1]->start(5000);
            m_timers[3]->start(5000);
        }
        else m_messages[1]->show();
    }
}

//music volume controller show or hide
void MainWindow::media_slot()
{
    if (m_md_ctrl.second->isHidden())
        m_md_ctrl.second->show();
    else m_md_ctrl.second->hide();
}




