#ifndef CITIZEN_H
#define CITIZEN_H

#include <QObject>

class citizen : public QObject
{
    Q_OBJECT
public:
    explicit citizen(QObject *parent = nullptr);

signals:
};

#endif // CITIZEN_H
