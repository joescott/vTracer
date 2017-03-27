#ifndef MODELWATCHDEFINITION_H
#define MODELWATCHDEFINITION_H

class ModelWatchColumn
{

public:
    ModelWatchColumn();

    bool    enabled;
    bool    hide;
    int     index;
    bool    indexFixed;
    QString pattern;
    bool    cs;

};

class ModelWatchDefinition
{
public:
    ModelWatchDefinition();
    QString toolTip;
    QString action;
    QList<ModelWatchColumn> columns;
};

#endif // MODELWATCHDEFINITION_H
