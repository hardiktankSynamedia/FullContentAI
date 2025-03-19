#include "imageloader.h"
#include <QFileInfo>
#include <QImageReader>
#include <QDebug>

ImageLoader::ImageLoader(QObject *parent) 
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &ImageLoader::handleNetworkReply);
}

ImageLoader::~ImageLoader()
{
}

void ImageLoader::loadFromFile(const QString& path)
{
    QFileInfo fileInfo(path);
    if (!fileInfo.exists()) {
        emit loadError("File does not exist: " + path);
        return;
    }

    QImageReader reader(path);
    m_loadedImage = reader.read();

    if (m_loadedImage.isNull()) {
        emit loadError("Failed to load image from file: " + reader.errorString());
        return;
    }

    emit imageLoaded(m_loadedImage);
}

void ImageLoader::loadFromUrl(const QString& url, bool modifyUrl)
{
    QString modifiedUrl = url;
    if (modifyUrl && modifiedUrl.startsWith("https://")) {
        modifiedUrl.replace(0, 5, "http");
    }

    QUrl qurl(modifiedUrl);
    if (!qurl.isValid()) {
        emit loadError("Invalid URL: " + url);
        return;
    }

    m_networkManager->get(QNetworkRequest(qurl));
}

void ImageLoader::handleNetworkReply(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit loadError("Network error: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray imageData = reply->readAll();
    m_loadedImage.loadFromData(imageData);

    if (m_loadedImage.isNull()) {
        emit loadError("Failed to create image from downloaded data");
    } else {
        emit imageLoaded(m_loadedImage);
    }

    reply->deleteLater();
}

QImage ImageLoader::getLoadedImage() const
{
    return m_loadedImage;
}
