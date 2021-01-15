#ifndef MODEL_NIO_DOCUMENT_H
#define MODEL_NIO_DOCUMENT_H

#include <QAbstractTableModel>
#include "document_nio_year.h"

class Model_Nio_Document : public QAbstractTableModel
  {
    Q_OBJECT

  public:
    static constexpr int columns = 16;
    static constexpr int monate = 12;

    explicit Model_Nio_Document (QObject* parent = nullptr);
    ~Model_Nio_Document();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //возвращает значение элемента
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    //сохраняет новое значение элемента
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    //возвращает параметры редактируемости элемента
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    //геттер
    const Pole_Nio &getItogoPoleNio() const;
    double getSpirtYear() const { return this->doc->getSpirtNioYear(); }
    //возврат документа для печати
    const Document_nio_year* getDocumentNioYear() const { return this->doc; }
    //сеттеры
    void setDocumentRead(const Document_nio_year& dNio);// для считывания документа из файла и обновления модели
    void setOtdel(const QString& otdel);
    void setDate(int year);
    //из привата
  private:
    Document_nio_year *doc;
    //****

  signals:
    void myChangeSignal();
  };

#endif // MODEL_NIO_DOCUMENT_H
