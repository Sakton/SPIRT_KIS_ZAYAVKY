#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "delegate_norma_table.h"

Delegate_Norma_Table::Delegate_Norma_Table(QObject *parent) : QStyledItemDelegate (parent)
{
}

QWidget *Delegate_Norma_Table::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if(index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 7 || index.column() == 12 || index.column() == 13)
    {
      QLineEdit *editor = new QLineEdit(parent);
      editor->setAutoFillBackground(true);
      return editor;
    }
  if(index.column() == 4 || index.column() == 5 || index.column() == 9 || index.column() == 10)
    {
      QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
      editor->setAutoFillBackground(true);
      editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
      return editor;
    }
  if(index.column() == 6 || index.column() == 11)
    {
      QSpinBox *editor = new QSpinBox(parent);
      editor->setAutoFillBackground(true);
      editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
      return editor;
    }
  return nullptr;
}

void Delegate_Norma_Table::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if(index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 7 || index.column() == 12 || index.column() == 13)
    {
      QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
      lineEdit->setText(index.model()->data(index).toString());
    }
  if(index.column() == 4 || index.column() == 5 || index.column() == 9 || index.column() == 10)
    {
      QDoubleSpinBox *dSpinBox = qobject_cast<QDoubleSpinBox*>(editor);
      dSpinBox->setAutoFillBackground(true);
      dSpinBox->setValue(index.model()->data(index).toDouble());
    }
  if(index.column() == 6 || index.column() == 11)
    {
      QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor);
      spinBox->setValue(index.model()->data(index).toInt());
    }
}

void Delegate_Norma_Table::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if(index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 7 || index.column() == 12 || index.column() == 13)
    {
      QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
      model->setData(index, lineEdit->text());
    }
  if(index.column() == 4 || index.column() == 5 || index.column() == 9 || index.column() == 10)
    {
      QDoubleSpinBox *dSpinBox = qobject_cast<QDoubleSpinBox*>(editor);
      model->setData(index, dSpinBox->value());
    }
  if(index.column() == 6 || index.column() == 11)
    {
      QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor);
      model->setData(index, spinBox->value());
    }
}

void Delegate_Norma_Table::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyledItemDelegate::paint(painter, option, index);
}

void Delegate_Norma_Table::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  editor->setGeometry(option.rect);
}
