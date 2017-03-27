#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>

class ItemDelegate : public QItemDelegate
{

public:


    ItemDelegate(){}

#if 0
    void paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
    {

        //QItemDelegate::paint(painter, option, index);
        QStyleOptionViewItem  viewOption(option);
        painter->setRenderHint(QPainter::Antialiasing, true);
        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
            painter->setBrush(option.palette.highlightedText());
        }
        else
            painter->fillRect(viewOption.rect, Qt::darkGreen);

        painter->drawText(viewOption.rect, Qt::AlignCenter, index.model()->data(index, Qt::EditRole).toString());
    }
#endif

    QWidget *createEditor(QWidget */*parent*/,
                          const QStyleOptionViewItem &/* option */,
                          const QModelIndex &/* index */) const
    {
        return NULL;
    }

    QSize sizeHint ( const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */ ) const
    {
        return QSize(50,16);
    }
};
#endif // ITEMDELEGATE_H
