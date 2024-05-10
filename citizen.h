#ifndef CITIZEN_H
#define CITIZEN_H

#include <QObject>
#include <QGraphicsPixmapItem>

class citizen : public QObject, QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit citizen(QPoint coords, QPixmap map);

public slots:

};

#endif // CITIZEN_H
