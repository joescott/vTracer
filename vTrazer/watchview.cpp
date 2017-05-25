#include "watchview.h"
#include "ui_watchview.h"

#include <QStandardItemModel>
#include <QDateTime>


WatchView::WatchView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatchView)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(0, 4);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TriggerTime"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Input"));

    wm = model;
    ui->watchView->setModel(model);
    ui->watchView->setColumnWidth(0,70);
    ui->watchView->setColumnWidth(1,160);
    //ui->watchView->setColumnHidden(2,true);

    connect(ui->watchView,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(on_watchClicked(QModelIndex)));

}

WatchView::~WatchView()
{
    delete ui;
}

void WatchView::on_watchClicked(QModelIndex index)
{
    //sMap a = wm->itemData(index);
    QVariant a = wm->index(index.row(),2).data();
    emit watchSelected(a.toInt());
}

void WatchView::addAlarm(QAbstractItemModel *sm, int row)
{
    Q_UNUSED(sm);
    QDateTime local(QDateTime::currentDateTime());
    int ncol =  wm->rowCount();
    wm->insertRow(ncol);
    wm->setData(wm->index(ncol, 0),ncol);
    wm->setData(wm->index(ncol, 1),local.toString("yyyy/MM/dd HH:mm:ss.zzz"));
    wm->setData(wm->index(ncol, 2),row);
    wm->setData(wm->index(ncol, 3),row);
}
