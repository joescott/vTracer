#include "sessionmanager.h"
#include "ui_sessionmanager.h"
#include "util.h"
#include "def.h"

#include <QFileSystemModel>
#include <QFileDialog>
#include <QMessageBox>

SessionManager::SessionManager(QSettings *qs,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionManager)
{
    ui->setupUi(this);

    m_qs = qs;

    completer = new QCompleter(this);
    completer->setMaxVisibleItems(10);

    QFileSystemModel *fsModel = new QFileSystemModel(completer);
    fsModel->setRootPath(util::directoryOf(SESSION_PATH).absolutePath());
    completer->setModel(fsModel);
    ui->sessionFile->setCompleter(completer);
    ui->sessionFile->setText(m_qs->value(CF_SESSION_FILE).toString());
    this->hide();

    connect(this,SIGNAL(endLoadSession()),
            this,SLOT(endAction()),Qt::QueuedConnection);
}

SessionManager::~SessionManager()
{
    delete ui;
}

void SessionManager::rowAddedTrigger(int row)
{
    emit rowAdded(row);
}

void SessionManager::saveSession(QString file)
{
    QSettings set(file, QSettings::IniFormat);

    buttonsEnable(false);

    set.clear();

    //Parser
    set.setValue(PARSER_DFT_TYPE, m_qs->value(CF_APP_PARSER).toString());

    //Filters
    set.beginWriteArray(FILTER_DFT_ARRAY);
    QList<ColumnFilter *> cflist;

    for(int i = 0; i < filters.count(); ++i)
    {
       Filter *f = filters.at(i);
       set.setArrayIndex(i);
       set.setValue(FILTER_DFT_INDEX,  f->getIndex());
       set.setValue(FILTER_DFT_STATUS, f->isEnabled());
       set.setValue(FILTER_DFT_TYPE,   f->type);

       cflist = f->colFilters;
       set.beginWriteArray(FILTER_CONDITION_DFT_ARRAY);
       for(int c = 0; c < cflist.count(); ++c)
       {
           ColumnFilter *cf = cflist.at(c);
           set.setArrayIndex(c);
           set.setValue(FILTER_DFT_COLINDEX,        cf->getFilterColIndex());
           set.setValue(FILTER_DFT_REGSTR,          cf->getRegExpStr());
           set.setValue(FILTER_DFT_CASESENCITIVE,   cf->getFilterCaseSencitive());
       }
       set.endArray();
    }
    set.endArray();
    //Watchs
    set.beginWriteArray(WATCH_DFT_ARRAY);
    QList<ColumnFilter *> cwlist;

    for(int i = 0; i < watchs.count(); ++i)
    {
       Watch *w = watchs.at(i);
       set.setArrayIndex(i);
       set.setValue(WATCH_DFT_INDEX,  w->getIndex());
       set.setValue(WATCH_DFT_STATUS, w->isEnabled());
       set.setValue(WATCH_DFT_TYPE,   w->type);

       cwlist = w->colFilters;
       set.beginWriteArray(WATCH_CONDITION_DFT_ARRAY);
       for(int c = 0; c < cwlist.count(); ++c)
       {
           ColumnFilter *cf = cwlist.at(c);
           set.setArrayIndex(c);
           set.setValue(WATCH_DFT_COLINDEX,        cf->getFilterColIndex());
           set.setValue(WATCH_DFT_REGSTR,          cf->getRegExpStr());
           set.setValue(WATCH_DFT_CASESENCITIVE,   cf->getFilterCaseSencitive());
       }
       set.endArray();
    }
    set.endArray();
    emit endLoadSession();
}

void SessionManager::endAction()
{
   buttonsEnable(true);
}

void SessionManager::buttonsEnable(bool status)
{
    ui->openButton->setEnabled(status);
    ui->saveButton->setEnabled(status);
}

