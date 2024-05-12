#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "HealthMarker.h" // Include HealthMarker header

// Define a static boolean variable to track whether bullets should increase in size
bool Bullet::shouldIncreaseSize = false;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // Set initial bullet size and draw graphics
    bulletSize = 1; // Initial bullet size
    setPixmap(QPixmap(":/map1/cannon_ball.jpeg").scaled(25 * bulletSize, 25 * bulletSize)); // Set initial pixmap size based on bulletSize
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);

    // Initialize size increase timer
    sizeIncreaseTimer = new QTimer(this);
    connect(sizeIncreaseTimer, SIGNAL(timeout()), this, SLOT(decreaseSize()));
}

void Bullet::move(){
    // Check if size increase timer is active
    if(shouldIncreaseSize){
        // Double the bullet size
        bulletSize = 2;
        setPixmap(QPixmap(":/map1/cannon_ball.jpeg").scaled(25 * bulletSize, 25 * bulletSize));
    } else {
        // Reset the bullet size to normal
        bulletSize = 1;
        setPixmap(QPixmap(":/map1/cannon_ball.jpeg").scaled(25 * bulletSize, 25 * bulletSize));
    }

    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; i++){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){

            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            emit hitEnemy(static_cast<Enemy*>(colliding_items[i]));
            // delete them from the heap to save memory
            delete colliding_items[i];
            delete this;

            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(HealthMarker)){
            // Handle collision with HealthMarker here
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

    // if the bullet is off the screen, destroy it
    if (pos().y() < 0 || pos().y() > scene()->sceneRect().height() || pos().x() < 0 || pos().x() > scene()->sceneRect().width())
    {
        scene()->removeItem(this);
        delete this;
    }
}

void Bullet::startSizeIncrease(){
    // Start the size increase timer for 30 seconds
    sizeIncreaseTimer->start(30000); // 30 seconds
}

void Bullet::decreaseSize(){
    // Stop the size increase timer
    sizeIncreaseTimer->stop();

    // Reset the bullet size to normal
    bulletSize = 1;
    setPixmap(QPixmap(":/map1/cannon_ball.jpeg").scaled(25 * bulletSize, 25 * bulletSize));

    // Reset the flag to false
    shouldIncreaseSize = false;
}
