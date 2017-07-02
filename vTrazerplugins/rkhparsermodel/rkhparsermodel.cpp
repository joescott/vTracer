#include <QtGui>

#include "rkhparsermodel.h"

QAbstractItemModel *RKHParserModel::createModel(QWidget *parent)
{
    Q_UNUSED(parent);
    QStandardItemModel *model = new QStandardItemModel(0, 9);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Timestamp"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sequence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Event"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Log"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("_id_type_FWK"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("_id_type_RQ"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("_id_type_SM"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("_id_type_OTHER"));

    return model;
}

void RKHParserModel::parseLine(QAbstractItemModel *model,QString line)
{
    int ncol =  model->rowCount();

    QRegularExpression re_gen("\\s*(\\d*)\\|.*\\[\\s*(\\d*)\\]\\s*\\|\\s*(.*)\\s*\\|\\s*(.*)\\s*:\\s*(.*)");
    QRegularExpressionMatch match_gen = re_gen.match(line);
    if(match_gen.hasMatch())
    {
        model->insertRow(ncol);
        model->setData(model->index(ncol, 0), match_gen.captured(1));
        model->setData(model->index(ncol, 1), match_gen.captured(2));
        model->setData(model->index(ncol, 2), match_gen.captured(3));
        model->setData(model->index(ncol, 3), match_gen.captured(4));


        model->setData(model->index(ncol, 4), match_gen.captured(5));
#if 1
            model->setData(model->index(ncol, 5), -1);
            model->setData(model->index(ncol, 6), -1);
            model->setData(model->index(ncol, 7), -1);
            model->setData(model->index(ncol, 8), -1);
#endif
        if(match_gen.captured(3).contains("FWK"))
        {
            model->setData(model->index(ncol, 5), 1.5);
        }else if(match_gen.captured(3).contains("RQ"))
            model->setData(model->index(ncol, 6), 2.5);
        else if(match_gen.captured(3).contains("SM"))
            model->setData(model->index(ncol, 7), 3.5);
        else
            model->setData(model->index(ncol, 8), 0.5);
        return;
    }
#if 1
    QRegularExpression re_conf("\\s+\\|\\s+(.*)\\s+");
    QRegularExpressionMatch match_conf = re_conf.match(line);
    if(match_conf.hasMatch())
    {
        QVariant data = model->data(model->index(ncol-1, 4));
        QString a = match_conf.captured(0);
        QString b = match_conf.captured(1);
        data = data.toString().append("\n");
        data = data.toString().append(match_conf.captured(1));
        model->setData(model->index(ncol-1, 4),data);
        return;
    }
    QRegularExpression re_end_conf("^\\s*$");
    QRegularExpressionMatch match_end_conf = re_end_conf.match(line);
    if(match_end_conf.hasMatch())
    {
        return;
    }
#endif
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
