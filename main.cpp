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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineSeries *rawData = new QLineSeries();
    QLineSeries *movingAvg9Data = new QLineSeries();
    QLineSeries *movingAvg12Data = new QLineSeries();
    QLineSeries *movingAvg26Data = new QLineSeries();

    QVector<double> closingValues;

    QFile daily(":data");
    if (!daily.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    QTextStream stream(&daily);

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

        // calculate MACD sets
        calculate_MACD(movingAvg9Data, closingValues, SUBSET_SIZE_9, momentInTime);
        calculate_MACD(movingAvg12Data, closingValues, SUBSET_SIZE_12, momentInTime);
        calculate_MACD(movingAvg26Data, closingValues, SUBSET_SIZE_26, momentInTime);

        rawData->append(momentInTime.toMSecsSinceEpoch(), values[6].toDouble());
    }
    daily.close();

    // create chart and add data sets
    QChart *chart = new QChart();
    rawData->setName("Daily Stock Data");
    movingAvg9Data->setName("Subset Size 9 MACD");
    movingAvg12Data->setName("Subset Size 12 MACD");
    movingAvg26Data->setName("Subset Size 26 MACD");
    chart->addSeries(rawData);
    chart->addSeries(movingAvg9Data);
    chart->addSeries(movingAvg12Data);
    chart->addSeries(movingAvg26Data);
    chart->setTitle("Daily stock data");
    chart->legend()->setVisible(true);

    // attach x values of data sets to x axis of chart
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MM/dd/yy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    rawData->attachAxis(axisX);
    movingAvg9Data->attachAxis(axisX);
    movingAvg12Data->attachAxis(axisX);
    movingAvg26Data->attachAxis(axisX);

    // attach y values of data sets to y axis of chart
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Closing value");
    chart->addAxis(axisY, Qt::AlignLeft);
    rawData->attachAxis(axisY);
    movingAvg9Data->attachAxis(axisY);
    movingAvg12Data->attachAxis(axisY);
    movingAvg26Data->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(820, 600);
    window.show();

    return a.exec();
}


