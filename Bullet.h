#ifndef BULLET_H
#define BULLET_H
#include"Enemy.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class QTimer;

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = nullptr);

public slots:
    void move();
    void startSizeIncrease();
    void decreaseSize();

private:
    QTimer *sizeIncreaseTimer;
    int bulletSize;
    static bool shouldIncreaseSize;
signals:
    void hitEnemy(Enemy* enemy);

};


#endif // BULLET_H
