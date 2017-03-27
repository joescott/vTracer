#ifndef WATCHTOOL_H
#define WATCHTOOL_H

#include "itemtool.h"

class WatchTool : public itemTool
{
public:
    explicit WatchTool(SessionManager *sessionManager, QWidget *parent = 0) :
        itemTool(sessionManager, parent){}

    QWidget *itemAddDefinition(int index);
    void itemDelDefinition(int index);
    void addWatchFromSession(Watch *watch);

private slots:
    void enableAllItems(bool checked);
};

#endif // WATCHTOOL_H
