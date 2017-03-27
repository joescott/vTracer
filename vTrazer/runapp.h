#ifndef RUNAPP_H
#define RUNAPP_H


#include <QWidget>
#include <QProcess>
#include <QSettings>
#include <QStateMachine>
#include <QTimer>
#include <QAbstractItemModel>

//Plugins
#include "parsermodelinterface.h"
#include "modelfilterdefinition.h"
#include "modelwatchdefinition.h"

namespace Ui {
class RunApp;
}


class RunApp : public QWidget
{
    Q_OBJECT
    
public:
    explicit RunApp(QSettings *pqs, QWidget *parent = 0);
    ~RunApp();

    bool loadPlugin(QString model);
    QAbstractItemModel *createModel();
    void appReadFile(QString fileName);
    QStringList getFilters();
    ModelFilterDefinition getFilterDefinition(int type);
    ModelWatchDefinition getWatchDefinition(int type);

signals:
    void appEndReadFile();
    void appReadyLines(int total, int lines);
    void appReadyRead(QByteArray line, int row);
    void appConf();
    void appErrorRead(QByteArray line);

private slots:
    void on_connectButton_clicked();
    void appRead();
    void appReadError();
    void appError(QProcess::ProcessError pe);

    void on_editCommand_clicked();

    void appReadFileTimer();
    void appCancelReadFile();

private:
    QWidget                     *m_p;
    QSettings                   *m_qs;
    Ui::RunApp                  *ui;
    QStateMachine               *mm;
    QProcess                    *qp;
    QAbstractItemModel          *sm;

    ParserModelInterface        *modelManager;

    bool                        forcedEnd;
    QTimer                      timer;
    QFile                       *dataFile;
    QTextStream                 *dataStream;
    int                         totalLines;
};

#endif // RUNAPP_H
