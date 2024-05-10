#include "mygraphicspixmapitem.h"
#include <QKeyEvent>
#include<QGraphicsScene>
#include<QDebug>
MyGraphicsPixmapItem::MyGraphicsPixmapItem(Building *cannon, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), cannon(cannon) {
    setFlags(QGraphicsItem::ItemIsFocusable);
    setFocus();
    cannon->setTransformOriginPoint(cannon->boundingRect().width() / 2, cannon->boundingRect().height() / 2);
}

void MyGraphicsPixmapItem::keyPressEvent(QKeyEvent *event) {
    if (cannon) {
        qreal rotationStep = 5.0;
        switch (event->key()) {
        case Qt::Key_Left:
            cannon->setRotation(cannon->rotation() - rotationStep);
            break;
        case Qt::Key_Right:
            cannon->setRotation(cannon->rotation() + rotationStep);
            break;
        case Qt::Key_Space:
            // Shoot bullets
            if (canShoot) shootBullet();
            break;
        default:
            QGraphicsPixmapItem::keyPressEvent(event);
        }
    } else {
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}
void MyGraphicsPixmapItem::shootBullet()
{
    if (scene() && cannon) {

        canShoot = false;
        Bullet *bullet = new Bullet();

        qreal angleDegrees = cannon->rotation(); // cannon is a QGraphicsItem with rotation
        qreal angleRadians = qDegreesToRadians(angleDegrees);
        qreal bulletVelocityX = qCos(angleRadians);
        qreal bulletVelocityY =  qSin(angleRadians);

        // Calculate the position of the bullet relative to the cannon

        QPointF bulletPos = cannon->pos() + QPointF(cannon->boundingRect().width() / 2, cannon->boundingRect().height() / 2) + QPointF(cannon->boundingRect().width() / 2 * bulletVelocityX, cannon->boundingRect().height() / 2 * bulletVelocityY);
        bullet->setTransformOriginPoint(bullet->boundingRect().width() / 2, bullet->boundingRect().height() / 2);
        bullet->setPos(bulletPos);
        bullet->setRotation(angleDegrees + 90);
        scene()->addItem(bullet);

        QEventLoop loop;
        QTimer::singleShot(500, &loop, &QEventLoop::quit);
        loop.exec();
        canShoot = true;
    }
}
