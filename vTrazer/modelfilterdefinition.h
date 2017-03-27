#ifndef MODELFILTERDEFINITION_H
#define MODELFILTERDEFINITION_H

#include <QString>

class ModelFilterColumn
{

public:
    ModelFilterColumn();

    bool    enabled;
    bool    hide;
    int     index;
    bool    indexFixed;
    QString pattern;
    bool    cs;

};

class ModelFilterDefinition
{
public:
    ModelFilterDefinition();
    QString toolTip;
    QList<ModelFilterColumn> columns;
};


#endif // MODELFILTERDEFINITION_H
