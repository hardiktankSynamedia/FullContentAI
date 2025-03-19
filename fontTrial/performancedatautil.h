#ifndef PERFORMANCEDATAUTIL_H
#define PERFORMANCEDATAUTIL_H

#include <QObject>
#include <QMap>
#include <QVector>

struct PerfData {
    QVector<qint64> timeData;
    double average;
};

class PerformanceDataUtil : public QObject
{
    Q_OBJECT

public:
    static PerformanceDataUtil* instance();
    void addPerfData(const QString& operationName, qint64 timeElapsed);
    QMap<QString, PerfData> m_perfMap;  // moved from private to public

signals:
    void perfDataChanged();

private:
    explicit PerformanceDataUtil(QObject *parent = nullptr);
};

#endif // PERFORMANCEDATAUTIL_H
