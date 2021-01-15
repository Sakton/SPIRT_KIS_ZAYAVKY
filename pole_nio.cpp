#include <QString>
#include <string.h>
#include <QVector>
#include <climits>
#include <QDebug>
#include <QList>
#include <ctype.h>
#include <vector>
#include <sstream>
#include <codecvt>
#include <QTextStream>
#include <QLatin1String>
#include "pole_nio.h"

Pole_Nio::Pole_Nio(QString indxNio, int komplekty, QVector<double> v) : indexNio{indxNio}, kolichestvoKomplectov{komplekty}, norma_month(v)
  {
  }

Pole_Nio::Pole_Nio(const Pole_Nio &a) : indexNio{a.indexNio}, kolichestvoKomplectov{a.kolichestvoKomplectov}
  {
    if(!norma_month.isEmpty()) this->norma_month.clear();
    this->norma_month = a.norma_month;
  }

Pole_Nio::~Pole_Nio()
  {
  }

Pole_Nio& Pole_Nio::operator + (const Pole_Nio &a)
  {
    if(this->indexNio == a.indexNio)
      {
        this->kolichestvoKomplectov += a.kolichestvoKomplectov;
      }
    if(this->norma_month.size() == a.norma_month.size())
      {
        for(int i = 0; i < this->norma_month.size(); ++i)
          {
            this->norma_month[i] += a.norma_month.at(i);
          }
      }
    return *this;
  }

bool Pole_Nio::sravnenye_vectorov(const QVector<double> &a, const QVector<double> &b) const
  {
    bool flag = 0;
    if(a.size() == b.size())
      {
        for(int i = 0; i < a.size(); ++i)
          {
            if(this->is_equal(a.at(i), b.at(i)))
              {
                flag = true;
              }
            else
              {
                flag = false;
              }
            if(!flag)
              {
                return false;
              }
          }
      }
    return false;
  }

bool Pole_Nio::is_equal(const double &x, const double &y) const
  {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
  }

Pole_Nio& Pole_Nio::operator = (const Pole_Nio &a)
  {
    if(this != &a) //проверка на самоприсваивание
      {
        if(!this->norma_month.empty())
          {
            this->norma_month.clear();
          }
        for(int i = 0; i < a.norma_month.size(); ++i)
          {
            this->norma_month.push_back(a.norma_month.at(i));
          }
        if(!this->indexNio.isEmpty())
          {
            this->indexNio.clear();
            this->indexNio = a.indexNio;
          }
        this->kolichestvoKomplectov = a.kolichestvoKomplectov;
      }
    return *this;
  }

bool Pole_Nio::operator == (const Pole_Nio &a)
  {
    if((this->kolichestvoKomplectov == a.kolichestvoKomplectov) && (this->indexNio == a.indexNio))
      {
        int flag = 0;
        for(int i = 0; i < this->norma_month.size(); ++i)
          {
            if(!(std::fabs(this->norma_month.at(i) - a.norma_month.at(i)) < std::numeric_limits<double>::epsilon()))
              {
                ++flag;
              }
          }
        if(flag) return  false;
      }
    return true;
  }

bool Pole_Nio::operator != (const Pole_Nio &a)
  {
    return !(*this == a);
  }

std::ostream& Pole_Nio::poleNioCout(std::ostream& out) const
  {
    out << "<pole_nio>" << "\n";
    if(!this->getIndexNio().isEmpty())
      {
        out << "\t<index_nio> " << this->getIndexNio().toStdString() << " </index_nio>" << "\n";
      }
    else
      {
        out << "\t<index_nio> " << std::string("нет_данных") << " </index_nio>" << "\n";
      }
    out << "\t<KolichestvoKomplectov> " << this->getKolichestvoKomplectov() << " </KolichestvoKomplectov>" << "\n";
    out << "\t<v_spirt_size> " << this->getNormaMonth().size() << " </v_spirt_size>" << "\n";
    out << "\t<spirt>";
    out << " ";
    for(double d : this->getNormaMonth()) out << "<" << d << "> ";
    out << "</spirt>" << "\n";
    out << "</pole_nio>";
    return out;
  }

