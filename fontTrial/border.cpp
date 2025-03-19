#include "border.h"
#include <QPainter>
#include <QPainterPath>

Border::Border(QQuickItem *parent) 
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
}

void Border::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    
    QPen pen(QColor("#ebebeb"));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    
    QPainterPath path;
    path.addRoundedRect(1, 1, width()-2, height()-2, 6, 6);
    painter->drawPath(path);
}
