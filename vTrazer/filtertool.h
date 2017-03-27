#ifndef FILTERTOOL_H
#define FILTERTOOL_H

#include "itemtool.h"

class FilterTool : public itemTool
{
public:
    explicit FilterTool(SessionManager *sessionManager, QWidget *parent = 0) :
        itemTool(sessionManager, parent){}

    QWidget *itemAddDefinition(int index);
    void itemDelDefinition(int index);
    void addFilterFromSession(Filter *filter);

private slots:
    void enableAllItems(bool checked);
};

#endif // FILTERTOOL_H
