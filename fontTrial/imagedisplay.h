#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QQuickPaintedItem>
#include <QImage>

class ImageDisplay : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit ImageDisplay(QQuickItem *parent = nullptr);
    void setImage(const QImage &image);
    void setCornerRadius(qreal radius);
    void paint(QPainter *painter) override;

private:
    QImage m_image;
    qreal m_cornerRadius = 0;
};

#endif // IMAGEDISPLAY_H
