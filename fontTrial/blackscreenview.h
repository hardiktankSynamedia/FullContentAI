#ifndef BLACKSCREENVIEW_H
#define BLACKSCREENVIEW_H

#include <QQuickItem>
#include "contentview.h"
#include "customtextpainter.h"

class BlackScreenView : public QQuickItem
{
    Q_OBJECT

public:
    explicit BlackScreenView(QQuickItem *parent = nullptr);

signals:
    void perfDataChanged();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void componentComplete() override;
    void itemChange(ItemChange change, const ItemChangeData &data) override;

private:
    ContentView* m_contentView;
    CustomTextPainter* m_text;
    CustomTextPainter* m_perfText;
    void createContentView();
    void destroyContentView();
    void setupText();

public slots:
    void updatePerfText();
};

#endif // BLACKSCREENVIEW_H