void SessionManager::openSession(QString file)
{
    QSettings set(file, QSettings::IniFormat);

    int fsize, cfsize, wsize, cwsize;

    if(m_qs->value(CF_APP_PARSER).toString()
                    .compare(set.value(PARSER_DFT_TYPE).toString()))
    {
        QMessageBox::warning(this, PROGRAM_NAME,
                             tr("Wrong model type!\n Actual model is %1 and"
                                "you are trying to load %2 type.")
                             .arg(m_qs->value(CF_APP_PARSER).toString())
                             .arg(set.value(PARSER_DFT_TYPE).toString()),
                             QMessageBox::Ok);
        return;
    }
    buttonsEnable(false);

    // UI Clear
    emit sessionClear();

    // Filters
    filters.clear();

    fsize = set.beginReadArray(FILTER_DFT_ARRAY);
    QList<ColumnFilter *> cflist;
    for(int i = 0; i < fsize; ++i)
    {
        int filter_type = set.value(QString("%1/%2").arg(i+1).arg(FILTER_DFT_TYPE)).toInt();
        ModelFilterDefinition mfd = rapp->getFilterDefinition(filter_type);
        Filter *f = new Filter(&mfd, this);
        addFilter(f);
        set.setArrayIndex(i);
        f->setIndex(set.value(FILTER_DFT_INDEX).toInt());
        f->filterEnable(set.value(FILTER_DFT_STATUS).toBool());
        f->type = filter_type;

        cflist = f->colFilters;
        cfsize = set.beginReadArray(FILTER_CONDITION_DFT_ARRAY);
        for(int c = 0; c < cfsize; ++c)
        {
            ColumnFilter *cf = cflist.at(c);
            int ci = c+1;
            cf->setFilterColIndex(set.value(QString("%1/%2").arg(ci).arg(FILTER_DFT_COLINDEX)).toInt());
            cf->setRegExpStr(set.value(QString("%1/%2").arg(ci).arg(FILTER_DFT_REGSTR)).toString());
            cf->setFilterCaseSencitive(set.value(QString("%1/%2").arg(ci).arg(FILTER_DFT_CASESENCITIVE)).toBool());
        }
        set.endArray();
        emit addFilterFromSession(f);
    }
    set.endArray();

    // Watches
    watchs.clear();

    wsize = set.beginReadArray(WATCH_DFT_ARRAY);
    QList<ColumnFilter *> cwlist;
    for(int i = 0; i < wsize; ++i)
    {
        int watch_type = set.value(QString("%1/%2").arg(i+1).arg(WATCH_DFT_TYPE)).toInt();
        ModelWatchDefinition mwd = rapp->getWatchDefinition(watch_type);
        Watch *w = new Watch(&mwd, this);
        addWatch(w);
        set.setArrayIndex(i);
        w->setIndex(set.value(WATCH_DFT_INDEX).toInt());
        w->watchEnable(set.value(WATCH_DFT_STATUS).toBool());
        w->type = watch_type;

        cwlist = w->colFilters;
        cwsize = set.beginReadArray(WATCH_CONDITION_DFT_ARRAY);
        for(int c = 0; c < cwsize; ++c)
        {
            ColumnFilter *cf = cwlist.at(c);
            int ci = c+1;
            cf->setFilterColIndex(set.value(QString("%1/%2").arg(ci).arg(WATCH_DFT_COLINDEX)).toInt());
            cf->setRegExpStr(set.value(QString("%1/%2").arg(ci).arg(WATCH_DFT_REGSTR)).toString());
            cf->setFilterCaseSencitive(set.value(QString("%1/%2").arg(ci).arg(WATCH_DFT_CASESENCITIVE)).toBool());
        }
        set.endArray();
        emit addWatchFromSession(w);
    }

    set.endArray();
    emit endLoadSession();
}

/**
 * Filters
 */
void SessionManager::orderFilters()
{
    for(int i = 0; i < countFilters(); ++i)
        getFilter(i)->setIndex(i);
}

void SessionManager::enableAllFilters(bool checked)
{
    for(int i = 0; i < countFilters(); ++i)
            enableFilter(i,checked);
}

void SessionManager::addFilter(Filter *filter)
{
    filters.append(filter);
    filter->setIndex(countFilters()-1);
}

Filter * SessionManager::getFilter(int index)
{
    return filters.at(index);
}

void SessionManager::delFilter(int index)
{
    getFilter(index)->close();
    filters.removeAt(index);
    orderFilters();
}

int SessionManager::countFilters()
{
    return filters.count();
}

void SessionManager::enableFilter(int index, bool checked)
{
    getFilter(index)->filterEnable(checked);

}

void SessionManager::filtersChanged()
{
    pm->refreshModel();
}

/**
 * Watchs
 */
void SessionManager::orderWatchs()
{
    for(int i = 0; i < countWatchs(); ++i)
        getWatch(i)->setIndex(i);
}

void SessionManager::enableAllWatchs(bool checked)
{
    for(int i = 0; i < countWatchs(); ++i)
            enableWatch(i,checked);
}

void SessionManager::addWatch(Watch *watch)
{
    watchs.append(watch);
    watch->setIndex(countWatchs()-1);
}

Watch *SessionManager::getWatch(int index)
{
    return watchs.at(index);
}

void SessionManager::delWatch(int index)
{
    getWatch(index)->close();
    watchs.removeAt(index);
    orderWatchs();
}

int SessionManager::countWatchs()
{
    return watchs.count();
}

void SessionManager::enableWatch(int index, bool checked)
{
    getWatch(index)->watchEnable(checked);
}

void SessionManager::watchsChanged()
{
    pm->refreshModel();
}

/**
 * Buttons
 */
void SessionManager::on_saveButton_clicked()
{
    QString fileName = ui->sessionFile->text();
    if(!fileName.isEmpty())
    {
        saveSession(fileName);
        m_qs->setValue(CF_SESSION_FILE, fileName);
    }else
         QMessageBox::warning(this, PROGRAM_NAME,
                               tr("Can't save session file. Session Filename is empty."),
                              QMessageBox::Ok);

}

void SessionManager::on_openButton_clicked()
{
    QString fileName = ui->sessionFile->text();
    if(!fileName.isEmpty())
    {
        openSession(fileName);
        ui->sessionFile->setText(fileName);
        m_qs->setValue(CF_SESSION_FILE, fileName);
    }else
         QMessageBox::warning(this, PROGRAM_NAME,
                               tr("Can't open session file. Session Filename is empty."),
                              QMessageBox::Ok);

}

void SessionManager::on_selectButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select File"),
                                                    util::directoryOf(SESSION_PATH).absolutePath(),
                                                    tr("Session Files (*)"));
    if(!fileName.isEmpty())
    {
        ui->sessionFile->setText(fileName);
    }else
         QMessageBox::warning(this, PROGRAM_NAME,
                               tr("Can't select File. Session Filename is empty."),
                              QMessageBox::Ok);

}
