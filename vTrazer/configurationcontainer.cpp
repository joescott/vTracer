#include "configurationcontainer.h"
#include "ui_configurationcontainer.h"

configurationContainer::configurationContainer(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::configurationContainer)
{
    ui->setupUi(this);
}

configurationContainer::~configurationContainer()
{
    delete ui;
}
