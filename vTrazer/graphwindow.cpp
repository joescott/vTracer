#include "graphwindow.h"
#include "ui_graphwindow.h"
#include "scatterwidget.h"
#include "rkheventview.h"
#include "sessionmanager.h"

GraphWindow::GraphWindow(int index,SessionManager *sm,QWidget *parent) :
    QWidget(parent),
    index(index),
    ui(new Ui::GraphWindow),
    sm(sm)
{
    ui->setupUi(this);
    //ScatterWidget *w = new ScatterWidget(sm);
    RKHEventView *w = new RKHEventView(sm);
    ui->horizontalLayout->addWidget(w);
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
