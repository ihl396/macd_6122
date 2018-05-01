#ifndef MACDCHART_H
#define MACDCHART_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class MACDChart : public QWidget
{
    Q_OBJECT
public:
    explicit MACDChart();

public slots:
    void addSeries(QLineSeries *);
    void addAxis(QAbstractAxis *, Qt::Alignment);
    QChart* returnChart();
    void connectMarkers();
    void disconnectMarkers();
    void handleMarkerClicked();

private:
    QChart *macd_chart;

};


#endif // MACDCHART_H
