#ifndef BORDER_H
#define BORDER_H

#include <QQuickPaintedItem>

class Border : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Border(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
};

#endif // BORDER_H
