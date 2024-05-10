#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsItem>

class Timer : public QGraphicsItem {
public:
    Timer(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void updateTime(int remainingTime);
    void setTextColor(const QColor& color);

private:
    QString m_timeString;
    QColor m_textColor;
};

#endif
