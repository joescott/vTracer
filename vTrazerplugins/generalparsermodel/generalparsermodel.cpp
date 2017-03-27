#include <QtGui>
#include <QStandardItemModel>


#include "generalparsermodel.h"

QAbstractItemModel *GeneralParserModel::createModel(QWidget *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 2);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Data1"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Data2"));
    return model;
}

void GeneralParserModel::parseLine(QAbstractItemModel *model,QString line)
{
        model->insertRow(0);
        model->setData(model->index(0, 0), QString("%1").arg(model->rowCount()));
        model->setData(model->index(0, 1), line);
}

QStringList GeneralParserModel::getFiltersTypes()
{
    QStringList filters;
    filters << tr("Default") << tr("State");
    return filters;
}

ModelFilterDefinition GeneralParserModel::getFilter(int filterType)
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

ModelFilterDefinition::ModelFilterDefinition(){}


ModelWatchDefinition GeneralParserModel::getWatch(int watchType)
{
    ModelWatchDefinition mwd;
    switch(watchType)
    {
        case 0:
        default:
            mwd.toolTip = tr("Default Watch");
            ModelWatchColumn mwc;
            mwd.columns << mwc;
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


//Q_EXPORT_PLUGIN2(generalparsermodel, GeneralParserModel);