std::istream& Pole_Nio::poleNioCin(std::istream& in)
  {
    std::string str1;
    std::string str2;
    std::string str3;
    std::string str4;
    std::string str5;
    std::string str6;

    std::getline(in, str1);
    std::getline(in, str2);
    std::getline(in, str3);
    std::getline(in, str4);
    std::getline(in, str5);
    std::getline(in, str6);

    std::stringstream s1(str1);  //пока не ясно зачем.

    std::stringstream s2(str2);
    std::vector<std::string>* v2 = new std::vector<std::string>();
    for(std::string buf; s2 >> buf;)
      {
        v2->push_back(buf);
      }
    std::string ind_nio = "";
    for(unsigned int i = 1; i < v2->size()-1; ++i)
      {
        ind_nio += v2->at(i) + " ";
      }
    this->setIndexNio(ind_nio);

    std::stringstream s3(str3);
    std::string sbros, sbros1;
    int k_vo = 0;
    s3 >> sbros >> k_vo >> sbros1;
    this->setKolichestvoKomlectov(k_vo);

    std::stringstream s4(str4);
    int sz_v = 0;
    s4 >> sbros >> sz_v >> sbros1; //sz_v проверка вектора

    std::stringstream s5(str5);
    std::string double_string;
    double buf = 0.;
    std::vector<std::string>* v_buf = new std::vector<std::string>();
    for(std::string buf; s5 >> buf;)
      {
        v_buf->push_back(buf);
      }
    std::vector<double>* v_dbl = new std::vector<double>();
    for(unsigned int i = 1; i < v_buf->size()-1; ++i)
      {
        for(unsigned int j = 1; j < v_buf->at(i).size()-1; ++j)
          {
            double_string += v_buf->at(i).at(j);
          }
        std::stringstream d_buf(double_string);
        d_buf >> buf;
        v_dbl->push_back(buf);
        double_string.clear();
      }
    this->setNormaMonth(*v_dbl);

    std::stringstream s6(str6);  //пока не ясно зачем.

    return in;
  }

QTextStream& Pole_Nio::poleNioCout(QTextStream& out) const
  {
    out << "<pole_nio>" << "\n";
    if(!this->getIndexNio().isEmpty())
      {
        out << "\t<index_nio> " << this->getIndexNio() << " </index_nio>" << " \n";
      }
    else
      {
        out << "\t<index_nio> " << QString("нет_данных") << " </index_nio>" << " \n";
      }
    out << "\t<KolichestvoKomplectov> " << this->getKolichestvoKomplectov() << " </KolichestvoKomplectov> "  << " \n";
    out << "\t<v_spirt_size> " << this->getNormaMonth().size() << " </v_spirt_size>" << "\n";
    out << "\t<spirt>";
    out << " ";
    for(double d : this->getNormaMonth()) out << "<" << d << "> ";
    out << "</spirt>" << "\n";
    out << "</pole_nio>";
    return out;
  }

QTextStream& Pole_Nio::poleNioCin(QTextStream& in)
  {
    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString str5;
    QString str6;

    in.readLineInto(&str1);
    in.readLineInto(&str2);
    in.readLineInto(&str3);
    in.readLineInto(&str4);
    in.readLineInto(&str5);
    in.readLineInto(&str6);

    QStringList bufItem1 = str1.split( " ", Qt::SkipEmptyParts );  //может для проверки использовать

    QStringList bufItem2 = str2.split( " ", Qt::SkipEmptyParts );
    QString indNio = "";
    for(int i = 1; i < bufItem2.size()-1; ++i)
      {
        indNio.append(bufItem2.at(i));
        if((bufItem2.size()-2) != i) indNio.append(' ');
      }
    this->setIndexNio(indNio);

    QStringList bufItem3 = str3.split( " ", Qt::SkipEmptyParts );
    int kol_vo = bufItem3.at(1).toInt();
    this->setKolichestvoKomlectov(kol_vo);

    QStringList bufItem4 = str4.split( " ", Qt::SkipEmptyParts );
    int size_vector = bufItem4.at(1).toInt(); //для обработки ошибки размера вектора

    QStringList bufItem5 = str5.split( " ", Qt::SkipEmptyParts );
    QVector<double>* v = new QVector<double>();
    QString duoble = "";
    for(int i = 1; i < bufItem5.size()-1; ++i)
      {
        for(int j = 1; j < bufItem5.at(i).size()-1; ++j)
          {
            duoble.append(bufItem5.at(i).at(j));
          }
        v->push_back(duoble.toDouble());
        duoble.clear();
      }
    if(size_vector == v->size())
      this->setNormaMonth(*v);

    QStringList bufItem6 = str6.split( " ", Qt::SkipEmptyParts );  //может для проверки ????

    return in;
  }

