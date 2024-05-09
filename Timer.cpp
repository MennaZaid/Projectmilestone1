#include "Timer.h"
#include <QPainter>

Timer::Timer(QGraphicsItem* parent) : QGraphicsItem(parent) {

    m_textColor = Qt::black;
}

QRectF Timer::boundingRect() const {
    return QRectF(0, 0, 150, 50);
}

void Timer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(m_textColor);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_timeString);
}

void Timer::updateTime(int remainingTime) {
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    m_timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    update();
}

void Timer::setTextColor(const QColor& color) {
    m_textColor = color;
    update();
}
