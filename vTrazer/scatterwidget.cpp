#include "scatterwidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QVXYModelMapper>
#include <QCategoryAxis>

ScatterWidget::ScatterWidget(SessionManager *sm,QWidget *parent) :
    QWidget(parent),
    m_sm(sm)
{

    connectSignals();
    // create layout
    QGridLayout *baseLayout = new QGridLayout();

    QChart *chart = new QChart();
    chart->setTitle(tr("Events"));

    QScatterSeries *series0 = new QScatterSeries(chart);
    series0->setName("FWK");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(10.0);

    QVXYModelMapper *mapper0 = new QVXYModelMapper(this);
    mapper0->setXColumn(0);
    mapper0->setYColumn(5);
    mapper0->setModel(sm->pm);
    mapper0->setSeries(series0);

    QScatterSeries *series1 = new QScatterSeries(chart);
    series1->setName("RQ");
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series1->setMarkerSize(10.0);

    QVXYModelMapper *mapper1 = new QVXYModelMapper(this);
    mapper1->setXColumn(0);
    mapper1->setYColumn(6);
    mapper1->setModel(sm->pm);
    mapper1->setSeries(series1);

    QScatterSeries *series2 = new QScatterSeries(chart);
    series2->setName("SM");
    series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series2->setMarkerSize(10.0);

    QVXYModelMapper *mapper2 = new QVXYModelMapper(this);
    mapper2->setXColumn(0);
    mapper2->setYColumn(7);
    mapper2->setModel(sm->pm);
    mapper2->setSeries(series2);

    QScatterSeries *series3 = new QScatterSeries(chart);
    series3->setName("Others");
    series3->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series3->setMarkerSize(10.0);

    QVXYModelMapper *mapper3 = new QVXYModelMapper(this);
    mapper3->setXColumn(0);
    mapper3->setYColumn(8);
    mapper3->setModel(sm->pm);
    mapper3->setSeries(series3);

    chart->addSeries(series0);
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);

#if 0
    // Customize plot area background
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
    plotAreaGradient.setColorAt(1.0, QRgb(0xB9B9B9));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);
#endif
    QCategoryAxis *axisY = new QCategoryAxis();
    axisY->append("E1", 1);
    axisY->append("E2", 2);
    axisY->append("E3", 3);
    axisY->append("E4", 4);

    axisY->setRange(0, 4);
#if 0
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
    axisY->setShadesVisible(true);
#endif
    chart->createDefaultAxes();
    chart->setAxisY(axisY, series0);
    chart->setAxisY(axisY, series1);
    chart->setAxisY(axisY, series2);
    chart->setAxisY(axisY, series3);
    chart->setAnimationOptions(QChart::AllAnimations);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

   connect(sm->pm,SIGNAL(rowsInserted(QModelIndex,int,int)),
            this,SLOT(up(QModelIndex,int,int)));

    baseLayout->addWidget(chartView);

    setLayout(baseLayout);

}

ScatterWidget::~ScatterWidget()
{
}

void ScatterWidget::connectSignals()
{
    /*
    connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_antialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_animatedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_legendComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    */
}

void ScatterWidget::up(QModelIndex parent, int first, int last)
{
    int column = 0;
    QModelIndex idx = m_sm->pm->index(first-1,column);
    QVariant data = idx.data(Qt::DisplayRole);
    chartView->chart()->axisX()->setMax(data);
}

