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
#include "citizen.h"
//s
#include<QTimer>
#include"Timer.h"
#include"HealthMarker.h"
#include"MyGraphicsPixmapItem.h"
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
    ~Map();
    QGraphicsScene* scene;
    void setupScene();
    void loadmapfromfile(const QString &file);
    void startThenewLevel();
    void resetGame(int newRemainingTime);
    //void startGameTimer();

public slots:
    void OnBuildingDamaged();
    void AddEnemy();
    void ResetCitizen();
    void RemoveBuildingFromList();
    void spawnHealthMarker();
    //void createCitizens(int numCitizens);

    //added
private:
    QTimer* healthMarkerTimer;
    QTimer* timer;
    int remainingTime;
    int newRemainingTime;
    Difficulty currentDifficulty;
    Tiles tilemap1;
    MainWindow* mainWindow;
    QHash<QPoint, Node*> grid;
    Building* castle;
    Timer* m_timer;
    QList<Building*> buildings;
    QList<Building*> buildingsBeingFixed;
    QList<Citizen*> citizens;
    QTimer* enemySpawnTimer;

};

#endif // MAP_H

