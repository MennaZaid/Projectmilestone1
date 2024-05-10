#include "tiles.h"
#include "node.h"
#include "map.h"
#include "pathfinder.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "MyGraphicsPixmapItem.h"
//s
#include<QApplication>
#include<QLabel>
#include<QTimer>
//e



Map::Map(QWidget *parent)
    : QObject(nullptr)
{
    scene = new QGraphicsScene();
    this->mainWindow = static_cast<MainWindow*>(parent);
    setupScene();


    //s
    m_timer=new Timer();
    scene->addItem(m_timer);

    QTimer* timer = new QTimer(this);
    int remainingTime = 5 * 60;
    connect(timer, &QTimer::timeout, [=]() mutable {
        m_timer->updateTime(remainingTime);
        if (remainingTime == 0) {
            timer->stop();
            m_timer->updateTime(0);
        } else {
            remainingTime--;
            //s
            if(remainingTime==0){
                QMessageBox::information(nullptr, "info", "CONGRATS YOU WON THE GAVE!!");
            }
            //e
        }
    });
    timer->start(1000);


    //e



    // //s

    // QLabel label("Time remaining: 5:00", nullptr, Qt::WindowStaysOnTopHint);
    // label.setAlignment(Qt::AlignCenter);
    // label.resize(200,100);
    // label.show();
    // scene->addItem(label);
    // //QTimer timer;
    // int remainingTime=5*60;

    // QObject::connect(&timer,&QTimer::timeout,[&](){

    //     int minutes=remainingTime/60;
    //     int seconds=remainingTime%60;

    //     QString timestring=QString("%1:%2").arg(minutes,2,10,QChar('0')).arg(seconds,2,10,QChar('0'));
    //     label.setText("Time remaining: "+timestring);


    //     if(remainingTime==0){
    //         timer.stop();
    //         //gameover
    //         label.setText("Time's up!");
    //     }
    //     else{
    //         remainingTime--;
    //     }

    // });
    // //e
}

void Map::setupScene()
{
    loadmapfromfile(":/map1.txt");
    QGraphicsView* view = new QGraphicsView(scene);
    view->setFixedSize(scene->width(), scene->height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
}

void Map::loadmapfromfile(const QString &filename)
{

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

    int i = 0;
    QList<QString> lines;

    while (!in.atEnd()) {
        Tiles tilemap1;
        lines.append(in.readLine());
    }


    for (int i = 0; i < lines.count(); i++)
    {
        QString line = lines[i];

        for (int j = 0;  j < line.length() / 2; j++)
        {
            QGraphicsPixmapItem *image1 = new QGraphicsPixmapItem(tilemap1.map1tiles["Default"].scaled(pixelWidth, pixelHeight));
            image1->setPos(posX, posY);
            scene->addItem(image1);
            posX += pixelWidth;
        }

        posX = 0;

        for (int j = 0; j < line.length() / 2; j++)
        {
            Node* node = new Node(QPoint(j,i));
            node->isWalkable = true;
            QChar character = line[j * 2];
            if (character == '0') {
            } else if (character == '1') {
                castle = new Building(QPoint(j, i), tilemap1.map1tiles["Castle"].scaled(pixelWidth, pixelHeight));
                castle->setPos(posX, posY);
                scene->addItem(castle);
                node->building = castle;
            } else if (character == '2') {
                Building* cannon = new Building(QPoint(j, i), tilemap1.map1tiles["Cannon"].scaled(pixelWidth, pixelHeight));
                cannon->setPos(posX, posY);
                scene->addItem(cannon);
                MyGraphicsPixmapItem *item = new MyGraphicsPixmapItem(cannon);
                scene->addItem(item);
                node->building = cannon;
                node->isWalkable = false;
            } else if (character == '3') {
                Building* fence = new Building(QPoint(j, i), tilemap1.map1tiles["Fence"].scaled(pixelWidth, pixelHeight));
                fence->setPos(posX, posY);
                scene->addItem(fence);
                node->building = fence;
            }
            grid[node->coords] = node;
            posX += pixelWidth;
        }
        posX = 0;
        posY += pixelHeight;
    }
    file.close();

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(AddEnemy()));
    timer->start(2000);
}

void Map::AddEnemy()
{
    int enemyPosX = rand() % 9;

    QPoint coords(enemyPosX, 0);
    Enemy* enemy = new Enemy(coords, QPixmap(":/photos/enemy.png").scaled(50, 50));
    scene->addItem(enemy);

    PathFinder path(coords, castle->coords, grid);
    enemy->processPath(path.path);
}