void Pole_Nio::setIndexNio(const QString name)
  {
    if(!name.isEmpty())
      {
        this->indexNio = name;
      }
  }

  void Pole_Nio::setIndexNio( const std::string& name ) { this->setIndexNio( QString::fromStdString( name ) ); }

  void Pole_Nio::setNormaMonth( const QVector< double >& v ) {
    if(!v.empty()/* && (v.size() != this->month)*/)
      {
        this->norma_month.clear();
        for(double d : v)
          {
            this->norma_month.push_back(d);
          }
      }
  }

void Pole_Nio::setNormaMonth(const std::vector<double>& v)
  {
    QVector<double>* n_vec = new QVector<double>();
    for(double d : v)
      {
        n_vec->push_back(d);
      }
    this->norma_month = *n_vec;
  }

void Pole_Nio::setKolichestvoKomlectov(int x)
  {
    if(x >= 0)
      {
        this->kolichestvoKomplectov = x;
      }
    else
      {
        x = 0;
      }
  }

void Pole_Nio::setNormaMonthFromIndex(int index, double znach)
  {
    if((0 >= index) || (index < this->month) || (this->norma_month.count() == this->month)) // unsigned int не может быть < 0 (убрал такую провеврку)
      {
        this->norma_month[index] = znach;
      }
  }

double Pole_Nio::summa_spirt_na_god_po_stroke_nio() const
  {
    double summ = 0.;
    if(!this->norma_month.empty())
      {
        for(double d : this->norma_month)
          {
            summ += d;
          }
      }
    return summ;
  }

void Pole_Nio::raspredelit_po_mesyatsam_is_obschey(double litres_year)
  {
    if(litres_year != 0.)
      {
        if(!this->norma_month.empty())
          {
            this->norma_month.clear();
          }

        for(uint i = 0; i < this->month; ++i)
          {
            this->norma_month.push_back(litres_year/this->month);
          }
      }
  }

//Pole_Nio &operator + (const Pole_Nio &a, const Pole_Nio &b) //тоже работает
//{
//  std::cout << "Binar + \n";
//  Pole_Nio *summ = new Pole_Nio();
//  if(b.naimenovanieNio == a.naimenovanieNio)
//    {
//      summ->naimenovanieNio = a.naimenovanieNio;
//      summ->kolichestvoKomplectov = a.kolichestvoKomplectov + b.kolichestvoKomplectov;
//      if(b.norma_month.size() == a.norma_month.size())
//        {
//          for(int i = 0; i < a.norma_month.size(); ++i)
//            {
//              summ->norma_month.push_back(b.norma_month.at(i)+a.norma_month.at(i));
//            }
//        }
//    }
//  return *summ;
//}

std::ostream& operator << (std::ostream& out, const Pole_Nio& a)
  {
    return a.poleNioCout(out);
  }

QTextStream& operator << (QTextStream& out, const Pole_Nio& a)
  {
    return a.poleNioCout(out);
  }

std::istream& operator >> (std::istream& inpt, Pole_Nio& a)
  {
    return a.poleNioCin(inpt);
  }

void Pole_Nio::print( std::vector< std::string >* v )  // TODO Вспомогательная тестовая
{
  for ( std::string s : *v ) {
    std::cout << s << " "
	      << " Size = " << s.size( ) << "\n";
  }
  std::cout << "\n";
}

QTextStream& operator >> (QTextStream& inpt, Pole_Nio& a)
  {
    return a.poleNioCin(inpt);
  }
