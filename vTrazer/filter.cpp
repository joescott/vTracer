#include "filter.h"
#include "columnfilter.h"
#include "ui_filter.h"

Filter::Filter(ModelFilterDefinition *mfd, SessionManager *sessionManager,
                int type, QWidget *parent) :
    QFrame(parent),
    editAllow(false),
    ui(new Ui::Filter),
    enabled(false),
    type(type),
    sm(sessionManager)
{
    ui->setupUi(this);

    foreach(ModelFilterColumn mfc, mfd->columns)
    {
        ColumnFilter *cf = new ColumnFilter(sm->pm);
        cf->setFilterColIndex(mfc.index);
        cf->setFilterCaseSencitive(mfc.cs);
        cf->setRegExpStr(mfc.pattern);
        colFilters.append(cf);
        connect(cf,SIGNAL(columnfilterChanged()),
                sm,SLOT(filtersChanged()));
    }
    setToolTip(mfd->toolTip);

    for(int i = 0; i < colFilters.count(); ++i)
         ui->FilterFrame->layout()->addWidget(colFilters.at(i));

    enabled = true;
    editAllow = true;
}

Filter::~Filter()
{
    delete ui;
}

void Filter::setIndex(int idx)
{
    index = idx;
    ui->label->setText(QString("%1").arg(index));
}

void Filter::on_closeButton_clicked()
{
    emit deleteFilter(index);
}

void Filter::on_enable_toggled(bool checked)
{
    if(checked)
        ui->enable->setIcon(QIcon(":img/online"));
    else
        ui->enable->setIcon(QIcon(":img/offline"));

    enabled = checked;

    emit enableFilter(checked);
}

void Filter::filterEnable(bool status)
{
    ui->enable->setChecked(status);
    on_enable_toggled(status);
}
