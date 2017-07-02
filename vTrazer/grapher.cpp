#include "grapher.h"
#include "ui_grapher.h"
#include "graphwindow.h"

#include <QMdiSubWindow>
#include <QtGui>

Grapher::Grapher(SessionManager *sm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Grapher),
    sm(sm)
{
    ui->setupUi(this);
    ui->graphertoolButton->addAction(ui->actionCascade);
    ui->graphertoolButton->addAction(ui->actionTile);
    ui->graphertoolButton->addAction(ui->actionNew);

}

Grapher::~Grapher()
{
    delete ui;
}


void Grapher::createSubWindow()
{
    static int cnt;
    GraphWindow *w = new GraphWindow(cnt, sm);
    w->setWindowTitle(tr("Graph %1").arg(cnt));
    ui->mdiArea->addSubWindow(w);
    ui->graphList->addItem(tr("Graph %1").arg(cnt));
    cnt++;

    connect(w,SIGNAL(closed(GraphWindow *)),
            this,SLOT(on_subWindowsClosed(GraphWindow *)));

    w->showMaximized();

    if(ui->actionCascade->isChecked())
        ui->mdiArea->cascadeSubWindows();
    else if(ui->actionTile->isChecked())
        ui->mdiArea->tileSubWindows();
}

void Grapher::on_actionNew_triggered()
{
    createSubWindow();
}

void Grapher::on_graphList_currentIndexChanged(int index)
{
    if(index == -1)
        return;
    QMdiSubWindow  *sw = ui->mdiArea->subWindowList().at(index);
    ui->mdiArea->setActiveSubWindow(sw);
}

void Grapher::on_subWindowsClosed(GraphWindow *w)
{
    int idx = ui->graphList->findText(w->windowTitle());
    if(idx != -1)
    ui->graphList->removeItem(idx);
}


void Grapher::on_actionCascade_toggled(bool arg1)
{
    if(arg1)
    {
        ui->mdiArea->cascadeSubWindows();
        ui->actionTile->setChecked(false);
    }
}

void Grapher::on_actionTile_toggled(bool arg1)
{
    if(arg1)
    {
        ui->mdiArea->tileSubWindows();
        ui->actionCascade->setChecked(false);
    }
}



