#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "def.h"
#include "util.h"

#include "generalconf.h"
#include "runconf.h"
#include "filter.h"
#include "sessionmanager.h"
#include "proxymodel.h"
#include "itemDelegate.h"


#include <QStateMachine>
#include <QMessageBox>
#include <QtGui>
#include <QFileDialog>
#include <QWidgetAction>


MainWindow::MainWindow(QSettings *qs,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sm(qs,this),
    rapp(qs,this)
{
    m_qs = qs;
    sm.rapp = &rapp;

    ui->setupUi(this);

    ui->actionViewTools->setChecked(true);
    ui->actionViewControl_Panel->setChecked(true);
    ui->ResultFrame->setHidden(true);
    ui->searchWidget->setHidden(true);


    /**
      * Hide First Column
      */
    //ui->mainView->setColumnHidden(0,true);

    ui->ControlPanelDockWidget->setWidget(&rapp);

    /**
     * Set Model
     */
    sourceModel = rapp.createModel();
    proxyModel = new ProxyModel(&sm);


    proxyModel->setSourceModel(sourceModel);
    sm.setModel(sourceModel, proxyModel);

    /**
     * ToolBox
     */
    // Filters
    filterTool = new FilterTool(&sm);
    filterTool->addTypes(rapp.getFilters());
    connect(filterTool,SIGNAL(itemsChanged()),
            this,SLOT(filtersChanged()));
    filterTool->signalsGeneralEnable();
    toolBox.addItem(filterTool,QIcon(":img/filter"),tr("Filters"));

    // Watches
    watchTool = new WatchTool(&sm);
    watchTool->addTypes(rapp.getFilters());
    connect(watchTool,SIGNAL(itemsChanged()),
            this,SLOT(watchsChanged()));
    toolBox.addItem(watchTool,QIcon(":img/watch"),tr("Watchs"));

    ui->ToolsDockWidget->setWidget(&toolBox);


    /**
     * WatchView
     */
    watchView = new WatchView();

    /**
     * Grapher
     */
    grapher = new Grapher(&sm);

    /**
     * Set View
     */
    ItemDelegate *delegate = new ItemDelegate();
    ui->tableView->setItemDelegate(delegate);
    ui->tableView->setModel(proxyModel);
    for(int i=0; i<proxyModel->columnCount(); i++)
        if(proxyModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().indexOf("_id_") == 0)
            ui->tableView->setColumnHidden(i, false);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested( const QPoint& )),
    this, SLOT(on_customContextMenu( const QPoint& )));

    /**
     *  SLOT & SIGNALS
     */
    connect(ui->actionAbout,SIGNAL(triggered()),
            this,SLOT(About()));

    connect(&sm,SIGNAL(sessionClear()),
            this,SLOT(sessionClear()));
    connect(&sm,SIGNAL(addFilterFromSession(Filter*)),
            this,SLOT(addFilterFromSession(Filter*)),Qt::QueuedConnection);
    connect(&sm,SIGNAL(addWatchFromSession(Watch*)),
            this,SLOT(addWatchFromSession(Watch*)),Qt::QueuedConnection);

    connect(&rapp,SIGNAL(appReadyRead(QByteArray ,int)),
            this,SLOT(watchTrigger(QByteArray ,int)));
    connect(&rapp,SIGNAL(appReadyRead(QByteArray, int)),
            this,SLOT(appReadyRead(QByteArray,int)));

    connect(&rapp,SIGNAL(appErrorRead(QByteArray)),
            this,SLOT(appErrorRead(QByteArray)));
    connect(&rapp,SIGNAL(appConf()),
            this,SLOT(on_actionRun_triggered()));
    connect(&rapp,SIGNAL(appEndReadFile()),
            this,SLOT(appEndReadFile()));
    connect(&rapp,SIGNAL(appReadyLines(int ,int)),
            this,SLOT(appReadyLines(int ,int)));

    connect(watchView,SIGNAL(watchSelected(int)),
            this,SLOT(watchSelected(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_customContextMenu( const QPoint &_point )
{
    QPoint      pos   = ui->tableView->mapToGlobal(_point);
    QModelIndex index = ui->tableView->currentIndex();
    //int         row   = index.row();
    if(index.row() < 0)
        return;
    int         col   = index.column();
    QString st = ui->tableView->model()->data(index).toString();
    QString header = ui->tableView->model()->headerData(col,Qt::Horizontal).toString();

    QMenu menu;
    QAction *action_genFilter = new QAction(QIcon(":img/filter"),tr("&Generate Filter %1 = %2").arg(header,st), this);
    connect(action_genFilter, SIGNAL(triggered()),this,SLOT(gen_filter()));
    menu.addAction(action_genFilter);
    QAction *action_genWatch = new QAction(QIcon(":img/watch"),tr("&Generate Watch %1 = %2").arg(header,st), this);
    connect(action_genWatch, SIGNAL(triggered()),this,SLOT(gen_watch()));
    menu.addAction(action_genWatch);
    menu.exec(pos);
}

void MainWindow::gen_filter()
{
    QModelIndex index = ui->tableView->currentIndex();
    //int row = ui->tableView->selectionModel()->currentIndex().row();
    //int col = ui->tableView->selectionModel()->currentIndex().column();

    QString st = ui->tableView->model()->data(index).toString();
    ModelFilterDefinition mfd = sm.rapp->getFilterDefinition(0);
    Filter *f = new Filter(&mfd, &sm);
    sm.addFilter(f);
    QList<ColumnFilter *> cflist = f->colFilters;

    ColumnFilter *cf = cflist.at(0);
    cf->setFilterColIndex(index.column());
    cf->setRegExpStr(st);
    cf->setFilterCaseSencitive(true);
    emit addFilterFromSession(f);
}

void MainWindow::gen_watch()
{
    QModelIndex index = ui->tableView->currentIndex();
    //int row = ui->tableView->selectionModel()->currentIndex().row();
    //int col = ui->tableView->selectionModel()->currentIndex().column();

    QString st = ui->tableView->model()->data(index).toString();
    ModelWatchDefinition mwd = sm.rapp->getWatchDefinition(0);
    Watch *w = new Watch(&mwd, &sm);
    sm.addWatch(w);
    QList<ColumnFilter *> cflist = w->colFilters;

    ColumnFilter *cf = cflist.at(0);
    cf->setFilterColIndex(index.column());
    cf->setRegExpStr(st);
    cf->setFilterCaseSencitive(true);
    emit addWatchFromSession(w);
}

void MainWindow::openAtResult(QWidget *w, QString str)
{
    int index;
    for(index = 0; index < ui->ResultTabWidget->count();++index)
        if(!ui->ResultTabWidget->tabText(index).compare(str))
            break;
    if(index == ui->ResultTabWidget->count())
        index = ui->ResultTabWidget->addTab(w,str);
    ui->ResultTabWidget->setCurrentIndex(index);

    ui->ResultFrame->setVisible(true);
    ui->actionViewResult->setChecked(true);
    w->setFocus();
}

void MainWindow::About()
{
    QMessageBox *about = new QMessageBox(this);
    about->setIcon(QMessageBox::NoIcon);
    about->setWindowTitle(PROGRAM_NAME);
    about->setText(PROGRAM_ABOUT);

    about->setStyleSheet("QMessageBox {background-image: url(:img/company);\
                         background-repeat:no-repeat;background-attachment:\
                         fixed;background-position:left bottom;}");


    about->show();
}

void MainWindow::on_actionConfigure_triggered()
{
    generalConf *vtc = new generalConf(this->m_qs,this);
    openAtResult(vtc,tr("Configuration"));
}

void MainWindow::on_actionRun_triggered()
{
    runConf *vtc = new runConf(this->m_qs,this);
    openAtResult(vtc,tr("Run Configuration"));
}

void MainWindow::on_ResultTabWidget_tabCloseRequested(int index)
{
    ui->ResultTabWidget->removeTab(index);

    if(!ui->ResultTabWidget->count())
    {
        ui->ResultFrame->setVisible(false);
        ui->actionViewResult->setChecked(false);
    }
}

void MainWindow::on_actionManual_triggered()
{
    QDesktopServices::openUrl(
                QUrl::fromLocalFile(util::directoryOf(HELP_SUB_DIR).
                                    absoluteFilePath(HELP_FILE)));
}

void MainWindow::on_actionSessionManager_triggered()
{
    openAtResult(&sm,tr("Session Manager"));
}


void MainWindow::on_actionShow_Full_Screen_toggled(bool arg1)
{
   if(arg1)
       this->showFullScreen();
   else
       this->showNormal();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle(tr("Warning"));
    msgBox->setText(("Are you sure you want to exit?"));
    msgBox->setIcon(QMessageBox::Question);

    QPushButton *yesButton = msgBox->addButton(tr("Yes"),
                                               QMessageBox::ActionRole);
    msgBox->addButton(tr("No"), QMessageBox::ActionRole);
    msgBox->exec();

    if ((QPushButton*)msgBox->clickedButton() == yesButton)
    {
        //Save what ever you want
        event->accept();
    }
}

void MainWindow::on_actionOpen_triggered()
{
        QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open vTrazer File"),
            QDir::currentPath(),
            tr("vTrazer files (*.log *.vtz);;All files (*)") );
        if( !fileName.isNull() )
        {
            lpbar = new LoadFileProgressBar(this);
            connect(lpbar,SIGNAL(cancelLoad()),
                &rapp,SLOT(appCancelReadFile()));
            lpbar->show();
            setEnabled(false);
            lpbar->setEnabled(true);
            ui->tableView->setModel(0);
            rapp.appReadFile(fileName);
        }
}

void MainWindow::appReadyLines(int prf, int totalLines)
{
    lpbar->setProgress(prf, totalLines);
}

void MainWindow::appEndReadFile()
{
    ui->tableView->setModel(proxyModel);
    ui->tableView->scrollToBottom();
    delete lpbar;
    setEnabled(true);
}

/******************************************************************************/
/**
 * Application
 */
/******************************************************************************/
void MainWindow::appReadyRead(QByteArray line, int row)
{
    Q_UNUSED(row);
    out.append(line);
    ui->tableView->resizeRowToContents(row);
    ui->tableView->scrollToBottom();
}

void MainWindow::appErrorRead(QByteArray line)
{
    out.appendError(line);
    openAtResult(&out,tr("App Output"));
    ui->actionOutput->setChecked(true);
    ui->tableView->scrollToBottom();
}

void MainWindow::on_actionOutput_triggered()
{
    openAtResult(&out,tr("App Output"));
}

void MainWindow::on_actionWatch_triggered()
{
    openAtResult(watchView,tr("Watch View"));
}

void MainWindow::on_actionGraph_triggered()
{
    openAtResult(grapher,tr("Graph View"));
}

/******************************************************************************/
/**
  * Search Action
  */
/******************************************************************************/
void MainWindow::on_actionFind_triggered()
{
   ui->searchWidget->setVisible(true);
   ui->searchWidget->setFocus();
   ui->regexpEdit->setFocus();
}

void MainWindow::on_hideButton_clicked()
{
    ui->searchWidget->hide();
    ui->regexpEdit->clear();
    ui->tableView->clearSelection();
    ui->tableView->scrollToBottom();
}

void MainWindow::on_regexpEdit_returnPressed()
{
   sIndexList.clear();
   if(ui->regexpEdit->text().isEmpty())
       return;

   for(int col = 0; col < proxyModel->columnCount();++col)
   {
                sIndexList << proxyModel->match(proxyModel->index(0,col),
                 Qt::DisplayRole,
                 ui->regexpEdit->text(), -1,
                 Qt::MatchContains | Qt::MatchRecursive );
   }
    if(sIndexList.count())
    {
        sCurrentIndex = sIndexList.begin();
        ////ui->tableView->setCurrentIndex(indexList.at(0));
        ui->tableView->selectRow((*sCurrentIndex).row());
    }
}

void MainWindow::on_nextSearch_clicked()
{
    if(sIndexList.count())
    {
        if(sCurrentIndex != sIndexList.end()-1)
            sCurrentIndex++;
        else
            sCurrentIndex = sIndexList.begin();

        ui->tableView->selectRow((*sCurrentIndex).row());
    }
}

void MainWindow::on_backSearch_clicked()
{
    if(sIndexList.count())
    {
        if(sCurrentIndex != sIndexList.begin())
            sCurrentIndex--;
        else
            sCurrentIndex = sIndexList.end()-1;

        ui->tableView->selectRow((*sCurrentIndex).row());
    }
}

/******************************************************************************/
/**
 * Session
 */
/******************************************************************************/
void MainWindow::sessionClear()
{
  filterTool->deleteAllItems();
  watchTool->deleteAllItems();
}

/******************************************************************************/
/**
 * Filters
 */
/******************************************************************************/
void MainWindow::filtersChanged()
{
    proxyModel->refreshModel();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::addFilterFromSession(Filter *filter)
{
    filterTool->addItemFromSession(filter);
    filterTool->signalsEnable(filter);
}

/******************************************************************************/
/**
 * Watchs
 */
/******************************************************************************/
void MainWindow::watchsChanged()
{
    proxyModel->refreshModel();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::addWatchFromSession(Watch *watch)
{
    watchTool->addItemFromSession(watch);
    watchTool->signalsEnable(watch);
}

void MainWindow::watchSelected(int row)
{
    QModelIndex pIndex = proxyModel->mapFromSource(sourceModel->index(row,0));
    ui->tableView->selectRow(pIndex.row());
}

void MainWindow::watchTrigger(QByteArray line, int row)
{
    Q_UNUSED(line);
#if 1
    QList<Watch *> wlist = sm.watchs;
    QList<ColumnFilter *> cflist;

    for(int i = 0; i < wlist.count(); ++i)
    {
        Watch *w = sm.watchs.at(i);
        if(!w->isEnabled())
            continue;
        bool prtn = true;
        cflist = sm.watchs.at(i)->colFilters;
        for(int c = 0; c < cflist.count(); ++c)
        {
            ColumnFilter *cf = cflist.at(c);
            QModelIndex m = sm.sm->index(row,cf->getFilterColIndex());
            QString s = sm.sm->data(m).toString();
            QRegularExpression re(cf->getRegExpStr(),
                                  cf->getFilterCaseSencitive()?
                                          QRegularExpression::NoPatternOption:
                                          QRegularExpression::CaseInsensitiveOption);
            QRegularExpressionMatch match = re.match(s);
            prtn &= match.hasMatch();
        }
        if(prtn)
        {
            watchView->addAlarm(sm.sm, line, row);
            openAtResult(watchView,tr("Watch View"));
            //out.append(line.append(">>>>ALARMA"));
        }
    }
#endif

}

// End Filters


