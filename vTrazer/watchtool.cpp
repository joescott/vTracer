#include "watchtool.h"

QWidget *WatchTool::itemAddDefinition(int index)
{
   ModelWatchDefinition mwd = sm->rapp->getWatchDefinition(index);
   Watch *w = new Watch(&mwd, sm, index);
   sm->addWatch(w);

   connect(w,SIGNAL(deleteWatch(int)),
            this,SLOT(deleteItem(int)));
   connect(w,SIGNAL(enableWatch(bool)),
            this,SLOT(enableItem(bool)));

   connect(this, SIGNAL(allItemsEnable(bool)),
           this, SLOT(enableAllItems(bool)));

   return w;
}

void WatchTool::itemDelDefinition(int index)
{
    sm->delWatch(index);
}

void WatchTool::addWatchFromSession(Watch *watch)
{
   connect(watch,SIGNAL(deleteWatch(int)),
            this,SLOT(deleteItem(int)));
   connect(watch,SIGNAL(enableWatch(bool)),
            this,SLOT(enableItem(bool)));

   addItemFromSession(watch);
}

void WatchTool::signalsGeneralEnable()
{
   connect(this, SIGNAL(allItemsEnable(bool)),
           this, SLOT(enableAllItems(bool)));
}

void WatchTool::signalsEnable(Watch *watch)
{
   connect(watch,SIGNAL(deleteWatch(int)),
            this,SLOT(deleteItem(int)));
   connect(watch,SIGNAL(enableWatch(bool)),
            this,SLOT(enableItem(bool)));
}


void WatchTool::enableAllItems(bool checked)
{
   sm->enableAllWatchs(checked);
}
