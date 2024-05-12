#include"HealthBar.h"
#include <QString>
#include<QFont>

HealthBar::HealthBar()
{
    health = 100;
    setPlainText("Health:\n" + QString::number(health));
    setDefaultTextColor(Qt::magenta);
    setFont(QFont("times", 14));
}

void HealthBar::decrement(int decrease)
{
    health -= decrease;
    setPlainText("Health:\n" + QString::number(health));
}

void HealthBar::increment(int add)
{
    health +=add;
    setPlainText("Health:\n" + QString::number(health));
}

int HealthBar::geth()
{
    return health;
}

void HealthBar::hrestart()
{
    health = 100;
    setPlainText("Health:\n" + QString::number(health));
}
