#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <QGraphicsTextItem>


class HealthBar : public QGraphicsTextItem
{
    Q_OBJECT
private:
    int health;
public:
    HealthBar();
public slots:
    void increment(int);
    void decrement(int);
    int geth();
    void hrestart();
};

#endif
