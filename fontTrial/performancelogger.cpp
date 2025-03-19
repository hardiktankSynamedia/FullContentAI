#include "performancelogger.h"
#include "performancedatautil.h"
#include <QDebug>

PerformanceLogger::PerformanceLogger(QObject *parent) : QObject(parent)
{
    m_flushTimer = new QTimer(this);
    m_flushTimer->setSingleShot(true);
    connect(m_flushTimer, &QTimer::timeout, this, &PerformanceLogger::clearLogs);
}

// Fix destructor definition
PerformanceLogger::~PerformanceLogger() 
{
    if (m_flushTimer) {
        delete m_flushTimer;
        m_flushTimer = nullptr;
    }
    clearLogs();
}

PerformanceLogger* PerformanceLogger::instance()
{
    static PerformanceLogger* instance = new PerformanceLogger();
    return instance;
}

void PerformanceLogger::startOperation(const QString& operationName)
{
    PerfStruct perfData;
    perfData.startTime = QDateTime::currentDateTime();
    m_activeOperations[operationName] = perfData;
    
    // Always restart timer when new operation is added
    if (m_flushTimer->isActive()) {
        m_flushTimer->stop();
    }
    m_flushTimer->start(FLUSH_TIMEOUT);
}

void PerformanceLogger::endOperation(const QString& operationName)
{
    if (!m_activeOperations.contains(operationName)) {
        qDebug() << "Warning: No matching start operation found for" << operationName;
        return;
    }
    
    PerfStruct& perfData = m_activeOperations[operationName];
    perfData.endTime = QDateTime::currentDateTime();
    qint64 elapsed = perfData.getElapsedMs();
    
    m_completedOperations[operationName] = elapsed;
    m_activeOperations.remove(operationName);
}

// Move clearLogs to public slot
void PerformanceLogger::clearLogs()
{
    if (!m_activeOperations.isEmpty()) {
        qDebug() << "Warning: Some operations did not complete:" << m_activeOperations.keys();
    }
    
    QMapIterator<QString, qint64> it(m_completedOperations);
    while (it.hasNext()) {
        it.next();
        qDebug() << "Performance:" << it.key() << "took" << it.value() << "ms";
        PerformanceDataUtil::instance()->addPerfData(it.key(), it.value());
    }
    
    m_activeOperations.clear();
    m_completedOperations.clear();
    
    if (m_flushTimer && m_flushTimer->isActive()) {
        m_flushTimer->stop();
    }
}
