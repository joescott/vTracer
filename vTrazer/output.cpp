#include "output.h"
#include "def.h"
#include "ui_output.h"

//#include "qtsvgdialgauge.h"

Output::Output(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Output)
{
    ui->setupUi(this);

    ui->outArea->blockSignals(true);
}

Output::~Output()
{
    delete ui;
}

void Output::append(QByteArray line)
{
    ui->outArea->append(QString(line));
}

void Output::appendError(QByteArray line)
{
    QColor oc = ui->outArea->textColor();
    ui->outArea->setTextColor(QColor(ERROR_COLOR));
    ui->outArea->append(QString(line));
    ui->outArea->setTextColor(oc);
}
