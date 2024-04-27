#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QPoint>
#include <QGraphicsPixmapItem>

class Building : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int currentHitpoints = 5;
    int maximumHitpoints = 5;
    bool isDestroyed = false; //For later usage;
    bool isCastle;
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
