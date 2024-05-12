// Map2.cpp
#include "map2.h"

Map2::Map2(QWidget *parent) : Map(nullptr)
{
    QPixmap snowman(":/Ice/SnowmanLight.png");
    // Define the size of the array


    // Create an array of QPixmap objects
    QPixmap PixmapArray2[5];

    // Initialize QPixmap objects in the array using a loop
    PixmapArray2[1] = QPixmap(":/Ice/IceCastle.png");
    PixmapArray2[3] = QPixmap(":/Ice/wallvertical.png");
    PixmapArray2[4] = QPixmap(":/Ice/Wall.png");
    PixmapArray2[0] = QPixmap(":/Ice/GameBG.png");
    PixmapArray2[2] = QPixmap(":/Ice/flamethrower.png");
   setupScene(PixmapArray2);
    AddEnemy(snowman);
}

