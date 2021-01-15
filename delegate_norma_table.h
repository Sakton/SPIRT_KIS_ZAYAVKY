#ifndef DELEGATE_NORMA_TABLE_H
#define DELEGATE_NORMA_TABLE_H
#include <QStyledItemDelegate>

class Delegate_Norma_Table : public QStyledItemDelegate
{
public:
  Delegate_Norma_Table(QObject *parent = nullptr);

  // QAbstractItemDelegate interface
public:
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DELEGATE_NORMA_TABLE_H
