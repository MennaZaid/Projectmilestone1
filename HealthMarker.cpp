#include "HealthMarker.h"
#include <QList>
#include "Bullet.h"
#include<QGraphicsScene>

HealthMarker::HealthMarker(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/photos/healthmarker.png").scaled(100, 100));
   // scene()->addItem(this);
}

//in bullet
void HealthMarker::handleCollision() {
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        if (typeid(*item) == typeid(Bullet)) {
            emit markerHit();
            if (scene())
                scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
