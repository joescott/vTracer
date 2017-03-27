#include <QtGui>

#include "rkhparsermodel.h"

QAbstractItemModel *RKHParserModel::createModel(QWidget *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 4);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Data2"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Data3"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Data4"));

    return model;
}

void RKHParserModel::parseLine(QAbstractItemModel *model,QString line)
{
    int ncol =  model->rowCount();
    model->insertRow(ncol);
    model->setData(model->index(ncol, 0),ncol);
    model->setData(model->index(ncol, 1), QString("%1").arg(model->rowCount()));
    model->setData(model->index(ncol, 2), line.trimmed());
    model->setData(model->index(ncol, 3), "data");
    /**TEST*/
    QRegExp rxlen("(\\d+)(?:\\s*)(cm|inch)");
    int pos = rxlen.indexIn("Length: 189cm");
    if (pos > -1) {
        QString value = rxlen.cap(1); // "189"
        QString unit = rxlen.cap(2);  // "cm"
        //qDebug()  << pos << unit << value;
    }

}

QStringList RKHParserModel::getFiltersTypes()
{
    QStringList filters;
    filters << tr("Default") << tr("State");
    return filters;
}

ModelFilterDefinition RKHParserModel::getFilter(int filterType)
{
    ModelFilterDefinition mfd;
    switch(filterType)
    {
        case 0:
        default:
            mfd.toolTip = tr("Default Filter");
            ModelFilterColumn mfc;
            mfd.columns << mfc;
            break;
    }
    return mfd;
}

ModelFilterDefinition::ModelFilterDefinition()
{
}

ModelFilterColumn::ModelFilterColumn()
{

    enabled     = true;
    hide        = false;
    index       = 0;
    indexFixed  = false;
    pattern     = "";
    cs          = false;
}

ModelWatchDefinition RKHParserModel::getWatch(int watchType)
{
    ModelWatchDefinition mwd;
    switch(watchType)
    {
        case 0:
        default:
            mwd.toolTip = tr("Default Watch");
            ModelWatchColumn mwc;
            mwd.columns << mwc;
            mwd.action = QString("note");
            break;
    }
    return mwd;
}

ModelWatchDefinition::ModelWatchDefinition(){}

ModelWatchColumn::ModelWatchColumn()
{

    enabled     = true;
    hide        = false;
    index       = 0;
    indexFixed  = false;
    pattern     = "";
    cs          = false;
}


//Q_EXPORT_PLUGIN2(rkhparsermodel, RKHParserModel)
