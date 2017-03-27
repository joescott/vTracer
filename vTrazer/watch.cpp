#include "watch.h"
#include "ui_watch.h"
#include "util.h"
#include "def.h"

Watch::Watch(ModelWatchDefinition *mwd, SessionManager *sessionManager,
                int type, QWidget *parent) :
    QFrame(parent),
    type(type),
    editAllow(false),
    ui(new Ui::Watch),
    enabled(false),
    sm(sessionManager)
{
    ui->setupUi(this);

    foreach(ModelWatchColumn mwc, mwd->columns)
    {
        ColumnFilter *cf = new ColumnFilter(sm->pm);
        cf->setFilterColIndex(mwc.index);
        cf->setFilterCaseSencitive(mwc.cs);
        cf->setRegExpStr(mwc.pattern);
        colFilters.append(cf);
        connect(cf,SIGNAL(columnfilterChanged()),
                sm,SLOT(watchsChanged()));
    }
    setToolTip(mwd->toolTip);

    for(int i = 0; i < colFilters.count(); ++i)
         ui->WatchFrame->layout()->addWidget(colFilters.at(i));

    enabled = true;
    editAllow = true;
}

Watch::~Watch()
{
    delete ui;
}

void Watch::setIndex(int idx)
{
    index = idx;
    ui->label->setText(QString("%1").arg(index));
}

void Watch::on_closeButton_clicked()
{
    emit deleteWatch(index);
}

void Watch::on_enable_toggled(bool checked)
{
    if(checked)
        ui->enable->setIcon(QIcon(":img/online"));
    else
        ui->enable->setIcon(QIcon(":img/offline"));

    enabled = checked;

    emit enableWatch(checked);
}

void Watch::watchEnable(bool status)
{
    ui->enable->setChecked(status);
    on_enable_toggled(status);
}


bool Watch::loadActionPlugin(QString action)
{
    QDir pluginsDir = util::directoryOf(PLUGIN_MODEL_PATH);
    QString fileName = QString("%1%2%3")
            .arg(PLUGIN_ACTION_PREFIX)
            .arg(action).
            arg(PLUGIN_ACTION_POSFIX);

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" ||
            pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#endif
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
    QObject *plugin = pluginLoader.instance();
    if (plugin){
       actionManager = qobject_cast<ActionInterface *>(plugin);
        if (actionManager)
            return true;
    }
    return false;
}

#if 0
QAbstractItemModel *Watch::createModel()
{
        QString modelName = m_qs->value(CF_APP_PARSER).toString();
        loadPlugin(modelName);
        sm = modelManager->createModel(this);
        return sm;
}
#endif
