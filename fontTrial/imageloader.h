#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

class ImageLoader : public QObject
{
    Q_OBJECT

public:
    explicit ImageLoader(QObject *parent = nullptr);
    ~ImageLoader();

    void loadFromFile(const QString& path);
    void loadFromUrl(const QString& url, bool modifyUrl = false);
    QImage getLoadedImage() const;

signals:
    void imageLoaded(const QImage& image);
    void loadError(const QString& errorMessage);

private slots:
    void handleNetworkReply(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_networkManager;
    QImage m_loadedImage;
};

#endif // IMAGELOADER_H
