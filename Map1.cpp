// Map1.cpp
#include "map1.h"
#include<QTimer>

void Map1::spawnHealthMarker() {
    // Ensure scene is properly initialized and accessible
    qDebug() << "working";
    if (!scene) return;

    // Generate random coordinates within the scene bounds
    int x = rand() % static_cast<int>(scene->width());
    int y = rand() % static_cast<int>(scene->height());

    // Create and add health marker to the scene
    HealthMarker *healthMarker = new HealthMarker();
    healthMarker->setPos(x, y);
    scene->addItem(healthMarker);
}

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

    //healthmarker= new HealthMarker;
    //healthmarker->setPos(500,500);

    //scene->addItem(healthmarker);

    //added
    srand(static_cast<uint>(QTime::currentTime().msec()));

    // Create a timer for spawning health markers
    healthMarkerTimer = new QTimer(this);
    connect(healthMarkerTimer, SIGNAL(timeout()), this, SLOT(spawnHealthMarker()));
    healthMarkerTimer->start(3000);

}

// void Map1::spawnHealthMarker() {
//     // Generate random coordinates within the scene bounds
//     int x = rand() % static_cast<int>(scene->width());
//     int y = rand() % static_cast<int>(scene->height());

//     HealthMarker *healthMarker = new HealthMarker();
//     healthMarker->setPos(x, y);
//     scene->addItem(healthMarker);
// }

