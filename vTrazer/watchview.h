#ifndef WATCHVIEW_H
#define WATCHVIEW_H

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class WatchView;
}

class WatchView : public QWidget
{
    Q_OBJECT
    
public:
    explicit WatchView(QWidget *parent = 0);
    ~WatchView();
    void addAlarm(QAbstractItemModel *sm, QByteArray line, int row);

private:
    QAbstractItemModel *wm;
    Ui::WatchView *ui;

private slots:
    void on_watchClicked(QModelIndex index);

signals:
    void watchSelected(int index);

};

#endif // WATCHVIEW_H
