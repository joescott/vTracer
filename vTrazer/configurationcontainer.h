#ifndef CONFIGURATIONCONTAINER_H
#define CONFIGURATIONCONTAINER_H

#include <QStackedWidget>

namespace Ui {
class configurationContainer;
}

class configurationContainer : public QStackedWidget
{
    Q_OBJECT

public:
    explicit configurationContainer(QWidget *parent = 0);
    ~configurationContainer();

private:
    Ui::configurationContainer *ui;
};

#endif // CONFIGURATIONCONTAINER_H
