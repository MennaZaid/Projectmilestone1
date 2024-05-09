
#ifndef MAP_H
#define MAP_H

#include <QHash>
#include "enemy.h"
#include <QObject>
#include <QGraphicsScene>
#include "tiles.h"
#include "mainwindow.h"
#include "building.h"
#include "node.h"
//s
#include<QTimer>
#include"Timer.h"
//e


class MainWindow;

class Map : public QObject
{
    Q_OBJECT

public:
    Map(QWidget *parent);
    QGraphicsScene* scene;
private:
    void setupScene();
    void loadmapfromfile(const QString &file);
    Tiles tilemap1;
    MainWindow* mainWindow;
    QHash<QPoint, Node*> grid;
    QHash<QPoint, Node*> gridWithoutObstacles;

    Building* castle;

    QList<Enemy*> enemies;
    //s
    Timer* m_timer;
    //e
public slots:
    void giveNewPath();
};

#endif // MAP_H
