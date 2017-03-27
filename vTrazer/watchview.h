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
    void addAlarm(QVariant data);

private:
    Ui::WatchView *ui;
    QAbstractItemModel *wm;
};

#endif // WATCHVIEW_H
