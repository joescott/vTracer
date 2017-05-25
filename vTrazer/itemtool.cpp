#include "itemtool.h"
#include "ui_itemtool.h"

itemTool::itemTool(SessionManager *sessionManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemTool),
    sm(sessionManager)
{
    ui->setupUi(this);
}

itemTool::~itemTool()
{
    delete ui;
}

void itemTool::addTypes(QStringList list)
{
    ui->ItemTypes->addItems(list);
}

void itemTool::on_addItemButton_clicked()
{
    ui->enable->setIcon(QIcon(":img/online"));

    QWidget *i =  itemAddDefinition(ui->ItemTypes->currentIndex());
    ui->ItemToolArea->layout()->addWidget(i);
    ui->ItemToolArea->layout()->setAlignment(Qt::AlignTop);
    emit itemsChanged();
}

void itemTool::deleteItem(int index)
{
    itemDelDefinition(index);
    emit itemsChanged();
}

void itemTool::enableItem(bool status)
{
    emit itemsChanged();
    if(!ui->enable->isChecked() && status)
    {
        ui->enable->setChecked(true);
        ui->enable->setIcon(QIcon(":img/online"));
    }
}

void itemTool::on_enable_clicked(bool checked)
{
  if(checked)
        ui->enable->setIcon(QIcon(":img/online"));
    else
        ui->enable->setIcon(QIcon(":img/offline"));

    emit allItemsEnable(checked);
}

void itemTool::addItemFromSession(QWidget *widget)
{
    ui->enable->setIcon(QIcon(":img/online"));

    ui->ItemToolArea->layout()->addWidget(widget);
    ui->ItemToolArea->layout()->setAlignment(Qt::AlignTop);

    emit itemsChanged();
}

void itemTool::deleteAllItems()
{
  QLayoutItem *item;
  while((item = ui->ItemToolArea->layout()->takeAt(1)))
  {
      item->widget()->close();
      delete item;
  }
}
