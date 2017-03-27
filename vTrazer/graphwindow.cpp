#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(int index,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphWindow),
    index(index)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::closeEvent(QCloseEvent *event)
{
    emit closed(this);
}
