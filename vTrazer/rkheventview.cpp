#include "rkheventview.h"
#include <QtGui/QResizeEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QGraphicsTextItem>
#include "callout.h"
#include <QVXYModelMapper>
#include <QCategoryAxis>
#include <QtGui/QMouseEvent>
#include <QtCharts/QScatterSeries>
#include <QMutableListIterator>
#include "eventserie.h"

RKHEventView::RKHEventView(SessionManager *sm, QWidget *parent)
    : QGraphicsView(new QGraphicsScene, parent),
      m_coordX(0),
      m_coordY(0),
      m_chart(0),
      m_tooltip(0),
      m_sm(sm)
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Order by max value
    m_series.append( new EventSerie("Other",	QColor("gray"),  0, 1, 8));
    m_series.append( new EventSerie("FWK", 		QColor("red"), 	 1, 2, 5));
    m_series.append( new EventSerie("RQ", 		QColor("blue"),  2, 3, 6));
    m_series.append( new EventSerie("SM", 		QColor("green"), 3, 4, 7));

    m_chart = new QChart;
    //m_chart->setMinimumSize(640, 480);
    m_chart->setTitle(tr("Events"));

    QCategoryAxis *axisY = new QCategoryAxis();
    QValueAxis *axisX = new QValueAxis();
    EventSerie *evt_serie;
    int min_range = 100;
    int max_range = -100;
#if 1
    foreach(evt_serie, m_series)
    {
        evt_serie->serie = new QScatterSeries(m_chart);
        evt_serie->serie->setName(evt_serie->name);
        evt_serie->serie->setColor(evt_serie->color);
        evt_serie->serie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        evt_serie->serie->setMarkerSize(10.0);
        evt_serie->mapper = new QVXYModelMapper(m_chart);
        evt_serie->mapper->setXColumn(0);
        evt_serie->mapper->setYColumn(evt_serie->idx);
        evt_serie->mapper->setModel(sm->pm);
        evt_serie->mapper->setSeries(evt_serie->serie);
        m_chart->addSeries(evt_serie->serie);
        m_chart->setAxisY(axisY, evt_serie->serie);
        m_chart->setAxisX(axisX, evt_serie->serie);
        axisY->append(evt_serie->name, evt_serie->max);
        if(evt_serie->max > max_range)
            max_range = evt_serie->max;
        if(evt_serie->min < min_range)
            min_range = evt_serie->min;
    }
#endif
    //m_chart->createDefaultAxes();

    axisY->setRange(min_range, max_range);
    // Customize axis colors
    //QPen axisPen(QRgb(0xd18952));
    //axisPen.setWidth(2);
    //axisX->setLinePen(axisPen);
    //axisY->setLinePen(axisPen);
    m_chart->setAnimationOptions(QChart::AllAnimations);

    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(m_chart);

    m_coordX = new QGraphicsSimpleTextItem(m_chart);
    m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height());
    m_coordX->setText("X: ");
    m_coordY = new QGraphicsSimpleTextItem(m_chart);
    m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height());
    m_coordY->setText("Y: ");

#if 1
   foreach(evt_serie, m_series)
   {
       connect(evt_serie->serie, SIGNAL(clicked(QPointF)), this, SLOT(keepCallout(QPointF)));
       connect(evt_serie->serie, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));
   }
#endif
   connect(sm->pm,SIGNAL(rowsInserted(QModelIndex,int,int)),
            this,SLOT(up(QModelIndex,int,int)));

    this->setMouseTracking(true);
}

void RKHEventView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        m_chart->zoomIn();
        break;
    case Qt::Key_Minus:
        m_chart->zoomOut();
        break;
    case Qt::Key_Left:
        m_chart->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        m_chart->scroll(10, 0);
        break;
    case Qt::Key_Up:
        m_chart->scroll(0, 10);
        break;
    case Qt::Key_Down:
        m_chart->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }

}

void RKHEventView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         m_chart->resize(event->size());
         m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 20);
         m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);
         foreach (Callout *callout, m_callouts)
             callout->updateGeometry();
    }
    QGraphicsView::resizeEvent(event);
}

void RKHEventView::mouseMoveEvent(QMouseEvent *event)
{
    m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos()).x()));
    m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);
}

void RKHEventView::keepCallout(QPointF point)
{
    m_tooltip = new Callout(m_chart);
    m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
    m_tooltip->setAnchor(point);
    m_tooltip->setZValue(11);
    m_tooltip->updateGeometry();
    m_tooltip->show();
    m_callouts.append(m_tooltip);
}

void RKHEventView::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chart);

    if (state) {
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}

void RKHEventView::up(QModelIndex parent /* unused */, int first, int last/* unused */)
{
    Q_UNUSED(parent);
    Q_UNUSED(last);
    int column = 0;
    QModelIndex idx = m_sm->pm->index(first-1,column);
    QVariant data = idx.data(Qt::DisplayRole);
    m_chart->axisX()->setMax(data);
}
