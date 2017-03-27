#include "watchmodel.h"

WatchModel::WatchModel()
{
}


QAbstractItemModel *WatchModel::createWatchModel(QWidget *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 4);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Data2"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Data3"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Data4"));

    return model;
}


