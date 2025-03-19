#ifndef MENUASSET_H
#define MENUASSET_H

#include <QQuickItem>
#include <QJsonObject>
#include "customtextpainter.h"
#include "imageloader.h"
#include "imagedisplay.h"
#include "progressbar.h"
#include "border.h"

class MenuAsset : public QQuickItem
{
    Q_OBJECT
public:
    explicit MenuAsset(const QJsonObject& assetModel, QQuickItem *parent = nullptr);
    void setFocused(bool focused);

private:
    void populateAssetTitle();
    void loadThumbnailImage();
    void createMetaDataRect();
    void createLabelProgramInfo();
    void createIconString();
    void createMetadataSeperator();
    void createChannelLogo();
    void createAssetDimmer();
    void createProgressBar();
    void createElideFader();
    
    QJsonObject m_assetModel;
    CustomTextPainter* m_title;
    ImageLoader* m_imageLoader;
    ImageDisplay* m_thumbnailImage;
    QQuickItem* m_metadataRect;
    qreal m_baseX;
    qreal m_baseY;
    CustomTextPainter* m_labelProgramInfo;
    CustomTextPainter* m_iconString;
    CustomTextPainter* m_metadataSeperator;
    ImageLoader* m_channelLogoLoader;
    ImageDisplay* m_channelLogo;
    ImageLoader* m_assetDimmerLoader;
    ImageDisplay* m_assetDimmer;
    ProgressBar* m_progressBar;
    Border* m_border;
    ImageLoader* m_elideFaderLoader;
    ImageDisplay* m_elideFader;
    bool m_focused = false;
};

#endif // MENUASSET_H
