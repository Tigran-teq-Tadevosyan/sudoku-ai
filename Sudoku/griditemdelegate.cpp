#include "griditemdelegate.h"
#include <QPainter>
#include <QDebug>

GridItemDelegate::GridItemDelegate(QObject *parent) : QItemDelegate(parent)
{
  pen.setColor( Qt::black );
  pen.setWidth( 3 );
}

void GridItemDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const {
  QItemDelegate::paint( painter, option, index );
  const QRect rect( option.rect );
  painter->setPen( pen );
  if( index.row() != 0 && index.row()%3 == 0 ){
     painter->drawLine(rect.topLeft(),rect.topRight());
  }
  if( index.column() != 0 && index.column()%3 == 0 ){
      painter->drawLine(rect.topLeft(),rect.bottomLeft());
  }
}
