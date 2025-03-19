#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QQuickItem>
#include <QJsonArray>
#include <QPropertyAnimation>
#include "menuasset.h"

class GridView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal contentY READ contentY WRITE setContentY)

public:
    explicit GridView(QQuickItem *parent = nullptr);
    void setRowModel(const QJsonArray &rowModel);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;

private slots:
    void handleWidthChanged();

private:
    void createGrid();
    void updateLayout();
    void setFocusToCell(int rowIndex, int colIndex);
    void updateFocus();
    void updateRowPositions();
    
    QJsonArray m_rowModel;
    QVector<QVector<MenuAsset*>> m_grid;
    int m_focusedRowIndex = 0;
    int m_focusedColIndex = 0;
    
    static constexpr qreal ROW_SPACING = 32;
    static constexpr qreal COLUMN_SPACING = 16;
    static constexpr qreal ITEM_WIDTH = 240;
    static constexpr qreal ITEM_HEIGHT = 192;

    QPropertyAnimation* m_animation;
    qreal m_contentY;
    bool m_animating;
    QQuickItem* m_container;

    qreal contentY() const { return m_contentY; }
    void setContentY(qreal y);
};

#endif // GRIDVIEW_H