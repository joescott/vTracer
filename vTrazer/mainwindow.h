#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QToolBox>

#include "filter.h"
#include "sessionmanager.h"
#include "runapp.h"
#include "output.h"
#include "proxymodel.h"
#include "loadfileprogressbar.h"
#include "filtertool.h"
#include "watchtool.h"
#include "watchview.h"
#include "grapher.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSettings *qs, QWidget *parent = 0);
    ~MainWindow();
    QDir directoryOf(const QString &subdir);

private:
    Ui::MainWindow        *     ui;
    QSettings             *     m_qs;
    QAbstractItemModel    *     sourceModel;
    ProxyModel            *     proxyModel;

    LoadFileProgressBar   *     lpbar;
    SessionManager              sm;
    RunApp                      rapp;
    Output                      out;
    QModelIndexList             sIndexList;
    QModelIndexList::iterator   sCurrentIndex;

    WatchView                   *watchView;
    QToolBox                    toolBox;
    FilterTool                  *filterTool;
    WatchTool                   *watchTool;
    Grapher                     *grapher;

void openAtResult(QWidget *w, QString str);

public slots:
    void About();
    void sessionClear();
    void addFilterFromSession(Filter *filter);
    void addWatchFromSession(Watch *watch);
    void appReadyRead(QByteArray line, int row);
    void appErrorRead(QByteArray line);
    void appEndReadFile();
    void appReadyLines(int prf, int totalLines);
    void filtersChanged();
    void watchsChanged();
    void watchTrigger(QByteArray line, int row);
    void watchSelected(int row);
    void gen_filter();
    void gen_watch();

private slots:
    void on_actionConfigure_triggered();
    void on_ResultTabWidget_tabCloseRequested(int index);
    void on_actionManual_triggered();
    void on_actionSessionManager_triggered();
    void on_actionQuit_triggered();
    void on_actionShow_Full_Screen_toggled(bool arg1);
    void on_actionRun_triggered();
    void on_actionOutput_triggered();
    void on_actionFind_triggered();
    void on_nextSearch_clicked();
    void on_backSearch_clicked();

    void on_hideButton_clicked();

    void on_actionOpen_triggered();

    void on_regexpEdit_returnPressed();

    void on_actionWatch_triggered();

    void on_actionGraph_triggered();

    void on_customContextMenu(const QPoint& _point);

protected:
     void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
