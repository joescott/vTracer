#include "runapp.h"
#include "ui_runapp.h"
#include "def.h"
#include "util.h"

#include <QDir>


RunApp::RunApp(QSettings *pqs, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunApp),
    mm(new QStateMachine(this))
{
    ui->setupUi(this);

    m_qs = pqs;
    m_p  = parent;

    qp = new QProcess(this);


    QState *offLineState = new QState();
    QState *onLineState = new QState();
    onLineState->setObjectName("onLineState");
    offLineState->setObjectName("offLineState");

    offLineState->addTransition(
                qp, SIGNAL(started()), onLineState);
    onLineState->addTransition(
                qp, SIGNAL(finished(int)), offLineState);

    offLineState->assignProperty(
                ui->connectButton,"icon", QIcon(":img/offline"));
    offLineState->assignProperty(
                ui->connectButton,"toolTip", tr("Press to go OnLine"));

    onLineState->assignProperty(
                ui->connectButton,"icon", QIcon(":img/online"));
    onLineState->assignProperty(
                ui->connectButton,"toolTip", tr("Press to go OffLine"));

    mm->addState(offLineState);
    mm->addState(onLineState);

    mm->setInitialState(offLineState);

    mm->start();

    connect(qp,SIGNAL(readyReadStandardError()),
            this,SLOT(appReadError()));
    connect(qp,SIGNAL(readyRead()),
            this,SLOT(appRead()));
    connect(qp,SIGNAL(error(QProcess::ProcessError)),
            this,SLOT(appError(QProcess::ProcessError)));
}

RunApp::~RunApp()
{
    delete ui;
}

void RunApp::on_connectButton_clicked()
{
    switch(qp->state())
    {
    case QProcess::NotRunning:
    {
        QString arguments  = m_qs->value(CF_APP_OPTIONS).toString();
        QStringList argumentList = arguments.split(" ");
        QString program = m_qs->value(CF_APP_PATH).toString().trimmed();

        ui->connectCommand->setText(program+" "+arguments);
        forcedEnd = false;
        qp->start(program, argumentList);
    }
        break;
    case QProcess::Running:
    case QProcess::Starting:
    default:
        ui->connectCommand->setText("");
        qp->terminate();
        //qp->kill();
        forcedEnd = true;

        break;
    }
}


void RunApp::appRead()
{
    /** Read Line by Line*/
    while(!qp->atEnd())
    {
        QByteArray line = qp->readLine();
        modelManager->parseLine(sm,line);
        emit appReadyRead(line,sm->rowCount()-1);
    }
}

void RunApp::appReadFile(QString fileName)
{
    dataFile = new QFile(fileName);
    dataFile->open(QIODevice::ReadOnly | QIODevice::Text);
    dataStream = new QTextStream(dataFile);
    connect(&timer,SIGNAL(timeout()), this,SLOT(appReadFileTimer()));
    timer.start(APP_OPENFILE_INTERVAL);
    totalLines = 0;
}

void RunApp::appReadFileTimer()
{
    int lines = APP_OPENFILE_LINES;
    while( !dataStream->atEnd() ) {
        modelManager->parseLine(sm,dataStream->readLine());
        if(!--lines)
            break;
    }
    totalLines += (APP_OPENFILE_LINES - lines);
    int prf = 100 * dataStream->pos()/dataFile->size() ;
    emit appReadyLines( prf, totalLines);

    if(dataStream->atEnd())
    {
        timer.stop();
        emit appEndReadFile();
    }
}

void RunApp::appCancelReadFile()
{
    timer.stop();
    emit appEndReadFile();
}

void RunApp::appReadError()
{
    QByteArray line = qp->readAllStandardError();
    emit appErrorRead(line);
}

void RunApp::appError(QProcess::ProcessError pe)
{
    if (pe == QProcess::Crashed  && forcedEnd)
        return;
    QString line = tr("Termination Code: %1").arg(pe);
    emit appErrorRead(line.toLatin1());
}

void RunApp::on_editCommand_clicked()
{
    emit appConf();
}

/**
 *  ModelManager
 */
bool RunApp::loadPlugin(QString model)
{
    QDir pluginsDir = util::directoryOf(PLUGIN_MODEL_PATH);
    QString fileName = QString("%1%2%3")
            .arg(PLUGIN_MODEL_PREFIX)
            .arg(model).
            arg(PLUGIN_MODEL_POSFIX);

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" ||
            pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#endif
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    QObject *plugin = pluginLoader.instance();
    if (plugin){
       modelManager = qobject_cast<ParserModelInterface *>(plugin);
        if (modelManager)
            return true;
    }
    return false;
}


QAbstractItemModel *RunApp::createModel()
{
        QString modelName = m_qs->value(CF_APP_PARSER).toString();
        loadPlugin(modelName);
        sm = modelManager->createModel(this);
        return sm;
}

QStringList RunApp::getFilters()
{
    return modelManager->getFiltersTypes();
}

ModelFilterDefinition RunApp::getFilterDefinition(int type)
{
    return modelManager->getFilter(type);
}

ModelWatchDefinition RunApp::getWatchDefinition(int type)
{
    return modelManager->getWatch(type);
}
