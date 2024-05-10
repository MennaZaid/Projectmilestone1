#include "building.h"

Building::Building(QPoint coords, QPixmap map) : QObject(nullptr)
{
    setPixmap(map);
    this->coords = coords;
}

void Building::TakeDamage()
{
    this->currentHitpoints--;
}


