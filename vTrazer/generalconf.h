#ifndef generalCONF_H
#define generalCONF_H

#include <QWidget>
#include <QSettings>
#include "ui_generalconf.h"

namespace Ui {
class generalConf;
}


class generalConf : public QWidget
{
    Q_OBJECT
public:
    generalConf(QSettings *pqs,QWidget *parent = 0);
    ~generalConf();
    void loadModelPlugin();

protected:

private:
    Ui::generalConf *ui;
    bool      editAllow;
    QSettings *m_qs;
    QHash<QString,QString> lang;

private slots:
    void on_langBox_currentIndexChanged(QString value);
    void on_models_currentIndexChanged(const QString &arg1);
};

#endif
