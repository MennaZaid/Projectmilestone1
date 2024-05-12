#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "HealthMarker.h"

bool Bullet::shouldIncreaseSize = false;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    bulletSize = 1;
    setPixmap(QPixmap(":/map1/bullet.png").scaled(25 * bulletSize, 25 * bulletSize));
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);

    sizeIncreaseTimer = new QTimer(this);
    connect(sizeIncreaseTimer, SIGNAL(timeout()), this, SLOT(decreaseSize()));
}

void Bullet::move(){
    if(shouldIncreaseSize){
        bulletSize = 2;
        setPixmap(QPixmap(":/map1/bullet.png").scaled(25 * bulletSize, 25 * bulletSize));
    } else {
        bulletSize = 1;
        setPixmap(QPixmap(":/map1/bullet.png").scaled(25 * bulletSize, 25 * bulletSize));
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){

            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            emit hitEnemy(static_cast<Enemy*>(colliding_items[i]));
            delete colliding_items[i];
            delete this;

            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(HealthMarker)){
            shouldIncreaseSize = true;
            startSizeIncrease();
            scene()->removeItem(colliding_items[i]);
        }
    }

    qreal angleDegrees = rotation() - 90;
    qreal angleRadians = qDegreesToRadians(angleDegrees);
    qreal bulletVelocityX = qCos(angleRadians);
    qreal bulletVelocityY =  qSin(angleRadians);

    QPointF direction(bulletVelocityX, bulletVelocityY);
    QPointF newPos = pos() + direction;
    setPos(newPos.x(), newPos.y());

    if (pos().y() < 0 || pos().y() > scene()->sceneRect().height() || pos().x() < 0 || pos().x() > scene()->sceneRect().width())
    {
        scene()->removeItem(this);
        delete this;
    }
}

void Bullet::startSizeIncrease(){
    sizeIncreaseTimer->start(30000);
}

void Bullet::decreaseSize(){
    sizeIncreaseTimer->stop();

    bulletSize = 1;
    setPixmap(QPixmap(":/map1/bullet.png").scaled(25 * bulletSize, 25 * bulletSize));

    shouldIncreaseSize = false;
}
