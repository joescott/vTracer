#include <QtGui>
#include <QtCore>

#include "proxymodel.h"
#include "filter.h"
#include "columnfilter.h"

ProxyModel::ProxyModel(SessionManager *smanager,QObject *parent)
    : QSortFilterProxyModel(parent),
      sm(smanager)
{
    setDynamicSortFilter(true);
}

bool ProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    bool rtn = true;
    QModelIndex index;
    QList<Filter *> flist = sm->filters;
    QList<ColumnFilter *> cflist;

    for(int i = 0; i < flist.count(); ++i)
    {
        bool prtn = true;
        Filter *f = sm->filters.at(i);
        if(!f->isEnabled())
            continue;
        cflist = sm->filters.at(i)->colFilters;
        for(int c = 0; c < cflist.count(); ++c)
        {
            ColumnFilter *cf = cflist.at(c);

            index = sourceModel()->index(sourceRow, cf->getFilterColIndex(), sourceParent);

            QRegExp regExp(cf->getRegExpStr(),
                           cf->getFilterCaseSencitive()?
                               Qt::CaseSensitive:Qt::CaseInsensitive);
            prtn = prtn && sourceModel()->data(index).toString().contains(regExp);
        }
        rtn = rtn && prtn;
    }

    return rtn;
}

void ProxyModel::refreshModel()
{
    invalidateFilter();
}
