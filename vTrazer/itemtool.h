#ifndef ITEMTOOL_H
#define ITEMTOOL_H

#include "sessionmanager.h"

#include <QWidget>
#include <QStringList>

namespace Ui {
class itemTool;
}

class itemTool : public QWidget
{
    Q_OBJECT
    
public:
    explicit itemTool(SessionManager *sessionManager,QWidget *parent = 0);
    ~itemTool();
    void addTypes(QStringList list);
    virtual QWidget *itemAddDefinition(int index){return 0;}
    virtual void itemDelDefinition(int index){}
    void addItemFromSession(QWidget *widget);
    void deleteAllItems();

signals:
    void itemsChanged();
    void allItemsEnable(bool);

public slots:
    void deleteItem(int index);
    void enableItem(bool status);
    virtual void enableAllItems(bool checked){}

private slots:
    void on_addItemButton_clicked();
    void on_enable_clicked(bool checked);

protected:
    Ui::itemTool    *ui;
    SessionManager  *sm;
};

#endif // ITEMTOOL_H
