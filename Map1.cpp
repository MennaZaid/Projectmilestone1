// Map1.cpp
#include "map1.h"

Map1::Map1(QWidget *parent) : Map(nullptr)
{
    QPixmap enemyman(":/photos/enemy.png");



    QPixmap PixmapArray1[5];
    PixmapArray1[1] = QPixmap(":/map1/Castle.png");
    PixmapArray1[3] = QPixmap(":/map1/fence_00.png");
    PixmapArray1[4] = QPixmap(":/map1/fence_01.png");
    PixmapArray1[0] = QPixmap(":/map1/green land.jpg");
    PixmapArray1[2] = QPixmap(":/map1/cannon.jpeg");
    setupScene( PixmapArray1);
    AddEnemy( enemyman);
}

