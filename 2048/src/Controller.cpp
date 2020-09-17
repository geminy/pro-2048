#include "Controller.h"
#include "Config.h"

#include <QCoreApplication>

#include <ctime>

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_preIndex(-1)
    , m_nextIndex(-1)
    , m_addedFlag(false)
    , m_movedFlag(false)
    , m_score(0)
    , m_bestScore(0)
    , m_step(0)
    , m_totalStep(0)
{
    connect(this, SIGNAL(backTrigger()), this, SLOT(onBackTriggered()));
    srand(time(0));
}

Controller::~Controller()
{
    disconnect(this, SIGNAL(backTrigger()), this, SLOT(onBackTriggered()));
}

/* get score */
int Controller::score() const
{
    return m_score;
}

/* get best score */
int Controller::bestScore() const
{
    return m_bestScore;
}

/* get step */
int Controller::step() const
{
    return m_step;
}

/* get total step */
int Controller::totalStep() const
{
    return m_totalStep;
}

/* initialize to start */
void Controller::start()
{
    initNum();
}

/* response for user */
void Controller::move(MOVE_DIRECTION direction)
{
    /* 0. game over ? */
    if (isOver()) {
        emit gameOver();
        return;
    }

    /* 1. add */
    added(direction);

    /* 2. move */
    moved(direction);

    /* 3. fresh */
    freshed(m_addedFlag || m_movedFlag);

    /* 4. update best score */
    if(m_bestScore < m_score) {
        m_bestScore = m_score;
    }
}

/* get grid background color, depends on specific number */
QColor Controller::color(int index) const
{
    int number = m_number[index];
    QColor color;
    switch(number) {
    case 0: color = QColor(255, 255, 255); break; // white
    case 2: color = QColor(245, 222, 179); break; // wheat
    case 4: color = QColor(238, 130, 238); break; // violet
    case 8: color = QColor(0, 255, 127); break; // springgreen
    case 16: color = QColor(255, 192, 203); break; // pink
    case 32: color = QColor(255, 165, 0); break; // orange
    case 64: color = QColor(173, 255, 47); break; // greenyellow
    case 128: color = QColor(255, 99, 71); break; // tomato
    case 256: color = QColor(154, 205, 50); break; // yellowgreen
    case 512: color = QColor(255, 215, 0); break; // gold
    case 1024: color = QColor(0, 255, 255); break; // cyan
    case 2048: color = QColor(0, 255, 0); break; // green
    case 4096: color = QColor(255, 255, 0); break; // yellow
    case 8192: color = QColor(255, 0, 0); break; // red
    default: color = QColor(0, 0, 0); break; // black
    }
    return color;
}

/* get grid number color, depends on specific number */
QColor Controller::numColor(int index) const
{
    int number = m_number[index];
    if(8192 > number) {
        return QColor(0, 0, 0); // black
    }
    else {
        return QColor(255, 255, 255); // white
    }
}

/* back to last step */
void Controller::onBackTriggered()
{
    if(0 < m_step) {
        m_number = m_state[m_step - 1];
        m_state.pop_back();
        m_step -= 1;
    }
}

/* show grid number of the rignt index */
int Controller::show(int index)
{
    return m_number[index];
}

/* quit */
void Controller::quitGame()
{
    QCoreApplication::quit();
}

/* initialize grid number with two 2 */
void Controller::initNum()
{
    /* score/step */
    m_score = 0;
    m_step = 0;
    m_totalStep = 0;

    /* grid number */
    m_number.clear();
    m_number = GridNumber(16, 0);
    int firstNumIndex = rand() % 16;
    int secondNumIndex = rand() % 16;
    while(firstNumIndex == secondNumIndex) {
        secondNumIndex = rand() % 16;
    }
    m_number[firstNumIndex] = 2;
    m_number[secondNumIndex] = 2;

    /* grid state */
    m_state.clear();
    m_state.push_back(m_number);
}

