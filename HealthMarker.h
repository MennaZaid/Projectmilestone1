#ifndef HEALTHMARKER_H
#define HEALTHMARKER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>


class HealthMarker : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    HealthMarker(QGraphicsItem *parent = nullptr);

signals:
    void markerHit();

public slots:
    void handleCollision();
};

#endif
