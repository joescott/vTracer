#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>

namespace Ui {
class Output;
}

class Output : public QWidget
{
    Q_OBJECT
    
public:
    explicit Output(QWidget *parent = 0);
    ~Output();

    void append(QByteArray line);
    void appendError(QByteArray line);

private:
    Ui::Output *ui;
};

#endif // OUTPUT_H
