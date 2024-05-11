#include "HealthMarker.h"
#include <QList>
#include "Bullet.h" // Include the Bullet class header file
#include<QGraphicsScene>
#include"Map1.h"

HealthMarker::HealthMarker(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("C:/Users/fatim/OneDrive/Documents/Projectmilestone1/healthmarker.png").scaled(100, 100)); // Set pixmap for the health marker
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
