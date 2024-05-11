#ifndef CITIZEN_H
#define CITIZEN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <node.h>
#include <QTimer>

class Citizen : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    QList<Node*> currentPath;
    int currentNodeIndex = 0;
    QTimer* currentTimer;
public:
    explicit Citizen(QPoint coords, QPixmap map);
    void ProcessPath(QList<Node*> path);
    bool busy = false;

public slots:
    void MoveToNextNode();
    void HealBuilding();
    void MakeAvailable();

signals:
    void Finished();
};

#endif // CITIZEN_H
