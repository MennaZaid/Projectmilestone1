// Map1.h
#ifndef MAP1_H
#define MAP1_H

#include "map.h"
#include"HealthMarker.h"
#include"tiles.h"
class Map1 : public Map
{
    Q_OBJECT
public:
    explicit Map1(QWidget *parent = nullptr);

    HealthMarker* healthmarker;

    //added
    QTimer* healthMarkerTimer;

public slots:
    void spawnHealthMarker();




private:


};

#endif // MAP1_H
