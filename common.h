#ifndef COMMON_H
#define COMMON_H

#include <QtCharts/QLineSeries>
#include <QVector>
#include <QtCore/QDateTime>

QT_CHARTS_USE_NAMESPACE

int SUBSET_SIZE_9 = 9;
int SUBSET_SIZE_12 = 12;
int SUBSET_SIZE_26 = 26;

void calculate_MACD(QLineSeries *movingAvgData, QVector<double> rawData, int subsetSize, QDateTime momentInTime) {
    // if number of data points in rawData is less than subset size, set value in MACD series to 0
    if (rawData.size() < subsetSize) {
        movingAvgData->append(momentInTime.toMSecsSinceEpoch(), 0.0);
    } else {
        // calculate MACD value for current MACD point if number of data points is greater than subset size
        double sum = 0;
        for (int i = rawData.size() - subsetSize; i < rawData.size(); i++) {
            sum += rawData[i];
        }
        double avg = sum/subsetSize;
        movingAvgData->append(momentInTime.toMSecsSinceEpoch(), avg);
    }
}

#endif // COMMON_H
