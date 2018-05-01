#include "macdchart.h"
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
#include <QtCharts/QLegendMarker>
#include <QtCharts/QXYLegendMarker>
#include <QtCore/QtMath>
#include <QtCharts/QChart>
#include <QtWidgets/QLabel>
#include <QtCore/QDebug>
#include <QtCharts/QLegend>
#include <QtWidgets/QFormLayout>
#include <QtCore/QtMath>


QT_CHARTS_USE_NAMESPACE

MACDChart::MACDChart() {
    macd_chart = new QChart();
    macd_chart->setTitle("Daily stock data");
    macd_chart->legend()->setVisible(true);
}

void MACDChart::addSeries(QLineSeries *series) {
    macd_chart->addSeries(series);
}

void MACDChart::addAxis(QAbstractAxis *axis, Qt::Alignment alignment) {
    macd_chart->addAxis(axis, alignment);
}

QChart* MACDChart::returnChart() {
    return macd_chart;
}

void MACDChart::connectMarkers() {
    // Connect all markers to handler
    const auto markers = macd_chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked, this, &MACDChart::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, &MACDChart::handleMarkerClicked);

        marker->setVisible(true);

        // Dim the marker if the series is currently not visible
        qreal alpha = 1.0;

        if (!marker->series()->isVisible())
            alpha = 0.5;

        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush);

        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush);

        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);

    }

}

void MACDChart::disconnectMarkers()
{
    const auto markers = macd_chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        QObject::disconnect(marker, &QLegendMarker::clicked, this, &MACDChart::handleMarkerClicked);
    }
}


void MACDChart::handleMarkerClicked() {
        QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
        Q_ASSERT(marker);

        switch (marker->type())
        {
            case QLegendMarker::LegendMarkerTypeXY:
            {
            // upon button click, toggle visibility of series
            marker->series()->setVisible(!marker->series()->isVisible());

            // turn marker on legend back to visible
            marker->setVisible(true);

            // Dim the marker, if series is not visible
            qreal alpha = 1.0;

            if (!marker->series()->isVisible())
                alpha = 0.5;

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);

            break;
            }
        default:
            {
            qDebug() << "Unknown marker type";
            break;
            }
        }

}
