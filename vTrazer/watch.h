#ifndef WATCH_H
#define WATCH_H

#include <QWidget>

#include "sessionmanager.h"
#include "columnfilter.h"
#include "modelwatchdefinition.h"
#include "actioninterface.h"

class SessionManager;

namespace Ui {
class Watch;
}

class Watch : public QFrame
{
    Q_OBJECT
    
public:
    explicit Watch(ModelWatchDefinition *mwd, SessionManager *sessionManager,
                    int type = 0, QWidget *parent = 0);
    ~Watch();
    void setIndex(int idx);
    int  getIndex(){ return index;}

    QList<ColumnFilter *>   colFilters;
    int                     type;

public slots:
    void watchEnable(bool status);

private slots:
    void on_closeButton_clicked();
    void on_enable_toggled(bool checked);

signals:
   void deleteWatch(int index);
   void enableWatch(bool checked);

private:
    int             index;
    bool            editAllow;
    Ui::Watch       *ui;
    bool            enabled;

    SessionManager *sm;
    ActionInterface     *actionManager;

    bool loadActionPlugin(QString action);

};

#endif // WATCH_H
