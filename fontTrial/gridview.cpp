#include "gridview.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include "performancelogger.h"

GridView::GridView(QQuickItem *parent) : QQuickItem(parent)
{
    setFlag(ItemIsFocusScope);
    setFlag(ItemClipsChildrenToShape);
    setFocus(true);
    
    m_container = new QQuickItem(this);
    m_container->setClip(true);
    m_container->setHeight(3 * ITEM_HEIGHT + ROW_SPACING);
    m_container->setWidth(width());
    
    m_animation = new QPropertyAnimation(this, "contentY", this);
    m_animation->setDuration(500);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    m_contentY = 0;
    m_animating = false;

    connect(this, &QQuickItem::widthChanged, this, &GridView::handleWidthChanged);
}

void GridView::setRowModel(const QJsonArray &rowModel)
{
    m_rowModel = rowModel;
    m_grid.clear();
    createGrid();
    setFocusToCell(0, 0);
}

void GridView::createGrid()
{
    PerformanceLogger::instance()->startOperation("GridView::createGrid");
    
    qreal yPos = 0;
    
    for (int row = 0; row < m_rowModel.size(); ++row) {
        QJsonArray items = m_rowModel[row].toObject()["items"].toArray();
        qreal xPos = 0;
        QVector<MenuAsset*> rowAssets;
        
        for (int col = 0; col < items.size(); ++col) {
            MenuAsset* asset = new MenuAsset(items[col].toObject(), this);
            asset->setParentItem(m_container);
            asset->setX(xPos);
            asset->setY(yPos);
            asset->setWidth(ITEM_WIDTH);
            asset->setHeight(ITEM_HEIGHT);
            asset->setFocused(row == 0 && col == 0);
            
            rowAssets.append(asset);
            xPos += ITEM_WIDTH + COLUMN_SPACING;
        }
        
        m_grid.append(rowAssets);
        
        if (xPos > width()) {
            setWidth(xPos - COLUMN_SPACING);
        }
        
        yPos += ITEM_HEIGHT + ROW_SPACING;
    }
    
    setHeight(yPos - ROW_SPACING);
    
    PerformanceLogger::instance()->endOperation("GridView::createGrid");
}

void GridView::keyPressEvent(QKeyEvent *event)
{
    if (m_grid.isEmpty()) return;

    int currentRow = m_focusedRowIndex;
    int currentCol = m_focusedColIndex;
    int maxCols = m_grid[currentRow].size();

    switch (event->key()) {
        case Qt::Key_Left:
            if (currentCol > 0) {
                setFocusToCell(currentRow, currentCol - 1);
            } else if (currentRow > 0) {
                int prevRow = currentRow - 1;
                int lastCol = m_grid[prevRow].size() - 1;
                setFocusToCell(prevRow, lastCol);
            }
            break;

        case Qt::Key_Right:
            if (currentCol < maxCols - 1) {
                setFocusToCell(currentRow, currentCol + 1);
            } else if (currentRow < m_grid.size() - 1) {
                setFocusToCell(currentRow + 1, 0);
            }
            break;

        case Qt::Key_Up:
            if (currentRow > 0) {
                setFocusToCell(currentRow - 1, currentCol);
            }
            break;

        case Qt::Key_Down:
            if (currentRow < m_grid.size() - 1) {
                setFocusToCell(currentRow + 1, currentCol);
            }
            break;

        default:
            QQuickItem::keyPressEvent(event);
            return;
    }
    
    event->accept();
}

void GridView::setFocusToCell(int rowIndex, int colIndex)
{
    if (rowIndex < 0 || rowIndex >= m_grid.size()) return;
    if (colIndex < 0 || colIndex >= m_grid[rowIndex].size()) return;

    if (m_focusedRowIndex < m_grid.size() && 
        m_focusedColIndex < m_grid[m_focusedRowIndex].size()) {
        m_grid[m_focusedRowIndex][m_focusedColIndex]->setFocused(false);
    }

    m_focusedRowIndex = rowIndex;
    m_focusedColIndex = colIndex;
    m_grid[rowIndex][colIndex]->setFocused(true);

    updateLayout();
}

void GridView::focusInEvent(QFocusEvent *event)
{
    QQuickItem::focusInEvent(event);
    updateFocus();
}

void GridView::updateFocus()
{
    if (!m_grid.isEmpty()) {
        setFocusToCell(m_focusedRowIndex, m_focusedColIndex);
    }
}

void GridView::setContentY(qreal y)
{
    if (m_contentY != y) {
        m_contentY = y;
        updateRowPositions();
    }
}

void GridView::updateRowPositions()
{
    for (int row = 0; row < m_grid.size(); ++row) {
        for (int col = 0; col < m_grid[row].size(); ++col) {
            m_grid[row][col]->setY(m_contentY + (row * (ITEM_HEIGHT + ROW_SPACING)));
        }
    }
}

void GridView::updateLayout()
{
    if (m_animating) {
        m_animation->stop();
    }

    qreal targetY = -(m_focusedRowIndex * (ITEM_HEIGHT + ROW_SPACING));
    
    m_animation->setStartValue(m_contentY);
    m_animation->setEndValue(targetY);
    m_animation->start();
    m_animating = true;

    connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        m_animating = false;
    });
}

void GridView::handleWidthChanged()
{
    if (m_container) {
        m_container->setWidth(width());
    }
}