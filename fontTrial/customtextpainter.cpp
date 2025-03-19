#include "customtextpainter.h"
#include <QPainter>

CustomTextPainter::CustomTextPainter(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_alignment(Qt::AlignLeft | Qt::AlignTop)
    , m_padding(0)
    , m_lineHeight(1.0)
    , m_elideMode(Qt::ElideNone)
    , m_clip(false)
    , m_borderWidth(0)
{
    setAntialiasing(true);
}

void CustomTextPainter::paint(QPainter *painter)
{
    painter->save();
    painter->setPen(m_color);
    painter->setFont(m_font);

//    QRectF boundingRect = painter->boundingRect(
//        QRectF(m_padding, m_padding,
//               width() - 2 * m_padding,
//               height() - 2 * m_padding),
//        m_alignment,
//        m_text
//    );

    QString displayText = m_text;
    if (m_elideMode != Qt::ElideNone) {
        displayText = painter->fontMetrics().elidedText(
            m_text,
            m_elideMode,
            width() - 2 * m_padding
        );
    }

    painter->drawText(
        QRectF(m_padding, m_padding,
               width() - 2 * m_padding,
               height() - 2 * m_padding),
        m_alignment,
        displayText
    );
    
    // Draw border if width > 0
    if (m_borderWidth > 0) {
        painter->setPen(QPen(m_borderColor, m_borderWidth));
        painter->drawRect(boundingRect());
    }

    painter->restore();
}

void CustomTextPainter::setText(const QString &text)
{
    if (m_text != text) {
        m_text = text;
        emit textChanged();
        update();
    }
}

void CustomTextPainter::setFont(const QFont &font)
{
    if (m_font != font) {
        m_font = font;
        emit fontChanged();
        update();
    }
}

void CustomTextPainter::setColor(const QColor &color)
{
    if (m_color != color) {
        m_color = color;
        emit colorChanged();
        update();
    }
}

void CustomTextPainter::setAlignment(Qt::Alignment alignment)
{
    if (m_alignment != alignment) {
        m_alignment = alignment;
        emit alignmentChanged();
        update();
    }
}

void CustomTextPainter::setPadding(qreal padding)
{
    if (m_padding != padding) {
        m_padding = padding;
        emit paddingChanged();
        update();
    }
}

void CustomTextPainter::setLineHeight(qreal lineHeight)
{
    if (m_lineHeight != lineHeight) {
        m_lineHeight = lineHeight;
        emit lineHeightChanged();
        update();
    }
}

void CustomTextPainter::setElideMode(Qt::TextElideMode mode)
{
    if (m_elideMode != mode) {
        m_elideMode = mode;
        emit elideModeChanged();
        update();
    }
}

void CustomTextPainter::setClip(bool clip)
{
    if (m_clip != clip) {
        m_clip = clip;
        setClip(clip);
        emit clipChanged();
        update();
    }
}

void CustomTextPainter::setBorderWidth(qreal width)
{
    m_borderWidth = width;
    update();
}

void CustomTextPainter::setBorderColor(const QColor& color)
{
    m_borderColor = color;
    update();
}

void CustomTextPainter::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QQuickPaintedItem::mousePressEvent(event);
}

void CustomTextPainter::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event->key());
    QQuickPaintedItem::keyPressEvent(event);
}
