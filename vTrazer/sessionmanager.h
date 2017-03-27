#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "filter.h"
#include "watch.h"
#include "proxymodel.h"
#include "runapp.h"

#include <QWidget>
#include <QSettings>
#include <QCompleter>

class Filter;
class Watch;
class ProxyModel;

namespace Ui {
    class SessionManager;
}

class SessionManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit SessionManager(QSettings *qs,QWidget *parent = 0);
    ~SessionManager();

    QAbstractItemModel          *sm;
    ProxyModel                  *pm;
    QCompleter                  *completer;
    RunApp                      *rapp;

    void setModel(QAbstractItemModel *model, ProxyModel *pmodel)
    {
        sm = model;
        pm = pmodel;
    }

    void saveSession(QString file);
    void openSession(QString file);


    //Begin     --- Filters
    QList<Filter *> filters;

    void         addFilter(Filter *filter);
    void         delFilter(int index);
    void         enableFilter(int index, bool checked);
    void         enableAllFilters(bool checked);
    Filter *     getFilter(int index);
    int          countFilters();
    //End       --- Filters

    //Begin     --- Watchs
    QList<Watch *> watchs;

    void         addWatch(Watch *watch);
    void         delWatch(int index);
    void         enableWatch(int index, bool checked);
    void         enableAllWatchs(bool checked);
    Watch *      getWatch(int index);
    int          countWatchs();
    //End       --- Watchs

signals:
    void sessionClear();
    void addFilterFromSession(Filter *filter);
    void addWatchFromSession(Watch *watch);

private slots:
    void on_saveButton_clicked();

    void on_openButton_clicked();

public slots:
    void filtersChanged();
    void watchsChanged();

private:
    Ui::SessionManager  * ui;
    QSettings           * m_qs;

private:
    void orderFilters();
    void orderWatchs();

};

#endif // SESSIONMANAGER_H
