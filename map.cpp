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
#include<QTime>
//e



Map::Map(QWidget *parent)
    : QObject(nullptr)
{
    timer=nullptr;
    scene = new QGraphicsScene();
    this->mainWindow = static_cast<MainWindow*>(parent);
    setupScene();
    srand(static_cast<uint>(QTime::currentTime().msec()));

    // Create a timer for spawning health markers
    healthMarkerTimer = new QTimer(this);
    connect(healthMarkerTimer, SIGNAL(timeout()), this, SLOT(spawnHealthMarker()));
    healthMarkerTimer->start(10000);

    //s
    m_timer = new Timer();
    scene->addItem(m_timer);

    QTimer* timer = new QTimer(this);
    int remainingTime = 5 * 10;
    connect(timer, &QTimer::timeout, [=]() mutable {
        m_timer->updateTime(remainingTime);
        if (remainingTime == 0) {
            timer->stop();
            m_timer->updateTime(0);
            startThenewLevel();
            QMessageBox::information(nullptr, "info", "CONGRATS YOU WON THE GAME!!");
        } else {
            remainingTime--;
        }
    });
    timer->start(1000); // Start the timer with a 1-second interval




}

void Map:: startThenewLevel()
{
    qDebug () <<"start the newlevel works";
    switch (currentDifficulty)
    {
    case One:
        currentDifficulty=Two;
        break;
    case Two:
        currentDifficulty=Three;
        break;
    case Three:
        currentDifficulty=Four;
        break;
    case Four:
        currentDifficulty=Five;
        break;

    }
    qDebug()<<"current Difficulty Level " << currentDifficulty;
    int newRemainingTime = 0;
    switch (currentDifficulty)
    {
    case One:
        newRemainingTime = 5 * 10;
        break;
    case Two:
        newRemainingTime = 5 * 2;
        QMessageBox::information(nullptr, "info", "You're staying longer this time");
        break;
    case Three:
        newRemainingTime = 5 * 3;
        QMessageBox::information(nullptr, "info", "You're staying longer this time");
        break;
    case Four:
        newRemainingTime = 5 * 4;
        QMessageBox::information(nullptr, "info", "You're staying longer this time");
        break;
    case Five:
        newRemainingTime = 5 * 5;
        QMessageBox::information(nullptr, "info", "You're staying longer this time");
        break;
    }
    qDebug()<<newRemainingTime;
    // Reset the game with the updated difficulty level
    resetGame();
}

void Map::resetGame() {
    qDebug() << "reset works";

    // Clear the scene
    scene->clear();

    // Restart the game setup with the updated parameters
    setupScene();

    // Stop and delete the previous timer if it exists
    if (timer) {
        timer->stop();
        timer->deleteLater();
    }

    // Create a new timer and start it with the new remaining time
    timer = new QTimer(this);
    remainingTime = newRemainingTime;
    connect(timer, &QTimer::timeout, [=]() mutable {
        m_timer->updateTime(remainingTime);
        if (remainingTime == 0) {
            timer->stop();
            m_timer->updateTime(0);
            startThenewLevel();
        } else {
            remainingTime--;
        }
    });
    timer->start(1000);
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

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Node* node = grid.value(QPoint(i, j));
            if (node->building != nullptr)
            {
                buildings.push_back(node->building);
                connect(node->building, SIGNAL(BuildingDamaged()), this, SLOT(OnBuildingDamaged()));
                connect(node->building, SIGNAL(FullyHealed()), this, SLOT(RemoveBuildingFromList()));
            }
        }
    }

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;

            QPoint offset(i, j);
            QPoint coords = castle->coords + offset;
            Citizen* citizen = new Citizen(coords, QPixmap(":/photos/citizen.png").scaled(75,50));
            scene->addItem(citizen);
            citizens.push_back(citizen);
            connect(citizen, SIGNAL(Finished()), this, SLOT(ResetCitizen()));
        }
    }

}

void Map::ResetCitizen()
{
    Citizen* citizen = static_cast<Citizen*>(sender());
    citizen->busy = false;
}

void Map::RemoveBuildingFromList()
{
    qDebug() << "RemoveBuildingFromList";
    Building* building = static_cast<Building*>(sender());
    if (buildingsBeingFixed.contains(building))
    {
        for (int i = 0; i < buildingsBeingFixed.count(); i++)
        {
            if (buildingsBeingFixed[i] == building)
            {
                buildingsBeingFixed.remove(i);
                return;
            }
        }
    }
}

void Map::OnBuildingDamaged()
{
    qDebug() << "OnBuildingDamaged";
    Building* building = static_cast<Building*>(sender());
    if(buildingsBeingFixed.contains(building)) return;
    for(int i = 0; i < citizens.count(); i++)
    {
        Citizen* citizen = citizens[i];
        if(!citizen->busy)
        {
            buildingsBeingFixed.push_back(building);
            citizen->busy = true;
            QPoint beginning(citizen->pos().x() / 100, citizen->pos().y() / 100);
            PathFinder path(beginning, building->coords, grid);
            citizen->ProcessPath(path.path);
            return;
        }
    }
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

void Map::spawnHealthMarker() {
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
