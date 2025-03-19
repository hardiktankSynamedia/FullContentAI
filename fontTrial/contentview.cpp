#include "contentview.h"
#include "gridview.h"  // Changed from tableview.h
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>

ContentView::ContentView(QQuickItem *parent) : QQuickItem(parent)
{
    // Enable focus and key handling
    setFlag(ItemIsFocusScope);
    setFlag(ItemAcceptsInputMethod);
    // Remove ItemStopsFocusHandling as it's not available in Qt 5.4.2
    setFocus(true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void ContentView::initialize()
{
    if (window()) {
        /*QJsonObject assetModel = loadAssetModel();
        m_menuAsset = new MenuAsset(assetModel, this);
        m_menuAsset->setX(60);
        m_menuAsset->setY(60);
        m_menuAsset->setWidth(240);
        m_menuAsset->setHeight(192);
        m_menuAsset->setParentItem(this;*/
        loadAndParseContent();
    }
}

QJsonObject ContentView::loadAssetModel()
{
    QFile file(":/data/assetItem.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open asset file";
        return QJsonObject();
    }

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    return document.object();
}

void ContentView::loadAndParseContent()
{
    QFile file(":/data/fullContent.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open fullContent.json";
        return;
    }

    QByteArray jsonData = file.readAll();
    if (jsonData.startsWith("\xEF\xBB\xBF")) {
        jsonData.remove(0, 3);
    }

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject root = doc.object();
    QJsonObject embedded = root["embedded"].toObject();
    QJsonObject assetList = embedded["assetList"].toObject();
    QJsonArray rowModel = assetList["items"].toArray();

    GridView* gridView = new GridView(this);  // Changed from TableView
    gridView->setRowModel(rowModel);
    gridView->setParentItem(this);
    gridView->setX(136);
    gridView->setY(128);
    gridView->setFocus(true);  // Give focus to GridView
    
    /*qreal xPos = 60;
    const qreal yPos = 300;
    const qreal GAP = 5;
    
    for (int i = 0; i < firstRow.size(); ++i) {
        MenuAsset* asset = new MenuAsset(firstRow.at(i).toObject(), this);
        asset->setParentItem(this);
        asset->setX(xPos);
        asset->setY(yPos);
        asset->setWidth(240);
        asset->setHeight(192);
        xPos += 240 + GAP;
    }*/

    setWidth(gridView->width());
    setHeight(gridView->height());
}

void ContentView::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "ContentView received key:" << event->key();
    
    if (event->key() == Qt::Key_Back || event->key() == Qt::Key_Escape || event->key() == Qt::Key_Backspace) {
        emit backPressed();
        event->accept();
        return;
    }
    
    // Modified focus handling for Qt 5.4.2
    QQuickItem* focusItem = nullptr;
    if (window()) {
        focusItem = window()->activeFocusItem();
    }
    
    if (focusItem && focusItem != this) {
        QCoreApplication::sendEvent(focusItem, event);
    } else {
        QQuickItem::keyPressEvent(event);
    }
}
