#ifndef PARSERMODELINTERFACE_H
#define PARSERMODELINTERFACE_H

#include <QString>
#include <QtGui>
#include "modelfilterdefinition.h"
#include "modelwatchdefinition.h"

class ParserModelInterface
{
public:
    virtual ~ParserModelInterface() {}
    virtual QAbstractItemModel *createModel(QWidget *parent) = 0;
    virtual void parseLine(QAbstractItemModel *model,QString line) = 0;
    virtual QStringList getFiltersTypes() = 0;
    virtual ModelFilterDefinition getFilter(int filterType) = 0;
    virtual ModelWatchDefinition getWatch(int watchType) = 0;
};


QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(ParserModelInterface, "com.trolltech.Plugin.ParserModelInterface/1.0")
QT_END_NAMESPACE

#endif
