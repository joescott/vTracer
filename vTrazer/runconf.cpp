#include <QFileDialog>
#include <QtCore>
#include "def.h"
#include "util.h"
#include "runconf.h"

runConf::runConf(QSettings *pqs,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::runConf),
    editAllow(false),
    m_qs(pqs)
{
    ui->setupUi(this);

    ui->appPath->setText(m_qs->value(CF_APP_PATH).toString());
    ui->appOptions->setText(m_qs->value(CF_APP_OPTIONS).toString());

    editAllow = true;
}

runConf::~runConf()
{
}

void runConf::on_appPath_editingFinished()
{
    if(editAllow)
        m_qs->setValue(CF_APP_PATH,ui->appPath->text());
}

void runConf::on_getAppButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select Application File"));
    ui->appPath->setText(path);
    if(editAllow)
        m_qs->setValue(CF_APP_PATH,path);
}

void runConf::on_appOptions_editingFinished()
{
    if(editAllow)
        m_qs->setValue(CF_APP_OPTIONS,ui->appOptions->text());
}



