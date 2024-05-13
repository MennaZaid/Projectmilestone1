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
    bool isCastlePath = false;

public:
    Enemy(QPoint, QPixmap);
    void DamageBuilding();
public slots:
    void processPath(QList<Node*>);
    void moveOnPath();
signals:
    void needNewPath();
};




#endif // ENEMY_H
