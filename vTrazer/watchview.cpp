#include "watchview.h"
#include "ui_watchview.h"

#include <QStandardItemModel>
#include <QDateTime>


WatchView::WatchView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatchView)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(0, 3);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TriggerTime"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("line"));

    wm = model;
    ui->watchView->setModel(model);
}

WatchView::~WatchView()
{
    delete ui;
}

void WatchView::addAlarm(QVariant data)
{
    QDateTime local(QDateTime::currentDateTime());
    int ncol =  wm->rowCount();
    wm->insertRow(ncol);
    wm->setData(wm->index(ncol, 0),ncol);
    wm->setData(wm->index(ncol, 1),local.toString("yyyy/MM/dd HH:mm:ss.zzz"));
    wm->setData(wm->index(ncol, 2),data);
}
