#include "building.h"
#include <QGraphicsScene>

Building::Building(QPoint coords, QPixmap map) : QObject(nullptr) , QGraphicsPixmapItem(nullptr)
{
    setPixmap(map);
    this->coords = coords;
}

void Building::TakeDamage()
{
    this->currentHitpoints--;
    emit BuildingDamaged();
 }

void Building::Heal()
{
    this->currentHitpoints++;
    if (currentHitpoints >= maximumHitpoints)
    {
        qDebug() << "fully healed";
        emit FullyHealed();
    }
}


