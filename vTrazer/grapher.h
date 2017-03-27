#ifndef GRAPHER_H
#define GRAPHER_H

#include <QWidget>
#include "graphwindow.h"

namespace Ui {
class Grapher;
}

class Grapher : public QWidget
{
    Q_OBJECT
    
public:
    explicit Grapher(QWidget *parent = 0);
    ~Grapher();


private slots:
    void on_actionNew_triggered();

    void on_graphList_currentIndexChanged(int index);

    void on_subWindowsClosed(GraphWindow *w);

    void on_actionCascade_toggled(bool arg1);
    
    void on_actionTile_toggled(bool arg1);
    
private:
    Ui::Grapher *ui;

    void createSubWindow();
};

#endif // GRAPHER_H
