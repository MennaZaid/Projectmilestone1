#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QPoint>
#include <QGraphicsPixmapItem>

class Building : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int currentHitpoints = 500;
    int maximumHitpoints = 500;
    bool isDestroyed = false; //For later usage;
public:
    int CurrentHitPoints()
    {
        return currentHitpoints;
    }
    QPoint coords;

    explicit Building(QPoint, QPixmap);

    void TakeDamage();
};

#endif // BUILDING_H
