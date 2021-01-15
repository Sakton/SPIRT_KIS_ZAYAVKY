#include <sstream>
#include <QDebug>
#include <vector>
#include <QStringList>
#include "document_nio_year.h"

Document_nio_year::Document_nio_year(int year, QString otdel):/*poles{pn},*/year{year},otdel{otdel}
  {
    this->itogo = new Pole_Nio();//FIXME обьект класса Pole_Nio??? или просто вектор?
  }

Document_nio_year::Document_nio_year(const Document_nio_year& dNio)
  {
    this->setPoles(dNio.getPoles());
    this->setOtdel(dNio.getOtdel());
    this->setYear(dNio.getYear());
  }

Document_nio_year::~Document_nio_year()
  {
    delete this->itogo;
  }

std::ostream& Document_nio_year::documentNioYearCout(std::ostream& out) const
  {
    out << "<otdel> ";
    if(this->getOtdel() != "")
      {
        out << this->getOtdel().toStdString();
      }
    else
      {
        out << std::string("отдел не выбран");
      }
    out << " </otdel>\n";

    out << "<year> ";
    out << this->getYear();
    out << " </year>\n";

    out << "<size_pole_nio_vector> ";
    out << this->getPoles().size();
    out << " </size_pole_nio_vector>\n";

    if(!this->getPoles().isEmpty())
      {
        for(Pole_Nio p : this->getPoles())
          {
            out << p << "\n";
          }
      }
    return out;
  }

std::istream& Document_nio_year::documentNioYearCin(std::istream& inpt)
  {
    std::string s1 = "";
    std::string s2 = "";
    std::string s3 = "";

    std::getline(inpt, s1);
    std::getline(inpt, s2);
    std::getline(inpt, s3);

    std::stringstream sstr1(s1);
    std::vector<std::string>* v_s1 = new std::vector<std::string>();
    for(std::string buf; sstr1 >> buf;)
      {
        v_s1->push_back(buf);
      }
    std::string otdel = "";
    for(unsigned int i = 1; i < v_s1->size()-1; ++i)
      {
        otdel += v_s1->at(i) + " ";
      }
    this->setOtdel(otdel);

    std::string bufff1, bufff2;
    std::stringstream sstr2(s2);
    int year;
    sstr2 >> bufff1 >> year >> bufff2;
    this->setYear(year);

    std::stringstream sstr3(s3);
    int size_vector = 0;
    sstr3 >> bufff1 >> size_vector >> bufff2;

    for(int i = 0; i < size_vector; ++i)
      {
        Pole_Nio* p = new Pole_Nio();
        inpt >> *p;
        this->setPoles(*p);
        delete p;
      }
    return inpt;
  }

QTextStream& Document_nio_year::documentNioYearCout(QTextStream& out) const
  {
    out << "<otdel> ";
    if(this->getOtdel() != "")
      {
        out << this->getOtdel();
      }
    else
      {
        out << QString("отдел не выбран");
      }
    out << " </otdel>\n";
    out << "<year> " << this->getYear() << " </year>\n";
    out << "<size_pole_nio_vector> " << this->getPoles().size() << " </size_pole_nio_vector>\n";
    if(!this->getPoles().isEmpty())
      {
        for(Pole_Nio p : this->getPoles())
          {
            out << p << "\n";
          }
      }
    return out;
  }

