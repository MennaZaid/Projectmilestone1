
#ifndef NODE_H
#define NODE_H

#include "building.h"
#include <QPoint>
#include "QObject"

class Node
{
public:
    Node(QPoint, Building* building = nullptr);
    QPoint coords; //In int

    Building* building;

    int gCost = INT32_MAX;
    int hCost = 0;
    Node* connectedTo;


    bool isWalkable;
    int getfCost()
    {
        return gCost + hCost;
    }

};

#endif // NODE_H

