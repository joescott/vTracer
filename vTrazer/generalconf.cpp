#include <QFileDialog>
#include "mainwindow.h"
#include <QtCore>
#include "def.h"
#include "util.h"
#include "generalconf.h"

generalConf::generalConf(QSettings *pqs,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::generalConf),
    editAllow(false),
    m_qs(pqs)
{
    ui->setupUi(this);
    LANG_DEFINITION(lang);


   ui->langBox->addItems(lang.values());
   ui->langBox->setCurrentIndex(
               ui->langBox->findText(lang[m_qs->value(CF_LANGUAGE).toString()]));

   loadModelPlugin();
   QString b = m_qs->value(CF_APP_PARSER).toString();
   int a = ui->models->findText(b);
   ui->models->setCurrentIndex(a);

   editAllow = true;
}

generalConf::~generalConf()
{
}

void generalConf::on_langBox_currentIndexChanged(QString value)
{
    if(editAllow)
    {
        QHash<QString, QString>::iterator i;
        for (i = lang.begin(); i != lang.end(); ++i)
             if(i.value() == value)
             {
                 m_qs->setValue(CF_LANGUAGE,i.key());
                 break;
             }
    }
}

void generalConf::loadModelPlugin()
{
    QDir pluginsDir = util::directoryOf(PLUGIN_MODEL_PATH);

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" ||
            pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#endif
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QRegExp rxlen("(?:lib)(.*)(?:\\.so)");
        if(rxlen.indexIn(fileName) > -1)
            ui->models->addItem(rxlen.cap(1));
    }
}

void generalConf::on_models_currentIndexChanged(const QString &arg1)
{
    if(editAllow)
        m_qs->setValue(CF_APP_PARSER,arg1);
}
