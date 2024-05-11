#include "building.h"
#include <QGraphicsScene>

Building::Building(QPoint coords, QPixmap map) : QObject(nullptr) , QGraphicsPixmapItem(nullptr)
{
    setPixmap(map);
    this->coords = coords;
    bar = new HealthBar(100, 10, pos());
}

void Building::TakeDamage()
{
    this->currentHitpoints--;
    this->bar->setValue(currentHitpoints);
    if (currentHitpoints < 500)
    {
        bar->show();
    }
    else
    {
        bar->hide();
    }
}


