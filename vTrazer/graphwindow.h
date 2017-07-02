#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include "sessionmanager.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QWidget
{
    Q_OBJECT
    
public:
    int index;
    explicit GraphWindow(int index, SessionManager *sm, QWidget *parent = 0);
    ~GraphWindow();

    void closeEvent(QCloseEvent *event);
    
private:
    Ui::GraphWindow *ui;


signals:
    void closed(GraphWindow *w);

protected:
    SessionManager  *sm;

};
#endif // GRAPHWINDOW_H
