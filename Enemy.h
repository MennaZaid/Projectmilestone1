#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPoint>
#include <QTimer>
#include "node.h"

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    QTimer* currentTimer;
    QList<Node*> currentPath;
    int currentNodeIndex = 0;
public:
    Enemy(QPoint, QPixmap);
public slots:
    void processPath(QList<Node*>);
    void moveOnPath();
};



#endif // ENEMY_H
