#pragma once

#include <QQuickPaintedItem>
#include <QColor>

class ProgressBar : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qreal progressPercentage READ progressPercentage WRITE setProgressPercentage NOTIFY progressPercentageChanged)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    explicit ProgressBar(QQuickItem *parent = nullptr);
    explicit ProgressBar(const QColor& bgColor, const QColor& fgColor, int percentage, QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    qreal progressPercentage() const { return m_progressPercentage; }
    QColor foregroundColor() const { return m_foregroundColor; }
    QColor backgroundColor() const { return m_backgroundColor; }

public slots:
    void setProgressPercentage(qreal percentage);
    void setForegroundColor(const QColor &color);
    void setBackgroundColor(const QColor &color);

signals:
    void progressPercentageChanged();
    void foregroundColorChanged();
    void backgroundColorChanged();

private:
    qreal m_progressPercentage;
    QColor m_foregroundColor;
    QColor m_backgroundColor;
};
