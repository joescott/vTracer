#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(int index,QWidget *parent) :
    QWidget(parent),
    index(index),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit closed(this);
}
