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
private:
    bool canShoot = true;
    Building *cannon;
};

#endif // MYGRAPHICSPIXMAPITEM_H


