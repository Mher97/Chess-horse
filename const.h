#ifndef CONST
#define CONST

#endif // CONST

#include <array>
#include <QtCore>
using namespace std;

/*constants  are designated for widgets and graphic items geometry,
 *  source paths and etc*/

const int BOARDSIZE = 8;
const int WHITE = 0;
const int BLACK = 1;
const int GREEN = 1;
const int BLUE = 2;
const int NONMARKED = 0;
const int INF = 100000;

const array<qreal, 4> for_board{0.3143, 0.0104166, 0.05116959, 0.091145833};

const array<pair<qreal,qreal>, 2> for_items{make_pair(0.804, 0.065), make_pair(0.804, 0.195)};

const array<QString, 8> for_paths{"/resources", "/horse1.png", "/flag.png", "/background2.jpg",
                                  "/sound.wav", "/USSR.wav", "/sound.png", "/horse4.png"};

const array<qreal,10> for_buttons={0.1, 0.20, 0.30, 0.40, 0.14, 0.24, 0.34, 0.05, 0.15, 0.08};

const array<QString,7> for_buttons_text={"Level1", "Level2", "About", "Exit", "New", "Run", "Back"};

const array<pair<qreal, qreal>, 2> for_texts_pos{make_pair(0.28, 0.035), make_pair(0.33, 0.75)};

const array<QString, 16> for_texts{"8", "7", "6", "5", "4", "3", "2", "1", "a", "b" , "c", "d", "e", "f", "g", "h"};

const array<pair<qreal,qreal>,4> for_media{make_pair(0.96,0.88), make_pair(0.03,0.03), make_pair(0.95,0.78), make_pair(0.045,0.1)};

const array<int,12> for_message{80, 2, 15, 25, 30, 70, 40, 30, 5, 5, 90, 60};

const array<int,12> for_about{30, 15, 50, 60, 90, 5, 8, 13, 10, 10, 77,70};

const array<int,8> for_labels{20, 84, 60, 7, 92};



