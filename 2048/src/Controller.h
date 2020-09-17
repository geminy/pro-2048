#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QColor>

/*
 * @class Controller
 */
class Controller : public QObject
{
    Q_OBJECT

    Q_ENUMS(MOVE_DIRECTION)

    Q_PROPERTY(int score READ score)
    Q_PROPERTY(int bestScore READ bestScore)
    Q_PROPERTY(int step READ step)
    Q_PROPERTY(int totalStep READ totalStep)

public:
    /*
     * @enum MOVE_DIRECTION
     */
    enum MOVE_DIRECTION
    {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_INVALID
    };

public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    int score() const;
    int bestScore() const;
    int step() const;
    int totalStep() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void move(MOVE_DIRECTION direction);
    Q_INVOKABLE QColor color(int index) const;
    Q_INVOKABLE QColor numColor(int index) const;

signals:
    void backTrigger();
    void gameOver();

// cannot be private for being called from qml
protected slots:
    void onBackTriggered();
    Q_INVOKABLE int show(int index);
    Q_INVOKABLE void quitGame();

private:
    void initNum();
    void added(MOVE_DIRECTION direction);
    void moved(MOVE_DIRECTION direction);
    void freshed(bool fresh);
    bool isOver();

private:
    typedef std::vector<int> GridNumber;
    typedef std::vector<GridNumber> StateCache;

    GridNumber m_number;
    GridNumber m_index;
    StateCache m_state;

    int m_preIndex;
    int m_nextIndex;
    bool m_addedFlag;
    bool m_movedFlag;

    int m_score;
    int m_bestScore;
    int m_step;
    int m_totalStep;
};

#endif // CONTROLLER_H
