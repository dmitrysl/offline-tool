#ifndef DELEGATE_H
#define DELEGATE_H

#include <QWidget>
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QString>

class Delegate : public QItemDelegate
 {
 Q_OBJECT
 public:
 Delegate(QWidget *parent = 0) : QItemDelegate(parent) {}
 ~Delegate() {}
 void paint(QPainter *painter, const QStyleOptionViewItem &option,
                const QModelIndex &index) const;
 };

#endif // DELEGATE_H