QTextStream& Document_nio_year::documentNioYearCin(QTextStream& inpt)
  {
    inpt.setLocale(QLocale::Russian);
    QStringList* buffer = new QStringList();
    QString* s1 = new QString();
    QString* s2 = new QString();
    QString* s3 = new QString();

    inpt.readLineInto(s1,0);
    inpt.readLineInto(s2,0);
    inpt.readLineInto(s3,0);

    *buffer = s1->split( " ", Qt::SkipEmptyParts );
    QString* otdelName = new QString();
    for(int i = 1; i < buffer->size()-1; ++i)
      {
        otdelName->append(buffer->at(i));
        if((buffer->size()-2) != i) otdelName->append(' ');
      }
    this->setOtdel(*otdelName);
    buffer->clear();

    *buffer = s2->split( " ", Qt::SkipEmptyParts );
    int year = buffer->at(1).toInt();
    this->setYear(year);
    buffer->clear();

    *buffer = s3->split( " ", Qt::SkipEmptyParts );
    int size_vector = 0;
    size_vector = buffer->at(1).toInt();
    buffer->clear();

    for(int i = 0; i < size_vector; ++i)
      {
        Pole_Nio* p = new Pole_Nio();
        inpt >> *p;
        this->setPoles(*p);
        delete p;
      }
    return inpt;
  }

Pole_Nio& Document_nio_year::itog()
  {
    Pole_Nio *itog = new Pole_Nio();//обьект класса Pole_Nio??? или просто вектор?
    QVector<double> buffer_itogo(12,0);
    itog->setIndexNio(QString("ITOGO"));
    for(int i = 0; i < this->poles.size(); ++i)
      {
        for(int j = 0; j < itog->month; ++j)
          {
            buffer_itogo[j] += this->poles.at(i).getNormaMonth().at(j);
          }
      }
    itog->setNormaMonth(buffer_itogo);
    return *itog;
  }

void Document_nio_year::setItogo()
  {
    QVector<double> buffer_itogo(12,0);
    int summ_kompl = 0;
    this->summ_spirt_year = 0;
    for(int i = 0; i < this->poles.size(); ++i)
      {
        for(int j = 0; j < this->itogo->month; ++j)
          {
            buffer_itogo[j] += this->poles.at(i).getNormaMonth().at(j);
            this->summ_spirt_year += this->poles.at(i).getNormaMonth().at(j);
          }
        summ_kompl += this->poles.at(i).getKolichestvoKomplectov();
      }
    this->itogo->setIndexNio(QString("ИТОГО:"));
    this->itogo->setKolichestvoKomlectov(summ_kompl);
    this->itogo->setNormaMonth(buffer_itogo);
  }

void Document_nio_year::setPoles(const QVector<Pole_Nio> &pn)
  {
    this->poles.clear();
    for(Pole_Nio p : pn)
      {
        this->setPoles(p);
      }
    this->setItogo();
  }

void Document_nio_year::setPoles(const Pole_Nio &pn)
  {
    this->poles.push_back(pn);
    this->setItogo();
  }

void Document_nio_year::setYear(int year)
  {
    if(year > 2016 && year < 2030)
      {
        this->year = year;
      }
  }

void Document_nio_year::setOtdel(const QString otdel)
  {
    if(!otdel.isEmpty()) //добавить проверку на чушь. (может на соответствие в базе, может в виджете)
      {
        this->otdel = otdel;
      }
  }

  void Document_nio_year::setOtdel( const std::string& otdel ) {
    if(otdel != "")
      {
        this->otdel = QString::fromStdString(otdel);
      }
  }

bool Document_nio_year::deletePoles(int index)
  {
    if(!this->poles.isEmpty() && (this->poles.count() > index) && (this->poles.count() >= 0))
      {
        this->poles.remove(index);
        return true;
      }
    return false;
  }

const Pole_Nio &Document_nio_year::getItogoPoNio() const
  {
    return *this->itogo;
  }

std::istream& operator >> (std::istream& inpt, Document_nio_year& d_n_year)
  {
    return d_n_year.documentNioYearCin(inpt);
  }

std::ostream& operator << (std::ostream& out, const Document_nio_year& d_n_year)
  {
    return d_n_year.documentNioYearCout(out);
  }

QTextStream& operator << (QTextStream& out, const Document_nio_year& d_n_year)
  {
    return d_n_year.documentNioYearCout(out);
  }

QTextStream& operator >> (QTextStream& inpt, Document_nio_year& d_n_year)
  {
    return d_n_year.documentNioYearCin(inpt);
  }
