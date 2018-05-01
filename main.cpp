#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCharts/QValueAxis>
#include <QVector>
#include "common.h"
#include "macdchart.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineSeries *rawData = new QLineSeries();
    QLineSeries *movingAvg9Data = new QLineSeries();
    QLineSeries *movingAvg12Data = new QLineSeries();
    QLineSeries *movingAvg26Data = new QLineSeries();
    QLineSeries *macd = new QLineSeries();
    QLineSeries *difference = new QLineSeries();

    QVector<double> closingValues;
    QVector<double> emaDifference;

    QFile daily(":data");
    if (!daily.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    QTextStream stream(&daily);

    int numDataPoints = 0;

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.startsWith("t"))
            continue;
        QRegExp rx("(\\,|\\/)");
        QStringList values = line.split(rx, QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[2].toInt(), values[0].toInt() , values[1].toInt()));

        // append new value to closingValues vector
        closingValues.append(values[6].toDouble());

        // calculate moving average sets
        calculate_MAvg(movingAvg9Data, closingValues, SUBSET_SIZE_9, momentInTime);
        calculate_MAvg(movingAvg12Data, closingValues, SUBSET_SIZE_12, momentInTime);
        calculate_MAvg(movingAvg26Data, closingValues, SUBSET_SIZE_26, momentInTime);

        rawData->append(momentInTime.toMSecsSinceEpoch(), values[6].toDouble());

        numDataPoints++;
    }

    daily.close();

    QFile daily2(":data");
    if (!daily2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    QTextStream stream2(&daily2);

    numDataPoints = 0;

    while (!stream2.atEnd()) {
        QString line = stream2.readLine();
        if (line.startsWith("t"))
            continue;
        QRegExp rx("(\\,|\\/)");
        QStringList values = line.split(rx, QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[2].toInt(), values[0].toInt() , values[1].toInt()));

        if (numDataPoints >= SUBSET_SIZE_26) {
            emaDifference.append(movingAvg12Data->at(numDataPoints).y() - movingAvg26Data->at(numDataPoints).y());
            difference->append(momentInTime.toMSecsSinceEpoch(), movingAvg12Data->at(numDataPoints).y() - movingAvg26Data->at(numDataPoints).y());
        } else {
            emaDifference.append(0.0);
            difference->append(momentInTime.toMSecsSinceEpoch(), 0.0);
        }


        // calculate moving average sets
        calculate_MAvg(macd, emaDifference, SUBSET_SIZE_9, momentInTime);

        numDataPoints++;
    }

    daily2.close();

    // create chart and add data sets
    MACDChart emaChart;
    rawData->setName("Daily Stock Data");
    movingAvg9Data->setName("9-Day EMA");
    movingAvg12Data->setName("12-Day EMA");
    movingAvg26Data->setName("26-Day EMA");
    emaChart.addSeries(rawData);
    emaChart.addSeries(movingAvg9Data);
    emaChart.addSeries(movingAvg12Data);
    emaChart.addSeries(movingAvg26Data);
    movingAvg9Data->setVisible(false);
    movingAvg12Data->setVisible(false);
    movingAvg26Data->setVisible(false);

    emaChart.connectMarkers();

    // attach x values of data sets to x axis of chart
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MM/dd/yy");
    axisX->setTitleText("Date");
    emaChart.addAxis(axisX, Qt::AlignBottom);
    rawData->attachAxis(axisX);
    movingAvg9Data->attachAxis(axisX);
    movingAvg12Data->attachAxis(axisX);
    movingAvg26Data->attachAxis(axisX);

    // attach y values of data sets to y axis of chart
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Closing value");
    emaChart.addAxis(axisY, Qt::AlignLeft);
    rawData->attachAxis(axisY);
    movingAvg9Data->attachAxis(axisY);
    movingAvg12Data->attachAxis(axisY);
    movingAvg26Data->attachAxis(axisY);

    QChartView *chartViewEMA = new QChartView(emaChart.returnChart());
    chartViewEMA->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartViewEMA);
    window.resize(820, 600);
    window.show();

    // create MACD chart
    MACDChart macdChart;
    macd->setName("Signal line");
    difference->setName("MACD");
    macdChart.addSeries(macd);
    macdChart.addSeries(difference);

    macdChart.connectMarkers();

    // attach x values of macd data set to x axis
    QDateTimeAxis *axisXMACD = new QDateTimeAxis;
    axisXMACD->setTickCount(10);
    axisXMACD->setFormat("MM/dd/yy");
    axisXMACD->setTitleText("Date");
    macdChart.addAxis(axisXMACD, Qt::AlignBottom);
    difference->attachAxis(axisXMACD);
    macd->attachAxis(axisXMACD);

    // attach y values of macd data set to y axis
    QValueAxis *axisYMACD = new QValueAxis;
    axisYMACD->setLabelFormat("%i");
    axisYMACD->setTitleText("MACD");
    macdChart.addAxis(axisYMACD, Qt::AlignLeft);
    difference->attachAxis(axisYMACD);
    macd->attachAxis(axisYMACD);

    QChartView *chartViewMACD = new QChartView(macdChart.returnChart());
    chartViewMACD->setRenderHint(QPainter::Antialiasing);

    QMainWindow window2;
    window2.setCentralWidget(chartViewMACD);
    window2.resize(800, 590);
    window2.show();

    return a.exec();
}


