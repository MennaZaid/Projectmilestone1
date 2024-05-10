
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

    Building* castle;

    QList<Enemy*> enemies;
<<<<<<< HEAD

=======
    //s
    Timer* m_timer;
    //e
>>>>>>> 66349ea28d5b73fccde6d822cebd221bac304d99
public slots:

    void AddEnemy();
};

#endif // MAP_H
