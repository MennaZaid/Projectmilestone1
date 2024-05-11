
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
#include"HealthMarker.h"
//e


class MainWindow;
enum Difficulty
{
    One,
    Two,
    Three,
    Four,
    Five
};

class Map : public QObject
{
    Q_OBJECT

public:
    Map(QWidget *parent);
    QGraphicsScene* scene;
    void setupScene();
    void loadmapfromfile(const QString &file);
    void startThenewLevel();
    void resetGame();
    void startGameTimer();

    HealthMarker* healthmarker;

    //added
    QTimer* healthMarkerTimer;
protected:
    QTimer* timer;
    int remainingTime;
    int newRemainingTime;
    Difficulty currentDifficulty;
    Tiles tilemap1;
    MainWindow* mainWindow;
    QHash<QPoint, Node*> grid;
    Building* castle;
    Timer* m_timer;

public slots:
void spawnHealthMarker();
    void AddEnemy();
};

#endif // MAP_H


