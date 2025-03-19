#include "menuasset.h"
#include <QFontMetrics>

MenuAsset::MenuAsset(const QJsonObject& assetModel, QQuickItem *parent) 
    : QQuickItem(parent)
    , m_assetModel(assetModel)
    , m_baseX(0)
    , m_baseY(0)
{
    m_title = new CustomTextPainter(this);
    m_imageLoader = new ImageLoader(this);
    m_thumbnailImage = new ImageDisplay(this);
    m_channelLogoLoader = new ImageLoader(this);
    m_channelLogo = new ImageDisplay(this);
    m_assetDimmerLoader = new ImageLoader(this);
    m_assetDimmer = new ImageDisplay(this);
    m_progressBar = new ProgressBar(QColor("#656565"), QColor("#D7D7D7"), 50, this);
    m_border = new Border(this);
    m_elideFaderLoader = new ImageLoader(this);
    m_elideFader = new ImageDisplay(this);

    // Create all components first
    
    loadThumbnailImage();
    createAssetDimmer();
    createChannelLogo();
    createProgressBar();
    populateAssetTitle();
    createMetaDataRect();
    createElideFader();

    // Set all parent items
    m_thumbnailImage->setParentItem(this);
    m_assetDimmer->setParentItem(this);
    m_channelLogo->setParentItem(this);
    m_title->setParentItem(this);
    m_progressBar->setParentItem(this);
    m_border->setParentItem(this);
    m_elideFader->setParentItem(this);

    // Set z-order for visibility
    m_thumbnailImage->setZ(0);
    m_assetDimmer->setZ(1);  // Updated z-index
    m_channelLogo->setZ(2);  // Updated z-index
    m_border->setZ(3);  // Border above channel logo
    m_elideFader->setZ(2);  // Same level as channel logo

    // Centralized positioning block - all positions relative to base coordinates
    m_thumbnailImage->setX(m_baseX);
    m_thumbnailImage->setY(m_baseY);
    
    m_border->setX(m_baseX);
    m_border->setY(m_baseY);
    m_border->setWidth(240);
    m_border->setHeight(135);
    
    m_title->setX(m_baseX + 8);
    m_title->setY(m_baseY + m_thumbnailImage->height() + 7);
    
    m_metadataRect->setX(m_baseX + 8);
    m_metadataRect->setY(m_baseY + 169);
    
    m_channelLogo->setX(m_baseX + 8);
    m_channelLogo->setY(m_baseY + 101);

    // Set initial visibility for border and metadata
    m_border->setVisible(false);
    m_metadataRect->setVisible(false);
}

void MenuAsset::createMetaDataRect()
{
    m_metadataRect = new QQuickItem(this);
    m_metadataRect->setParentItem(this);
    m_metadataRect->setWidth(231);
    m_metadataRect->setHeight(23);

    createLabelProgramInfo();
    createMetadataSeperator();
    createIconString();
}

void MenuAsset::createMetadataSeperator()
{
    m_metadataSeperator = new CustomTextPainter(this);
    m_metadataSeperator->setParentItem(m_metadataRect);
    m_metadataSeperator->setHeight(23);
    m_metadataSeperator->setWidth(14);
    
    QFont font("Regular");
    font.setPixelSize(18);
    m_metadataSeperator->setFont(font);
    
    m_metadataSeperator->setText(" \u00B7 ");
    m_metadataSeperator->setColor(QColor("#ebebeb"));
    m_metadataSeperator->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    
    // Position it after labelProgramInfo
    m_metadataSeperator->setX(m_labelProgramInfo->x() + m_labelProgramInfo->width());
    m_metadataSeperator->setY(0);
}

void MenuAsset::createLabelProgramInfo()
{
    m_labelProgramInfo = new CustomTextPainter(this);
    m_labelProgramInfo->setParentItem(m_metadataRect);
    m_labelProgramInfo->setHeight(23);
    
    QFont font("Gotham Narrow Book");
    font.setPixelSize(18);
    m_labelProgramInfo->setFont(font);
    
    m_labelProgramInfo->setText(m_assetModel["labelProgramInfo"].toString());
    m_labelProgramInfo->setColor(QColor("#ebebeb"));
    m_labelProgramInfo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    
    // Calculate width based on text content
    QFontMetrics fm(font);
    qreal textWidth = fm.width(m_labelProgramInfo->text());
    m_labelProgramInfo->setWidth(textWidth);
    
    m_labelProgramInfo->setX(0);
    m_labelProgramInfo->setY(0);
}

void MenuAsset::createIconString()
{
    m_iconString = new CustomTextPainter(this);
    m_iconString->setParentItem(m_metadataRect);
    m_iconString->setHeight(23);
    
    QFont font("Regular");
    font.setPixelSize(18);
    m_iconString->setFont(font);
    
    m_iconString->setText(m_assetModel["iconsString"].toString());
    m_iconString->setColor(QColor("#ebebeb"));
    m_iconString->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    
    // Calculate width based on text content
    QFontMetrics fm(font);
    qreal iconWidth = fm.width(m_iconString->text());
    m_iconString->setWidth(iconWidth);
    
    // Position relative to labelProgramInfo with 10px gap
    m_iconString->setX(m_metadataSeperator->x() + m_metadataSeperator->width());
    m_iconString->setY(0);
}

