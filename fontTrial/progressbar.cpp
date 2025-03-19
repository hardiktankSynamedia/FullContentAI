#include "progressbar.h"
#include <QPainter>

ProgressBar::ProgressBar(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_progressPercentage(0)
    , m_foregroundColor(Qt::white)
    , m_backgroundColor(Qt::gray)
{
    setAntialiasing(true);
}

ProgressBar::ProgressBar(const QColor& bgColor, const QColor& fgColor, int percentage, QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    setBackgroundColor(bgColor);
    setForegroundColor(fgColor);
    setProgressPercentage(percentage);
}

void ProgressBar::paint(QPainter *painter)
{
    QRectF bounds = boundingRect();
    
    // Draw background
    painter->fillRect(bounds, m_backgroundColor);
    
    // Draw progress
    QRectF progressRect = bounds;
    progressRect.setWidth(bounds.width() * (m_progressPercentage / 100.0));
    painter->fillRect(progressRect, m_foregroundColor);
}

void ProgressBar::setForegroundColor(const QColor &color)
{
    if (m_foregroundColor != color) {
        m_foregroundColor = color;
        update(); // Trigger repaint
        emit foregroundColorChanged();
    }
}

void ProgressBar::setBackgroundColor(const QColor &color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        update(); // Trigger repaint
        emit backgroundColorChanged();
    }
}

void ProgressBar::setProgressPercentage(qreal percentage)
{
    percentage = qBound(0.0, percentage, 100.0);
    if (!qFuzzyCompare(m_progressPercentage, percentage)) {
        m_progressPercentage = percentage;
        update(); // Trigger repaint
        emit progressPercentageChanged();
    }
}
