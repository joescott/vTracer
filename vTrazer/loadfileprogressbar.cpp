#include "loadfileprogressbar.h"
#include "ui_loadfileprogressbar.h"
#include "util.h"

LoadFileProgressBar::LoadFileProgressBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFileProgressBar)
{
    ui->setupUi(this);
    timeElapsed.start();
}


LoadFileProgressBar::~LoadFileProgressBar()
{
    delete ui;
}

void LoadFileProgressBar::setProgress( int progress, int lines)
{
    ui->progressBar->setValue(progress);
    ui->label->setText(tr("Lines: %1").arg(lines));

    ui->time->setText(util::msecToString(timeElapsed.elapsed()));
}

void LoadFileProgressBar::on_stopLoadButton_clicked()
{
    emit cancelLoad();
}
