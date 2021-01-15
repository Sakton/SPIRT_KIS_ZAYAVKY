#ifndef DOCUMENT_NORMA_H
#define DOCUMENT_NORMA_H
#include <QVector>
#include <iostream>
#include <QTextStream>
#include <QDate>
#include "pole_norma.h"


class Document_Norma
  {
    QVector<Pole_Norma> polesDocumentNorma;
    QString otdel;
    int year;
  public:
    Document_Norma(/*QVector<Pole_Norma> v = QVector<Pole_Norma>() ,*/QString otdel = QString(""), int year = QDate().currentDate().year());

    std::ostream& documentNormaCout(std::ostream& out) const;
    std::istream& documentNormaCin(std::istream& in);
    QTextStream& documentNormaCout(QTextStream& out) const;
    QTextStream& documentNormaCin(QTextStream& in);
    friend std::ostream& operator << (std::ostream& out, const Document_Norma& dn);
    friend std::istream& operator >> (std::istream& in, Document_Norma& dn);
    friend QTextStream& operator << (QTextStream& out, const Document_Norma& dn);
    friend QTextStream& operator >> (QTextStream& in, Document_Norma& dn);

    double summSpirtCurrentYear() const;
    double summSpirtNewYear() const;
    //getters
    const Pole_Norma& getPoleNorma(int index) const { return this->polesDocumentNorma.at(index); }
    const QVector<Pole_Norma>& getPolesNorma() const { return this->polesDocumentNorma; }
    const QString getOtdel() const { return this->otdel; }
    int getYear() const { return this->year; }
    //setters
    void setOtdel(const QString& otdel);
    void setOtdel(const std::string& otdel);
    void setYear(int year) { this->year = year; }
    void addPole(const Pole_Norma& pn);
    void addPoles(const QVector<Pole_Norma>& v_pn, bool erase); //замена полей с спиртом... мож пригодится
    bool deletePole(int index);
    QVector<Pole_Norma>& setPolesFromEdit() { return this->polesDocumentNorma; }
  };

std::ostream& operator << (std::ostream& out, const Document_Norma& dn);
std::istream& operator >> (std::istream& in, Document_Norma& dn);
QTextStream& operator << (QTextStream& out, const Document_Norma& dn);
QTextStream& operator >> (QTextStream& in, Document_Norma& dn);

#endif // DOCUMENT_NORMA_H
