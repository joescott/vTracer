#ifndef GENERALPARSERMODEL_H
#define GENERALPARSERMODEL_H

#include <QObject>
#include <QtGui>
#include "parsermodelinterface.h"
#include "modelfilterdefinition.h"
#include "modelwatchdefinition.h"

class GeneralParserModel : public QObject, ParserModelInterface
{
    Q_OBJECT
    Q_INTERFACES(ParserModelInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.ParserModelInterface")

public:
    QAbstractItemModel *createModel(QWidget *parent);
    void parseLine(QAbstractItemModel *model,QString line);
    QStringList getFiltersTypes();
    ModelFilterDefinition getFilter(int filterType);
    ModelWatchDefinition getWatch(int watchType);
};

#endif
