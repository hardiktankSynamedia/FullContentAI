#include "imagedisplay.h"
#include <QPainter>
#include <QPainterPath>

ImageDisplay::ImageDisplay(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
}

void ImageDisplay::setImage(const QImage &image)
{
    m_image = image;
    update();
}

void ImageDisplay::setCornerRadius(qreal radius)
{
    m_cornerRadius = radius;
    update();
}

void ImageDisplay::paint(QPainter *painter)
{
    if (!m_image.isNull()) {
        painter->setRenderHint(QPainter::Antialiasing);
        
        // Create a path for rounded rectangle
        QPainterPath path;
        path.addRoundedRect(boundingRect(), m_cornerRadius, m_cornerRadius);
        
        // Set the clip path
        painter->setClipPath(path);
        
        // Draw the image
        painter->drawImage(boundingRect(), m_image, m_image.rect());
    }
}
