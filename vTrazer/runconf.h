#ifndef runCONF_H
#define runCONF_H

#include <QWidget>
#include <QSettings>
#include "ui_runconf.h"

namespace Ui {
class runConf;
}


class runConf : public QWidget
{
    Q_OBJECT
public:
    runConf(QSettings *pqs,QWidget *parent = 0);
    ~runConf();

protected:

private:
    Ui::runConf *ui;
    bool      editAllow;
    QSettings *m_qs;

private slots:
    void on_appPath_editingFinished();
    void on_getAppButton_clicked();
    void on_appOptions_editingFinished();
};

#endif
