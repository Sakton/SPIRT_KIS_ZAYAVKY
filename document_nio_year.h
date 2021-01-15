#ifndef DOCUMENT_NIO_YEAR_H
#define DOCUMENT_NIO_YEAR_H
#include <QVector>
#include <QString>
#include <QTextStream>
#include <iostream>
#include <QDate>
#include "pole_nio.h"

class Pole_Nio;

class Document_nio_year
{
  QVector<Pole_Nio> poles;
  Pole_Nio *itogo;
  int year;
  double summ_spirt_year;
  QString otdel;

private:
  //void setItogo();

public:
  std::ostream& documentNioYearCout(std::ostream& out) const;
  std::istream& documentNioYearCin(std::istream& inpt);
  QTextStream& documentNioYearCout(QTextStream& out) const;
  QTextStream& documentNioYearCin(QTextStream& inpt);
  friend std::ostream& operator << (std::ostream& out, const Document_nio_year& d_n_year);
  friend std::istream& operator >> (std::istream& inpt, Document_nio_year& d_n_year);
  friend QTextStream& operator << (QTextStream& out, const Document_nio_year& d_n_year);
  friend QTextStream& operator >> (QTextStream& inpt, Document_nio_year& d_n_year);

  Document_nio_year(/*QVector<Pole_Nio> pn = QVector<Pole_Nio>(), */int year = QDate().currentDate().year(), QString otdel = "");
  Document_nio_year(const Document_nio_year& dNio);
  ~Document_nio_year();

  Pole_Nio& itog(); //перенос, но есть *itogo ???
  //сеттеры
  void setPoles(const QVector<Pole_Nio> &vecPn);
  void setPoles(const Pole_Nio &pn);
  void setYear(int year);
  void setOtdel(const QString otdel);
  void setOtdel(const std::string& otdel);
  bool deletePoles(int index);
  void setItogo();
  //TODO ???
  //попробовать сделать через буферный вектор, а потом переписывать или менять вектор в поле ?????
  QVector<Pole_Nio>& setPolesFromEdit() { return this->poles; } //переделать на новый метод с аргументом

  //геттеры
  const QVector<Pole_Nio>& getPoles() const { return  this->poles; }
  int getYear() const { return this->year; }
  const QString getOtdel() const { return this->otdel; }
  int getRowPoles(){ return this->getPoles().size(); }
  const Pole_Nio& getItogoPoNio() const;
  double getSpirtNioYear() const { return this->summ_spirt_year; }
};

std::istream& operator >> (std::istream& inpt, Document_nio_year& d_n_year);
std::ostream& operator << (std::ostream& out, const Document_nio_year& d_n_year);
QTextStream& operator << (QTextStream& out, const Document_nio_year& d_n_year);
QTextStream& operator >> (QTextStream& inpt, Document_nio_year& d_n_year);

#endif // DOCUMENT_NIO_YEAR_H
