#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QMediaPlayer>
#include<QAudioOutput>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    QMediaPlayer* war;
    QMediaPlayer* intromusic;
    QMediaPlayer* click;
    QMediaPlayer* backgroundMusic;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setSoundVolume(float);
    void setMusicVolume(float);

private slots:

    void on_pushButtonStart_clicked();
    void on_pushButtonSettings_clicked();

private:
    Ui::MainWindow* ui;

};
#endif // MAINWINDOW_H

/*#include "map1.h"
#include "tiles.h"
#include "node.h"
#include "pathfinder.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include "Player.h"

Map1::Map1(QWidget *parent)
    : QObject(nullptr)
{
    scene = new QGraphicsScene();
    this->mainWindow = static_cast<MainWindow*>(parent);
    setupScene();
}


void Map1::setupScene()
{
    loadmapfromfile(":/text/map1.txt");
    QGraphicsView* view = new QGraphicsView(scene);
    view->setFixedSize(scene->width(), scene->height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
}


void Map1::loadmapfromfile(const QString &filename)
{

    QMessageBox::information(nullptr, "Test message 1", "1");

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this->mainWindow, "Error", "File is not open");
        return;
    }
    QTextStream in(&file);

    int posX = 0; // Initial position X
    int posY = 0; // Initial position Y
    int pixelWidth = 100; // Width of each pixel
    int pixelHeight = 100; // Height of each pixel

    QMessageBox::information(nullptr, "Test message 2", "2");

    int i = 0;
    QList<QString> lines;

    while (!in.atEnd()) {
        Tiles tilemap1;
        lines.append(in.readLine());
    }

    QMessageBox::information(nullptr, "Test message 2", "2");


    for (int i = 0; i < lines.count(); i++)
    {
        QString line = lines[i];

        for (int j = 0;  j < line.length() / 2; j++)
        {
            QGraphicsPixmapItem *image1 = new QGraphicsPixmapItem(tilemap1.map1land.scaled(pixelWidth, pixelHeight));
            image1->setPos(posX, posY);
            scene->addItem(image1);
            posX += pixelWidth;
        }

        posX = 0;

        for (int j = 0; j < line.length() / 2; j++)
        {
            Node* node = new Node(QPoint(i, j));
            Node* nodeFake = new Node(QPoint(i, j));
            nodeFake->isWalkable = true;
            QChar character = line[j * 2];
            if (character == '0') {
                node->isWalkable = true;
            } else if (character == '1') {
                node->isWalkable = false;
                castle = new Building(QPoint(i, j), tilemap1.map1Castle.scaled(pixelWidth, pixelHeight));
                castle->setPos(posX, posY);
                scene->addItem(castle);
            } else if (character == '2') {
                node->isWalkable = false;
                Building* cannon = new Building(QPoint(i,j), tilemap1.map1Canon.scaled(pixelWidth, pixelHeight));
                cannon->setPos(posX, posY);
                scene->addItem(cannon);
                otherBuildings.push_back(cannon);
            } else if (character == '3') {
                node->isWalkable = false;
                Building* fence = new Building(QPoint(i,j), tilemap1.map1fence.scaled(pixelWidth, pixelHeight));
                fence->setPos(posX, posY);
                scene->addItem(fence);
                /*QChar charLeft = (j != 0) ? line[j - 1] : 'N';
                QChar charRight = (j != (line.length() - 1)) ? line[j + 1] : 'N';
                QChar charUp = (i != 0) ? lines[i - 1][j] : 'N';
                QChar charDown = (i != (lines.count() - 1)) ? lines[i + 1][j] : 'N';

                // Check neighboring nodes if they are fences to determine the correct fence picture
                QString corner = "3";
                if (charLeft == '3' && charUp == '3' && charRight == '3' && charDown == '3') {
                    corner = "center";
                } else if (charLeft == '3' && charUp == '3') {
                    corner = "topLeft";
                } else if (charRight == '3' && charUp == '3') {
                    corner = "topRight";
                } else if (charLeft == '3' && charDown == '3') {
                    corner = "bottomLeft";
                } else if (charRight == '3' && charDown == '3') {
                    corner = "bottomRight";
                } else if (charLeft == '3' && charRight == '3') {
                    corner = "horozintal";
                } else {
                    corner = "vertical";
                }


                QGraphicsPixmapItem* fence = new QGraphicsPixmapItem(tilemap1.fences1[corner].scaled(pixelWidth, pixelHeight));

                fence->setPos(posX, posY);
                scene->addItem(fence);* // All of this is to needs different fence pictures to be found;

            }
            grid[node->coords] = node;
            gridWithoutObstacles[nodeFake->coords] = nodeFake;
            posX += pixelWidth;
        }
        posX = 0;
        posY += pixelHeight;
    }

    QMessageBox::information(nullptr, "Test message 2", "2");

    file.close();

    Enemy* enemy1 = new Enemy(QPoint(0,0), QPixmap(":/photos/enemy.png").scaled(50,50));
    Enemy* enemy2 = new Enemy(QPoint(8,8), QPixmap(":/photos/enemy.png").scaled(50,50));

    scene->addItem(enemy1);

    enemies.push_back(enemy1);

    for (int i = 0; i < enemies.count(); i++)
    {
        Enemy* enemy = enemies[i];
        PathFinder path(enemy->coords, castle->coords, gridWithoutObstacles);
        QList<Node*> obstacles;
        for (Node* node : path.path)
        {
            Node* realNode = grid[node->coords];
            if (!realNode->isWalkable) obstacles.push_back(realNode);
        }
        if (obstacles.count() == 0)
        {
            enemy->processPath(path.path, true);
        }
        else
        {
            Node* newEnd = obstacles[0];
            PathFinder newPath(enemy->coords, newEnd->coords, gridWithoutObstacles);
            enemy->processPath(path.path, false);
            QObject::connect(enemy ,SIGNAL(needNewPath()), this, SLOT(giveNewPath()));
        }
    }
}

void Map1::giveNewPath()
{
    Enemy* enemy = static_cast<Enemy*>(sender());
    PathFinder path(enemy->coords, castle->coords, gridWithoutObstacles);
    QList<Node*> obstacles;
    for (Node* node : path.path)
    {
        Node* realNode = grid[node->coords];
        if (!realNode->isWalkable) obstacles.push_back(node);
    }
    if (obstacles.count() == 0)
    {
        enemy->processPath(path.path, true);
    }
    else
    {
        Node* newEnd = obstacles[0];
        PathFinder newPath(enemy->coords, newEnd->coords, gridWithoutObstacles);
        enemy->processPath(path.path, false);
    }
}*/
