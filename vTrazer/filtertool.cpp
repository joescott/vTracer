#include "filtertool.h"

QWidget *FilterTool::itemAddDefinition(int index)
{
   ModelFilterDefinition mfd = sm->rapp->getFilterDefinition(index);
   Filter *f = new Filter(&mfd, sm, index);
   sm->addFilter(f);

   connect(f,SIGNAL(deleteFilter(int)),
            this,SLOT(deleteItem(int)));
   connect(f,SIGNAL(enableFilter(bool)),
            this,SLOT(enableItem(bool)));

   connect(this, SIGNAL(allItemsEnable(bool)),
           this, SLOT(enableAllItems(bool)));

   return f;
}

void FilterTool::itemDelDefinition(int index)
{
    sm->delFilter(index);
}

void FilterTool::addFilterFromSession(Filter *filter)
{
   connect(filter,SIGNAL(deleteFilter(int)),
            this,SLOT(deleteItem(int)));
   connect(filter,SIGNAL(enableFilter(bool)),
            this,SLOT(enableItem(bool)));

   addItemFromSession(filter);
}

void FilterTool::enableAllItems(bool checked)
{
   sm->enableAllFilters(checked);
}
