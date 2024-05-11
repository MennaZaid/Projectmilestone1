
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
#include"tiles.h"
#include<array>
#include<QPixmap>
//e


class MainWindow;

class Map : public QObject
{
    Q_OBJECT

public:
    Map(QWidget *parent);
    QGraphicsScene* scene;
protected:
    void setupScene(QPixmap pixmapArray[]);
    void loadmapfromfile(const QString &file , QPixmap pixmapArray[]);
    MainWindow* mainWindow;
    QHash<QPoint, Node*> grid;
    Building* castle;
    Timer* m_timer;

    QPixmap pixmapArray[5];

public slots:

    void AddEnemy(QPixmap Pixmap);
};

#endif // MAP_H
