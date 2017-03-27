#ifndef FILTER_H
#define FILTER_H

#include <QFrame>
#include <QString>

#include "sessionmanager.h"
#include "columnfilter.h"
#include "modelfilterdefinition.h"

class SessionManager;

namespace Ui {
    class Filter;
}

class Filter : public QFrame
{
    Q_OBJECT

public:

    explicit Filter(ModelFilterDefinition *mfd, SessionManager *sessionManager,
                    int type = 0, QWidget *parent = 0);
    ~Filter();

    void setIndex(int idx);
    int  getIndex(){ return index;}

    void setEditable(bool edit){editAllow = edit;}
    bool isEnabled(){ return enabled; }

    QList<ColumnFilter *>   colFilters;
    int                     type;

signals:
    void deleteFilter(int index);
    void enableFilter(bool status);

public slots:
    void filterEnable(bool status);

private slots:
    void on_closeButton_clicked();
    void on_enable_toggled(bool checked);

private:
    int            index;
    bool           editAllow;
    Ui::Filter     *ui;
    bool           enabled;

    SessionManager *sm;

};

#endif // FILTER_H
