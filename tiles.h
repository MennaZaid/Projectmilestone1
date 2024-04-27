#ifndef TILES_H
#define TILES_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMap>
#include<QPixmap>
class Tiles
{

public:
    Tiles();
    QMap<QString, QPixmap> map1tiles;
    QPixmap map2land;
    QPixmap map2Castle;
    QPixmap map2Fence;
    QPixmap map2Canon;
    QPixmap map3land;
    QPixmap map3Castle;
    QPixmap map3Fence;
    QPixmap map3Canon;
};

#endif // TILES_H
