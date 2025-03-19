#ifndef PERFORMANCELOGGER_H
#define PERFORMANCELOGGER_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <QString>
#include <QDateTime>

struct PerfStruct {
    QDateTime startTime;
    QDateTime endTime;
    qint64 getElapsedMs() const {
        return startTime.msecsTo(endTime);
    }
};

class PerformanceLogger : public QObject
{
    Q_OBJECT
public:
    static PerformanceLogger* instance();
    void startOperation(const QString& operationName);
    void endOperation(const QString& operationName);
    virtual ~PerformanceLogger();

public slots:
    void clearLogs();

private:
    explicit PerformanceLogger(QObject *parent = nullptr);
    
    QTimer* m_flushTimer;
    QMap<QString, PerfStruct> m_activeOperations;
    QMap<QString, qint64> m_completedOperations;
    
    static constexpr int FLUSH_TIMEOUT = 3000; // 10 seconds
};

#endif // PERFORMANCELOGGER_H
