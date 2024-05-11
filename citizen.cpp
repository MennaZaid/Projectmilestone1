#include "citizen.h"

float dotProduct1(QPointF a, QPointF b)
{
    return a.x() * b.x() + a.y() * b.y();
}

QPointF lerp1(QPointF a, QPointF b, float t)
{
    return (1-t) * a + t * b;
}

float inverseLerp1(QPointF a, QPointF b, QPointF v)
{
    //Find how far the lerp is between 2 points, a and b

    QPointF ab = b - a;
    QPointF av = v - a;

    float nominator = dotProduct1(ab, av);
    float denominator = dotProduct1(ab, ab);
    return (nominator / denominator); // Or you can do it by components (i.e ab.y / av.y
    //  but I like this because it looks more elegant
}


Citizen::Citizen(QPoint coords, QPixmap map) : QObject(nullptr), QGraphicsPixmapItem(nullptr)
{
    setPixmap(map);
    setPos(coords * 100);
}

void Citizen::ProcessPath(QList<Node *> path)
{
    this->currentPath = path;
    currentNodeIndex = 0;
    connect(currentPath.value(path.count() - 1)->building, SIGNAL(destroyed(QObject*)), this, SLOT(MakeAvailable()));
    currentTimer = new QTimer();
    connect(currentTimer,SIGNAL(timeout()), this, SLOT(MoveToNextNode()));
    currentTimer->start(10);
}

void Citizen::MoveToNextNode()
{
    Node* currentNode = currentPath[currentNodeIndex];

    if (currentNodeIndex == currentPath.count() - 2)
    {
        disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(MoveToNextNode()));
        delete currentTimer;
        currentTimer = new QTimer();
        connect(currentTimer, SIGNAL(timeout()), this, SLOT(HealBuilding()));
        currentTimer->start(20);
        connect(currentPath.value(currentNodeIndex + 1)->building, SIGNAL(FullyHealed()), this, SLOT(MakeAvailable()));
    }

    Node* nextNode = currentPath[currentNodeIndex + 1];

    //This is needed to find where the enemy is its path between 2 nodes
    float currentValue = inverseLerp1(QPointF(currentNode->coords) * 100, QPointF(nextNode->coords) * 100, pos());
    // This is the new position, plus a small increment to make it actually move
    QPointF newPoint = lerp1(QPointF(currentNode->coords) * 100, QPointF(nextNode->coords) * 100, currentValue + 0.005);
    setPos(newPoint);

    if (currentValue >= 1)
    {
        currentNodeIndex++;
    }
}

void Citizen::HealBuilding()
{
    Node* currentNode = currentPath[currentNodeIndex + 1];
    currentNode->building->Heal();
}

void Citizen::MakeAvailable()
{
    if (currentPath.value(currentNodeIndex + 1)->building != nullptr)
    {
        disconnect(currentPath.value(currentNodeIndex + 1)->building, SIGNAL(destroyed(QObject*)), this, SLOT(MakeAvailable()));
        disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(HealBuilding()));
        disconnect(currentPath.value(currentNodeIndex + 1)->building, SIGNAL(FullyHealed()), this, SLOT(MakeAvailable()));
        disconnect(currentPath.value(currentNodeIndex + 1)->building, SIGNAL(FullyHealed()), this, SLOT(MakeAvailable()));
    }
    delete currentTimer;
    emit Finished();
}
