#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"


Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // draw graphics
    setPixmap(QPixmap(":/map1/332-3329390_transparent-cannonball-png-cannon-ball-2d-png-png.png").scaled(25, 25));
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);
}

void Bullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; i++){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){

            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            // delete them from the heap to save memory
            delete colliding_items[i];
            delete this;

            return;
        }
    }

    qreal angleDegrees = rotation() - 90;
    qreal angleRadians = qDegreesToRadians(angleDegrees);
    qreal bulletVelocityX = qCos(angleRadians);
    qreal bulletVelocityY =  qSin(angleRadians);

    QPointF direction(bulletVelocityX, bulletVelocityY);
    QPointF newPos = pos() + direction;
    setPos(newPos.x(), newPos.y());

    // if the bullet is off the screen, destroy it
    if (pos().y() < 0 || pos().y() > scene()->sceneRect().height() || pos().x() < 0 || pos().x() > scene()->sceneRect().width())
    {
        scene()->removeItem(this);
        delete this;
    }
}
