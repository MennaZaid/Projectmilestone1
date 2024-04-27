#include "enemy.h"
#include <QMessageBox>

float dotProduct(QPointF a, QPointF b)
{
    return a.x() * b.x() + a.y() * b.y();
}

Enemy::~Enemy()
{
    delete currentTimer;
    delete this;
}

QPointF lerp(QPointF a, QPointF b, float t)
{
    return (1-t) * a + t * b;
}

float inverseLerp(QPointF a, QPointF b, QPointF v)
{
    QPointF ab = b - a;
    QPointF av = v - a;

    float nominator = dotProduct(ab, av);
    float denominator = dotProduct(ab, ab);

    return (nominator / denominator); // Or you can do it by components (i.e ab.y / av.y
    //  but I like this because it looks more elegant
}

Enemy::Enemy(QPoint coords, QPixmap pixMap) : QGraphicsPixmapItem(nullptr), QObject(nullptr)
{
    setPixmap(pixMap);
    this->coords = coords;
}
void Enemy::processPath(QList<Node*> path, bool isCastlePath)
{
    this->currentNodeOnPath = 0;
    this->currentPath = path;
    this->isCastlePath = isCastlePath;

    currentTimer = new QTimer();
    connect(currentTimer, SIGNAL(timeout()), this, SLOT (moveOnPath()));
    currentTimer->start(15);
}

void Enemy::DamageBuilding()
{
    Node* node = currentPath.last();
    node->building->TakeDamage();
    if (node->building->CurrentHitPoints() < 0)
    {
        if (!isCastlePath)
        {
            disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(DamageBuilding()));
            delete currentTimer;
            delete node->building;
            emit needNewPath();
        }
        else
        {
            disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(DamageBuilding()));
            delete currentTimer;
            delete node->building;
            QMessageBox::information(nullptr, "info", "YOU LOST THE GAME!!");
        }
    }
}

void Enemy::moveOnPath()
{
    if (currentNodeOnPath == currentPath.count() - 1)
    {
        if (!isCastlePath)
        {
            currentNodeOnPath = 0;
            disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(moveOnPath()));
            delete currentTimer;
            currentTimer = new QTimer();
            connect(currentTimer, SIGNAL(timeout()), this, SLOT(DamageBuilding()));
            currentTimer->start(1000);
            return;
        }
        else
        {
            disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(moveOnPath()));
            delete currentTimer;
            currentTimer = new QTimer();
            connect(currentTimer, SIGNAL(timeout()), this, SLOT(DamageBuilding()));
            currentTimer->start(1000);
            return;
        }
    }
    Node* currentNode = currentPath[currentNodeOnPath];
    Node* nextNode = currentPath[currentNodeOnPath + 1];

    float currentValue = inverseLerp(QPointF(currentNode->coords) * 100, QPointF(nextNode->coords) * 100, pos());


    QPointF newPoint = lerp(QPointF(currentNode->coords) * 100, QPointF(nextNode->coords) * 100, currentValue + 0.005);

    setPos(newPoint);

    if (currentValue >= 1)
    {
        coords = nextNode->coords;
        currentNodeOnPath++;
    }
}

