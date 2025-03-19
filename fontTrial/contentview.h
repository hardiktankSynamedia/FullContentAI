#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include <QQuickItem>
#include <QQuickWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "menuasset.h"

class ContentView : public QQuickItem
{
    Q_OBJECT
public:
    explicit ContentView(QQuickItem *parent = nullptr);
    void initialize();

signals:
    void backPressed();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override {
        QQuickItem::focusInEvent(event);
        // When ContentView gets focus, pass it to GridView  // Changed comment
        QQuickItem* gridView = childItems().isEmpty() ? nullptr : childItems().first();
        if (gridView) {
            gridView->setFocus(true);
        }
    }

private:
    QJsonObject loadAssetModel();
    void loadAndParseContent();
    MenuAsset* m_menuAsset;
};

#endif // CONTENTVIEW_H
