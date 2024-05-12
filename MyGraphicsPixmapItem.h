#ifndef MYGRAPHICSPIXMAPITEM_H
#define MYGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include "building.h"
#include"Bullet.h"
class MyGraphicsPixmapItem : public QGraphicsPixmapItem {
public:
    MyGraphicsPixmapItem(Building *cannon, QGraphicsItem *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void shootBullet();
    void setPos(qreal x, qreal y);
    void setRotation(qreal angle);
private:
    bool canShoot = true;
    Building *cannon;
};

#endif // MYGRAPHICSPIXMAPITEM_H


