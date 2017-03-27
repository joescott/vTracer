#ifndef COLUMNFILTER_H
#define COLUMNFILTER_H

#include <QFrame>

#include <QSortFilterProxyModel>

namespace Ui {
class ColumnFilter;
}

class ColumnFilter : public QFrame
{
    Q_OBJECT
    
public:
    explicit ColumnFilter(QAbstractProxyModel *proxyModel,
                          QString regStr = 0, int colIndex = 0, bool cs = 0,
                          QWidget *parent = 0);
    ~ColumnFilter();
    bool getFilterCaseSencitive();
    void setFilterCaseSencitive(bool status);
    int  getFilterColIndex();
    void setFilterColIndex(int index);
    QString getRegExpStr();
    void setRegExpStr(QString regexp);


signals:
    void columnfilterChanged();

private slots:
    void on_RegExp_textChanged(const QString &arg1);

    void on_FilterColumn_currentIndexChanged(int index);

    void on_CaseSencitive_clicked(bool checked);

private:
    Ui::ColumnFilter    *ui;
    QAbstractProxyModel *pm;


    void fillFilterColFromModel(QAbstractProxyModel *model);
};

#endif // COLUMNFILTER_H
