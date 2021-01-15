#ifndef DELEGATE_NIO_TABLE_H
#define DELEGATE_NIO_TABLE_H
#include <QStyledItemDelegate>
#include <QWidget>


class Delegate_Nio_Table : public QStyledItemDelegate
{

public:
  Delegate_Nio_Table(QObject* parent = nullptr);

  //Возвращает редактора, чтобы использоваться для редактирования элемента данных с данным индексом.
  //Обратите внимание на то, что индекс содержит информацию об используемой модели.
  //Родительский виджет редактора указан родителем и опционами позиции опционом.
  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

  // QAbstractItemDelegate interface
  //Эта чистая абстрактная функция должна быть повторно реализована, если вы хотите обеспечить пользовательское предоставление.
  //Используйте живописца и параметр стиля для предоставления позиции, указанной индексом позиции.
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

  //Эта чистая абстрактная функция должна быть повторно реализована, если вы хотите обеспечить пользовательское предоставление.
  //Опционы указаны опционом и модельной позицией индексом.
  // ***Возвращает размер, необходимый делегату для
  // ***отображения или редактирования элемента
  // ***с модельным индексом index
  QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

  //Устанавливает данные для позиции в данном индексе в модели к содержанию данного редактора.
  void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

  //Устанавливает содержание данного редактора к данным для позиции в данном индексе.
  //Обратите внимание на то, что индекс содержит информацию об используемой модели.
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;

  //Обновляет геометрию редактора для позиции с данным индексом, согласно прямоугольнику, указанному в опционе.
  //Если позиция будет иметь внутреннее расположение, то редактор будет размечен соответственно.
  //Обратите внимание на то, что индекс содержит информацию об используемой модели.
  void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // DELEGATE_NIO_TABLE_H
