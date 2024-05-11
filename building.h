#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QBrush>

class HealthBar : public QGraphicsRectItem {
public:
    HealthBar(qreal width, qreal height, QPointF pos, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(parent), m_value(500) {
        setRect(0, 0, width, height);
        setValue(500);
        QBrush brush(Qt::green );
        setBrush(brush);
        setPos(pos.x(), pos.y() + 10);
    }

    void setValue(int value) {
        m_value = value;
        qreal newWidth = rect().width() * (m_value / 500.0);
        setRect(0, 0, newWidth, rect().height());
        QBrush brush;
        if (m_value > 350)
            brush = QBrush(Qt::green);
        else if (m_value > 150)
            brush = QBrush(Qt::yellow);
        else
            brush = QBrush(Qt::red);
        setBrush(brush);
    }

private:
    int m_value;
};


class Building : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int currentHitpoints = 500;
    int maximumHitpoints = 500;
    HealthBar* bar;
public:
    int CurrentHitPoints()
    {
        return currentHitpoints;
    }
    QPoint coords;

    explicit Building(QPoint, QPixmap);

    void TakeDamage();
};

#endif // BUILDING_H
