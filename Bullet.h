#ifndef BULLET_H
#define BULLET_H

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
    static bool shouldIncreaseSize; // Static boolean variable to track if bullet size should be increased
};

#endif // BULLET_H
