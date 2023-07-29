#ifndef GRIDITEMDELEGATE_H
#define GRIDITEMDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QPen>

class GridItemDelegate : public QItemDelegate
{
public:
  explicit GridItemDelegate(QObject *parent = 0);
  void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

signals:

public slots:

private:
  QPen pen;
};

#endif // GRIDITEMDELEGATE_H
