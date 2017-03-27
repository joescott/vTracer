#ifndef LOADFILEPROGRESSBAR_H
#define LOADFILEPROGRESSBAR_H

#include <QDialog>
#include <QTime>

namespace Ui {
class LoadFileProgressBar;
}

class LoadFileProgressBar : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoadFileProgressBar(QWidget *parent = 0);
    ~LoadFileProgressBar();
    void setProgress( int progress, int lines);

signals:
    void cancelLoad();

private slots:
    void on_stopLoadButton_clicked();

private:
    Ui::LoadFileProgressBar *ui;
    QTime                   timeElapsed;
};

#endif // LOADFILEPROGRESSBAR_H
