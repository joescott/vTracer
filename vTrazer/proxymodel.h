#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QDate>
#include <QSortFilterProxyModel>

#include "sessionmanager.h"
#include "watch.h"

class SessionManager;
class Watch;

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyModel(SessionManager *smanager, QObject *parent = 0);
    void refreshModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent)const;

private:
    SessionManager *sm;


};

#endif
