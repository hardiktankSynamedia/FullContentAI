#include "blackscreenview.h"
#include "performancedatautil.h"
#include <QKeyEvent>
#include <QFont>
#include <QDebug>
#include <QTimer>

BlackScreenView::BlackScreenView(QQuickItem *parent) 
    : QQuickItem(parent)
    , m_contentView(nullptr)
    , m_text(nullptr)
{
    setFlag(ItemAcceptsInputMethod);
    setFlag(ItemIsFocusScope);
    setAcceptedMouseButtons(Qt::AllButtons);

    // Create performance text painter
    m_perfText = new CustomTextPainter(this);
    m_perfText->setX(136);
    m_perfText->setY(48);
    m_perfText->setHeight(24);
    m_perfText->setWidth(1000);
    m_perfText->setColor(QColor("white"));
    QFont font;
    font.setFamily("Gotham Narrow Book");
    font.setPixelSize(20);
    m_perfText->setFont(font);
    
    // Connect to PerformanceDataUtil signal
    connect(PerformanceDataUtil::instance(), &PerformanceDataUtil::perfDataChanged,
            this, &BlackScreenView::updatePerfText);
    
    // Comment out timer based updates
    /*
    QTimer* updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &BlackScreenView::updatePerfText);
    updateTimer->start(1000); // Update every second
    */
}

void BlackScreenView::componentComplete()
{
    QQuickItem::componentComplete();
    setupText();
    setFocus(true);
}

void BlackScreenView::setupText()
{
    if (!m_text) {
        m_text = new CustomTextPainter(this);
        m_text->setParentItem(this);
        m_text->setText("Press Enter to load");
        
        QFont font;
        font.setFamily("Gotham Narrow Book");
        font.setPixelSize(50);
        m_text->setFont(font);
        m_text->setColor(QColor("white"));
        m_text->setWidth(width());
        m_text->setHeight(height());
        m_text->setAlignment(Qt::AlignCenter);

        connect(this, &QQuickItem::widthChanged, this, [this]() {
            if (m_text) {
                m_text->setWidth(width());
                m_text->setX(0);
            }
        });
        
        connect(this, &QQuickItem::heightChanged, this, [this]() {
            if (m_text) {
                m_text->setHeight(height());
                m_text->setY(0);
            }
        });
    }
}

void BlackScreenView::itemChange(ItemChange change, const ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);
    if (change == ItemSceneChange && data.window) {
        // Window changed, ensure focus is set
        setFocus(true);
    }
}

void BlackScreenView::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Select || event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && !m_contentView) {
        createContentView();
        event->accept();
        return;
    }
    if (m_contentView) {

    }else{
        if (event->key() == Qt::Key_Back || event->key() == Qt::Key_Escape || event->key() == Qt::Key_Backspace) {
            event->accept();
            return;
        }
    }

    QQuickItem::keyPressEvent(event);
}

void BlackScreenView::createContentView()
{
    m_text->setVisible(false);  // Hide text when content view is shown
    m_contentView = new ContentView(this);
    m_contentView->setWidth(1280);
    m_contentView->setHeight(720);
    m_contentView->initialize();
    m_contentView->setFocus(true);

    connect(m_contentView, &ContentView::backPressed, this, [this]() {
        destroyContentView();
        setFocus(true);
    });
}

void BlackScreenView::destroyContentView()
{
    if (m_contentView) {
        m_contentView->deleteLater();
        m_contentView = nullptr;
        m_text->setVisible(true);  // Show text again when returning to black screen
    }
}

void BlackScreenView::updatePerfText()
{
    QString perfText;
    QMap<QString, PerfData>& perfMap = PerformanceDataUtil::instance()->m_perfMap;
    
    QMapIterator<QString, PerfData> it(perfMap);
    while (it.hasNext()) {
        it.next();
        const QString& opName = it.key();
        const PerfData& data = it.value();
        
        perfText += QString("%1: Latest=%2ms, Avg=%3ms, Samples=%4, MenuAsset_Count=24\n")
            .arg(opName)
            .arg(data.timeData.isEmpty() ? 0 : data.timeData.last())
            .arg(data.average, 0, 'f', 2)
            .arg(data.timeData.size());
    }
    
    
    m_perfText->setText(perfText);
    emit perfDataChanged();
}
