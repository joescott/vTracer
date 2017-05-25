#include <QtGui>

#include "rkhparsermodel.h"

QAbstractItemModel *RKHParserModel::createModel(QWidget *parent)
{
    Q_UNUSED(parent);
    QStandardItemModel *model = new QStandardItemModel(0, 5);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Timestamp"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sequence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Event"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Log"));


    return model;
}

void RKHParserModel::parseLine(QAbstractItemModel *model,QString line)
{
    int ncol =  model->rowCount();

    QRegularExpression re("\\s*(\\d*)\\|.*\\[\\s*(\\d*)\\]\\s*\\|\\s*(.*)\\s*\\|\\s*(.*)\\s*:\\s*(.*)");
    QRegularExpressionMatch match = re.match(line);
    if (match.hasMatch()) {
        model->insertRow(ncol);
        model->setData(model->index(ncol, 0), match.captured(1));
        model->setData(model->index(ncol, 1), match.captured(2));
        model->setData(model->index(ncol, 2), match.captured(3));
        model->setData(model->index(ncol, 3), match.captured(4));
        model->setData(model->index(ncol, 4), match.captured(5));
    }
}

QStringList RKHParserModel::getFiltersTypes()
{
    QStringList filters;
    filters << tr("Default") << tr("FWK OBJ");
    return filters;
}

ModelFilterDefinition RKHParserModel::getFilter(int filterType)
{
    ModelFilterDefinition mfd;
    ModelFilterColumn mfc[2];
    switch(filterType)
    {
    case (int)RKHFilterTypes::FWK_OBJ:
        mfd.toolTip = tr("FWK OBJ");
        mfc[0].index 	= 2;
        mfc[0].pattern = "FWK";
        mfc[1].index 	= 3;
        mfc[1].pattern = "OBJ";
        mfd.columns << mfc[0] << mfc[1];
        break;
    case (int)RKHFilterTypes::DEFAULT:
    default:
        mfd.toolTip = tr("Default Filter");
        mfd.columns << mfc[0];
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
