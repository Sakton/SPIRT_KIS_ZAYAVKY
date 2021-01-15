#ifndef MODEL_NORMA_DOCUMENT_H
#define MODEL_NORMA_DOCUMENT_H
#include <QAbstractTableModel>
#include "document_norma.h"

class Document_Norma;

class Model_Norma_Document : public QAbstractTableModel
{
  Q_OBJECT

const int columnCounts = 14;

Document_Norma* documentNorma;
public:
  Model_Norma_Document(QObject *parent = nullptr);
  /*const */Document_Norma& getDocument() const { return *this->documentNorma; }
  ~Model_Norma_Document();

  int rowCount(const QModelIndex &parent = QModelIndex()) const override; // QModelIndex &parent = QModelIndex()!!!!!!!! по умолчанию
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool insertRows(int row, int count, const QModelIndex &parent) override;
  bool removeRows(int row, int count, const QModelIndex &parent) override;
  //геттеры
  const Document_Norma* getDocumentNorma() const { return this->documentNorma; }
  //сеттеры
  void setDocumentNormaRead(const Document_Norma& docNorm);
  void setOtdel(const QString& otdel);
  void setDate(int year);
signals:
  void myChangeNormaSignal();
};

#endif // MODEL_NORMA_DOCUMENT_H
