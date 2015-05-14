#include "delegate.h"


void Delegate::paint(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{
//    painter->fillRect(option.rect, QColor(255, 255, 255));

    //option.palette.setColor(QPalette::Window, QColor(255, 255, 204));
//    QString val;
//    if (qVariantCanConvert<QString>(index.data()))
//        val = qVariantValue<QString>(index.data());
//    if (val == "1")
//    {
//        painter->fillRect(option.rect, option.palette.highlight());
//    }
//    else
        QItemDelegate::paint(painter, option, index);
}
