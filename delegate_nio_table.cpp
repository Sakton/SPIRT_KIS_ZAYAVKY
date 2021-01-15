#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "delegate_nio_table.h"
//делать сразу методы createEditor, setEditorData, setModelData и потом проверять

Delegate_Nio_Table::Delegate_Nio_Table(QObject *parent) : QStyledItemDelegate (parent)
{
}

QWidget *Delegate_Nio_Table::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if(index.column() == 1)
    {
      QLineEdit *editor = new QLineEdit(parent);
      editor->setText(index.model()->data(index).toString());
      editor->setAutoFillBackground(true);
      return editor;
    }
  if(index.column() == 2)
    {
      QSpinBox *editor = new QSpinBox(parent);
      editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
      editor->setAutoFillBackground(true);
      return editor;
    }
  if((index.column() >= 3) && (index.column() <= 15))
    {
      QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
      editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
      editor->setAutoFillBackground(true);
      editor->setDecimals(3); //знаки после запятой
      return editor;
    }
  return nullptr;
}

void Delegate_Nio_Table::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  //установка виджета в ячейки и задание размера с ячейку
  editor->setGeometry(option.rect);
}

void Delegate_Nio_Table::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if(index.column() == 1)
    {
      QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
      lineEdit->setText(index.model()->data(index).toString());
    }
  if(index.column() == 2)
    {
      QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
      spinbox->setValue(index.model()->data(index).toInt());
    }
  if((index.column() >= 3) && (index.column() <= 15))
    {
      QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
      doubleSpinBox->setValue(index.model()->data(index).toDouble());
    }
}

void Delegate_Nio_Table::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if(index.column() == 1)
    {
      QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
      model->setData(index, lineEdit->text());
    }
  if(index.column() == 2)
    {
      QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
      model->setData(index, spinbox->value());
    }
  if((index.column() >= 3) && (index.column() <= 15))
    {
      QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
      model->setData(index, doubleSpinBox->value());
    }
}

void Delegate_Nio_Table::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  //взять метод паинт у родителя, иначе не пишет данные..
  QStyledItemDelegate::paint(painter, option, index);
}

QSize Delegate_Nio_Table::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  // return QAbstractItemDelegate::sizeHint( option, index );
  return QSize( option.widget->width( ), option.widget->height( ) );
}
