#ifndef WATCHMODEL_H
#define WATCHMODEL_H

class WatchModel
{
public:
    WatchModel();
    QAbstractItemModel *createWatchModel(QWidget *parent);
};

#endif // WATCHMODEL_H
