#include "performancedatautil.h"
#include <QDebug>

PerformanceDataUtil::PerformanceDataUtil(QObject *parent) : QObject(parent)
{
}

PerformanceDataUtil* PerformanceDataUtil::instance()
{
    static PerformanceDataUtil* instance = new PerformanceDataUtil();
    return instance;
}

void PerformanceDataUtil::addPerfData(const QString& operationName, qint64 timeElapsed)
{
    PerfData& data = m_perfMap[operationName];
    data.timeData.append(timeElapsed);
    
    // Calculate average
    qint64 sum = 0;
    foreach(qint64 time, data.timeData) {
        sum += time;
    }
    data.average = static_cast<double>(sum) / data.timeData.size();
    
    qDebug() << "Performance Stats for" << operationName << ":";
    qDebug() << "  New time:" << timeElapsed << "ms";
    qDebug() << "  Average time:" << data.average << "ms";
    qDebug() << "  Total samples:" << data.timeData.size();
    
    emit perfDataChanged();
}
