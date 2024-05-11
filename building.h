#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QBrush>



class Building : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int currentHitpoints = 500;
    int maximumHitpoints = 500;
public:

    int CurrentHitPoints()
    {
        return currentHitpoints;
    }
    QPoint coords;

    explicit Building(QPoint, QPixmap);

    void TakeDamage();
    void Heal();

signals:
    void BuildingDamaged();
    void FullyHealed();
};

#endif // BUILDING_H
