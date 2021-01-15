#include <limits>
#include <sstream>
#include <QString>
#include <QStringList>
#include "document_norma.h"
#include "pole_norma.h"

Document_Norma::Document_Norma(/*QVector<Pole_Norma> v, */QString otdel, int year):/*polesDocumentNorma{v}, */otdel{otdel}, year{year}
  {
  }

std::ostream& Document_Norma::documentNormaCout(std::ostream& out) const
  {
    if(!this->getOtdel().isEmpty())
      {
        out << "<otdel> " << this->getOtdel().toStdString() << " </otdel>\n";
      }
    else
      {
        out << "<otdel> " << std::string("нет данных") << " </otdel>\n";
      }
    out << "<year> " << this->year << " </year>\n";
    out << "<size_pole_norma> " << this->getPolesNorma().size() << " </size_pole_norma>\n";
    if(!this->getPolesNorma().isEmpty())
      {
        for(Pole_Norma p : this->getPolesNorma())
          {
            out << p;
          }
      }
    return out;
  }

std::istream& Document_Norma::documentNormaCin(std::istream& in)
  {
    std::string s1;
    std::string s2;
    std::string s3;

    std::getline(in, s1);
    std::getline(in, s2);
    std::getline(in, s3);

    std::stringstream buf1(s1);
    std::vector<std::string>* v = new std::vector<std::string>();
    for(std::string s;buf1 >> s;)
      {
        v->push_back(s);
      }
    std::string otdel;
    for(unsigned int i = 1; i < v->size() - 1; ++i)
      {
        otdel += v->at(i);
        if(i != (v->size() - 2)) otdel += " ";
      }
    this->setOtdel(otdel);

    std::stringstream buf2(s2);
    std::string ss1, ss2;
    int year = 0;
    buf2 >> ss1 >> year >> ss2;
    this->setYear(year);
    ss1.clear();
    ss2.clear();

    std::stringstream buf3(s3);
    int size_v_pole_norma = 0;
    buf3 >> ss1 >> size_v_pole_norma >> ss2;

    for(int i = 0; i < size_v_pole_norma; ++i)
      {
        Pole_Norma* pnrm = new Pole_Norma();
        in >> *pnrm;
        this->addPole(*pnrm);
        delete pnrm;
      }

    return in;
  }

QTextStream& Document_Norma::documentNormaCout(QTextStream& out) const
  {
    {
      if(!this->getOtdel().isEmpty())
        {
          out << "<otdel> " << this->getOtdel() << " </otdel>\n";
        }
      else
        {
          out << "<otdel> " << QString("нет данных") << " </otdel>\n";
        }
      out << "<year> " << this->year << " </year>\n";
      out << "<size_pole_norma> " << this->getPolesNorma().size() << " </size_pole_norma>\n";
      if(!this->getPolesNorma().isEmpty())
        {
          for(Pole_Norma p : this->getPolesNorma())
            {
              out << p;
            }
        }
      return out;
    }
  }

QTextStream& Document_Norma::documentNormaCin(QTextStream& in)
  {
    QString s1;
    QString s2;
    QString s3;

    in.readLineInto(&s1);
    in.readLineInto(&s2);
    in.readLineInto(&s3);

    QStringList buf = s1.split( " ", Qt::SkipEmptyParts );
    QString otdel;
    for(int i = 1; i < buf.size() - 1; ++i)
      {
        otdel.append(buf.at(i));
        if(i != (buf.size() - 2)) otdel += " ";
      }
    this->setOtdel(otdel);
    buf.clear();

    buf = s2.split( " ", Qt::SkipEmptyParts );
    int year = buf.at(1).toInt();
    this->setYear(year);
    buf.clear();

    buf = s3.split( " ", Qt::SkipEmptyParts );
    int size_v_pole_norma = buf.at(1).toInt();

    for(int i = 0; i < size_v_pole_norma; ++i)
      {
        Pole_Norma* pnrm = new Pole_Norma();
        in >> *pnrm;
        this->addPole(*pnrm);
        delete pnrm;
      }

    return in;
  }

QTextStream& operator >>(QTextStream& in, Document_Norma& dn)
  {
    return dn.documentNormaCin(in);
  }

QTextStream& operator <<(QTextStream& out, const Document_Norma& dn)
  {
    return dn.documentNormaCout(out);
  }

std::istream& operator >> (std::istream& in, Document_Norma& dn)
  {
    return dn.documentNormaCin(in);
  }

std::ostream& operator << (std::ostream& out, const Document_Norma& dn)
  {
    return dn.documentNormaCout(out);
  }

double Document_Norma::summSpirtCurrentYear() const
  {
    double summ = 0.;
    for(Pole_Norma x : this->getPolesNorma())
      {
        if(x.getKolvoSpirtaPoInstr() < std::numeric_limits<double>::min())
          {
            summ += x.summa_spirt_na_god_po_stroke_nio();
          }
        else
          {
            summ += x.getKolvoSpirtaPoInstr();
          }
      }
    return summ;
  }

double Document_Norma::summSpirtNewYear() const
  {
    double summ = 0.;
    for(Pole_Norma x : this->getPolesNorma())
      {
        summ += x.getkolvoSpirtaPoInstr_NewYear();
      }
    return summ;
  }

void Document_Norma::setOtdel(const QString& otdel)
  {
    this->otdel = otdel;
  }

void Document_Norma::setOtdel( const std::string& otdel ) { this->setOtdel( QString::fromStdString( otdel ) ); }

void Document_Norma::addPole(const Pole_Norma& pn)
  {
    this->polesDocumentNorma.push_back(pn);
  }

void Document_Norma::addPoles(const QVector<Pole_Norma>& v_pn, bool erase)
  {
    if(erase) this->polesDocumentNorma.clear();
    for(Pole_Norma x : v_pn)
      {
        this->polesDocumentNorma.push_back(x);
      }
  }

bool Document_Norma::deletePole(int index)
  {
    if((index >= 0) && (index < this->polesDocumentNorma.size()))
      {
        this->polesDocumentNorma.remove(index);
        return true;
      }
    return false;
  }
