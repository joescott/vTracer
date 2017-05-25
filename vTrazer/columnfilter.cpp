#include "columnfilter.h"
#include "ui_columnfilter.h"

ColumnFilter::ColumnFilter(QAbstractProxyModel *proxyModel,
                           QString regStr, int colIndex, bool cs,
                           QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ColumnFilter),
    pm(proxyModel)
{
    ui->setupUi(this);

    fillFilterColFromModel(proxyModel);

    setFilterColIndex(colIndex);
    setRegExpStr(regStr);
    setFilterCaseSencitive(cs);
}

ColumnFilter::~ColumnFilter()
{
    delete ui;
}

void ColumnFilter::fillFilterColFromModel(QAbstractProxyModel *model)
{
    if(ui->FilterColumn->count() != 0)
        ui->FilterColumn->clear();

    for(int i=0; i < model->columnCount(); ++i)
        ui->FilterColumn->addItem(
                    model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
}

bool ColumnFilter::getFilterCaseSencitive()
{
    return ui->CaseSencitive->isChecked();
}

void ColumnFilter::setFilterCaseSencitive(bool status)
{
    ui->CaseSencitive->setChecked(status);
}

int ColumnFilter::getFilterColIndex()
{
    return ui->FilterColumn->currentIndex();
}

void ColumnFilter::setFilterColIndex(int index)
{
    ui->FilterColumn->setCurrentIndex(index);
}

QString ColumnFilter::getRegExpStr()
{
    return ui->RegExp->text();
}

void ColumnFilter::setRegExpStr(QString regexp)
{
    ui->RegExp->blockSignals(true);
    ui->RegExp->setText(regexp);
    ui->RegExp->blockSignals(false);
}

void ColumnFilter::on_RegExp_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit columnfilterChanged();
}

void ColumnFilter::on_FilterColumn_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    emit columnfilterChanged();
}

void ColumnFilter::on_CaseSencitive_clicked(bool checked)
{
    Q_UNUSED(checked);
    emit columnfilterChanged();
}