void MenuAsset::populateAssetTitle()
{
    QFont fontVar("Gotham Narrow Bold");
    fontVar.setPixelSize(20);
    
    m_title->setText(m_assetModel["title"].toString());
    m_title->setWidth(232);
    m_title->setHeight(24);
    m_title->setFont(fontVar);
    m_title->setColor(QColor("#ebebeb"));
    m_title->setAlignment(Qt::AlignLeft);
}

void MenuAsset::loadThumbnailImage()
{
    m_thumbnailImage->setWidth(240);
    m_thumbnailImage->setHeight(135);
    m_thumbnailImage->setCornerRadius(6);


    connect(m_imageLoader, &ImageLoader::imageLoaded, 
            [this](const QImage& image) {
        m_thumbnailImage->setImage(image);
    });
    
    connect(m_imageLoader, &ImageLoader::loadError,
            [](const QString& error) {
        qDebug() << "Image loading error:" << error;
    });
    
    m_imageLoader->loadFromUrl(m_assetModel["thumbnailUri"].toString());
}

void MenuAsset::createChannelLogo()
{
    // Initial placeholder size
    qreal maxWidth = 120;
    qreal maxHeight = 26;
    
    m_channelLogo->setWidth(maxWidth);
    m_channelLogo->setHeight(maxHeight);
    m_channelLogo->setVisible(true);
    m_channelLogo->setOpacity(1.0);
    
    connect(m_channelLogoLoader, &ImageLoader::imageLoaded, 
            [this, maxWidth, maxHeight](const QImage& image) {
        // Calculate aspect ratio preserving dimensions
        qreal aspectRatio = (qreal)image.width() / image.height();
        qreal newWidth = maxWidth;
        qreal newHeight = maxHeight;
        
        if (aspectRatio > (maxWidth / maxHeight)) {
            // Image is wider than placeholder - fit to width
            newWidth = maxWidth;
            newHeight = newWidth / aspectRatio;
        } else {
            // Image is taller than placeholder - fit to height
            newHeight = maxHeight;
            newWidth = newHeight * aspectRatio;
        }
        
        // Only center vertically, keep left alignment
        qreal yOffset = (maxHeight - newHeight) / 2;
        
        m_channelLogo->setWidth(newWidth);
        m_channelLogo->setHeight(newHeight);
        m_channelLogo->setX(m_baseX + 8);  // Always align left
        m_channelLogo->setY(m_baseY + 101 + yOffset);
        
        m_channelLogo->setImage(image);
        m_channelLogo->update();
    });
    
    connect(m_channelLogoLoader, &ImageLoader::loadError,
            [](const QString& error) {
        qDebug() << "Channel logo loading error:" << error;
    });
    
    m_channelLogoLoader->loadFromUrl(m_assetModel["regularChannelLogo"].toString());
}

void MenuAsset::createAssetDimmer()
{
    m_assetDimmer->setWidth(240);
    m_assetDimmer->setHeight(56);
    m_assetDimmer->setX(m_baseX);
    m_assetDimmer->setY(m_baseY + 79);
    
    connect(m_assetDimmerLoader, &ImageLoader::imageLoaded,
            [this](const QImage& image) {
        m_assetDimmer->setImage(image);
    });
    
    m_assetDimmerLoader->loadFromFile(":/images/assetDimmer.png");
}

void MenuAsset::createProgressBar()
{
    m_progressBar->setWidth(224);
    m_progressBar->setHeight(2);
    m_progressBar->setX(m_baseX + 8);
    m_progressBar->setY(m_baseY + 125);  // Position it above the assetDimmer
}

void MenuAsset::createElideFader()
{
    m_elideFader->setWidth(40);
    m_elideFader->setHeight(49);
    m_elideFader->setX(m_baseX + 200);  // 240 - 40 to position at right edge
    m_elideFader->setY(m_baseY + 143);  // 192 - 49 to position at bottom
    
    connect(m_elideFaderLoader, &ImageLoader::imageLoaded,
            [this](const QImage& image) {
        m_elideFader->setImage(image);
    });
    
    m_elideFaderLoader->loadFromFile(":/images/elideFader_40x49.png");
}

void MenuAsset::setFocused(bool focused)
{
    m_focused = focused;
    if (m_title) {
        m_title->setColor(focused ? QColor("#ebebeb") : QColor("#969696"));
    }
    
    // Show/hide border and metadata based on focus
    if (m_border) {
        m_border->setVisible(focused);
    }
    if (m_metadataRect) {
        m_metadataRect->setVisible(focused);
    }
}
