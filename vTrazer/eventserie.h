#ifndef EVENTSERIE_H
#define EVENTSERIE_H

#include <QtCharts/QScatterSeries>
#include <QVXYModelMapper>

QT_CHARTS_BEGIN_NAMESPACE
class QScatterSeries;
class QVXYModelMapper;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class EventSerie
{
public:
    EventSerie(QString lname,QColor lcolor,int lmin, int lmax, int lidx){
        name = lname;
        color = lcolor;
        min = lmin;
        max = lmax;
        idx = lidx;
    }

    QScatterSeries *serie;
    QString name;
    QColor color;
    QVXYModelMapper *mapper;
    int min;
    int max;
    int idx;
};

#endif // EVENTSERIE_H