/* add the same number */
void Controller::added(MOVE_DIRECTION direction)
{
    /* move down */
    if(MOVE_DOWN == direction) {
        m_addedFlag = false;
        for(int c = 0; c < PANEL_GRID_COLUMN; c++) {
            m_preIndex = c;
            m_nextIndex = m_preIndex + 4;
            while(m_nextIndex <= c + 12) {
                if(0 == m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex + 4;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex += 4;
                    continue;
                }
                if(m_number[m_preIndex] != m_number[m_nextIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex + 4;
                }
                else {
                    m_number[m_preIndex] = 0;
                    m_number[m_nextIndex] += m_number[m_nextIndex];
                    m_score += m_number[m_nextIndex];
                    m_preIndex = m_nextIndex + 4;
                    m_nextIndex = m_preIndex + 4;
                    m_addedFlag = true;
                }
            }
        }
    }

    /* move up */
    if(MOVE_UP == direction) {
        m_addedFlag = false;
        for(int c = 0; c < PANEL_GRID_COLUMN; c++) {
            m_preIndex = c + 12;
            m_nextIndex = m_preIndex - 4;
            while(m_nextIndex >= c) {
                if(0 == m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex - 4;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex -= 4;
                    continue;
                }
                if(m_number[m_preIndex] != m_number[m_nextIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex - 4;
                }
                else {
                    m_number[m_preIndex] = 0;
                    m_number[m_nextIndex] += m_number[m_nextIndex];
                    m_score += m_number[m_nextIndex];
                    m_preIndex = m_nextIndex - 4;
                    m_nextIndex = m_preIndex - 4;
                    m_addedFlag = true;
                }
            }
        }
    }

    /* move right */
    if(MOVE_RIGHT == direction) {
        m_addedFlag = false;
        for(int r = 0; r < PANEL_GRID_ROW; r++) {
            m_preIndex = r * 4;
            m_nextIndex = m_preIndex + 1;
            while(m_nextIndex <= r * 4 + 3) {
                if(0 == m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex + 1;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex += 1;
                    continue;
                }
                if(m_number[m_preIndex] != m_number[m_nextIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex + 1;
                }
                else {
                    m_number[m_preIndex] = 0;
                    m_number[m_nextIndex] += m_number[m_nextIndex];
                    m_score += m_number[m_nextIndex];
                    m_preIndex = m_nextIndex + 1;
                    m_nextIndex = m_preIndex + 1;
                    m_addedFlag = true;
                }
            }
        }
    }

    /* move left */
    if(MOVE_LEFT == direction) {
        m_addedFlag = false;
        for(int r = 0; r < PANEL_GRID_ROW; r++) {
            m_preIndex = r * 4 + 3;
            m_nextIndex = m_preIndex - 1;
            while(m_nextIndex >= r * 4) {
                if(0 == m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex - 1;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex -= 1;
                    continue;
                }
                if(m_number[m_preIndex] != m_number[m_nextIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex - 1;
                }
                else {
                    m_number[m_preIndex] = 0;
                    m_number[m_nextIndex] += m_number[m_nextIndex];
                    m_score += m_number[m_nextIndex];
                    m_preIndex = m_nextIndex - 1;
                    m_nextIndex = m_preIndex - 1;
                    m_addedFlag = true;
                }
            }
        }
    }
}

/* move grid number position */
void Controller::moved(MOVE_DIRECTION direction)
{
    /*move down */
    if(MOVE_DOWN == direction) {
        m_movedFlag = false;
        for(int c = 0; c < PANEL_GRID_COLUMN; c++) {
            m_preIndex = c + 12;
            m_nextIndex = m_preIndex - 4;
            while(m_nextIndex >= c) {
                if(0 != m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex - 4;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex -= 4;
                }
                else {
                    m_number[m_preIndex] = m_number[m_nextIndex];
                    m_number[m_nextIndex] = 0;
                    m_preIndex = m_preIndex - 4;
                    m_nextIndex = m_nextIndex - 4;
                    m_movedFlag = true;
                }
            }
        }
    }

    /* move up */
    if(MOVE_UP == direction) {
        m_movedFlag = false;
        for(int c = 0; c < PANEL_GRID_COLUMN; c++) {
            m_preIndex = c;
            m_nextIndex = m_preIndex + 4;
            while(m_nextIndex <= c + 12) {
                if(0 != m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex + 4;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex += 4;
                }
                else {
                    m_number[m_preIndex] = m_number[m_nextIndex];
                    m_number[m_nextIndex] = 0;
                    m_preIndex = m_preIndex + 4;
                    m_nextIndex = m_nextIndex + 4;
                    m_movedFlag = true;
                }
            }
        }
    }

    /* move right */
    if(MOVE_RIGHT == direction) {
        m_movedFlag = false;
        for(int r = 0; r < PANEL_GRID_ROW; r++) {
            m_preIndex = r * 4 + 3;
            m_nextIndex = m_preIndex - 1;
            while(m_nextIndex >= r * 4) {
                if(0 != m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex - 1;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex -= 1;
                }
                else {
                    m_number[m_preIndex] = m_number[m_nextIndex];
                    m_number[m_nextIndex] = 0;
                    m_preIndex = m_preIndex - 1;
                    m_nextIndex = m_nextIndex - 1;
                    m_movedFlag = true;
                }
            }
        }
    }

    /* move left */
    if(MOVE_LEFT == direction) {
        m_movedFlag = false;
        for(int r = 0; r < PANEL_GRID_ROW; r++) {
            m_preIndex = r * 4;
            m_nextIndex = m_preIndex + 1;
            while(m_nextIndex <= r * 4 + 3) {
                if(0 != m_number[m_preIndex]) {
                    m_preIndex = m_nextIndex;
                    m_nextIndex = m_preIndex + 1;
                    continue;
                }
                if(0 == m_number[m_nextIndex]) {
                    m_nextIndex += 1;
                }
                else {
                    m_number[m_preIndex] = m_number[m_nextIndex];
                    m_number[m_nextIndex] = 0;
                    m_preIndex = m_preIndex + 1;
                    m_nextIndex = m_nextIndex + 1;
                    m_movedFlag = true;
                }
            }
        }
    }
}

/* fresh grid number if added or moved */
void Controller::freshed(bool fresh)
{
    if(fresh) {
        /* step */
        m_step += 1;
        m_totalStep = m_step;

        /* store unused grid index */
        m_index.clear();
        for(size_t s = 0; s < m_number.size(); s++) {
            if(!m_number[s]) {
                m_index.push_back(s);
            }
        }

        /* generate another 2 in random position */
        int randIndex = rand() % m_index.size();
        m_number[m_index[randIndex]] = 2;

        /* update state */
        m_state.push_back(m_number);
    }
}

/* game state checking */
bool Controller::isOver()
{
    // null check
    for (size_t i = 0; i < m_number.size(); i++) {
        if (0 == m_number[i]) {
            return false;
        }
    }
    int preIndex = 0;
    int nextIndex = 0;

    // row check
    for (int row = 0; row < 4 ; row++) {
        preIndex = row * 4;
        for (int col = 1; col < 4; col++) {
            nextIndex = preIndex + 1;
            if (m_number[preIndex] == m_number[nextIndex]) {
                return false;
            }
            preIndex = nextIndex;
        }
    }

    // column check
    for (int col = 0; col < 4; col++) {
        preIndex = col;
        for (int row = 1; row < 3; row++) {
            nextIndex = preIndex + 4;
            if (m_number[preIndex] == m_number[nextIndex]) {
                return false;
            }
            preIndex = nextIndex;
        }
    }

    // game over
    return true;
}
