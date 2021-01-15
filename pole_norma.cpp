#include <sstream>
#include <QDebug>
#include <QStringList>
#include "pole_norma.h"

Pole_Norma::Pole_Norma(QString indexNio, int kolichestvoKompectov, QVector<double> v)
  : Pole_Nio(indexNio, kolichestvoKompectov, v),
    invNumNio{""},
    naimenovanieNio{""},
    kolvoSpirtaPoInstr{0},
    kolvoSpirtaKoefficient{0},
    periodReglament{""},
    kolvoSpirtaPoInstr_NewYear{0},
    kolvoSpirtaKoefficient_NewYear{0},
    kolvoKomplectov_NewYear{0},
    periodReglament_NewYear{""},
    primechanye{""}
  {
  }

Pole_Norma::Pole_Norma(const Pole_Nio& pnio)
  :Pole_Nio(pnio),
    invNumNio{""},
    naimenovanieNio{""},
    kolvoSpirtaPoInstr{0},
    kolvoSpirtaKoefficient{0},
    periodReglament{""},
    kolvoSpirtaPoInstr_NewYear{0},
    kolvoSpirtaKoefficient_NewYear{0},
    kolvoKomplectov_NewYear{0},
    periodReglament_NewYear{""},
    primechanye{""}
  {
  }

Pole_Norma::Pole_Norma(const Pole_Norma& pnrm)
  :Pole_Nio(pnrm.getIndexNio(),pnrm.getKolvoKomplectov(), pnrm.getNormaMonth())
  {
    this->setInvNumNio(pnrm.getInvNumNio());
    this->setNaimenovanieNio(pnrm.getNaimenovanieNio());
    this->setKolvoSpirtaPoInstr(pnrm.getKolvoSpirtaPoInstr());
    this->setKolvoSpirtaKoefficient(pnrm.getKolvoSpirtaKoefficient());
    this->setPeriodReglament(pnrm.getperiodReglament());
    this->setKolvoSpirtaPoInstr_NewYear(pnrm.getkolvoSpirtaPoInstr_NewYear());
    this->setKolvoSpirtaKoefficient_NewYear(pnrm.getKolvoSpirtaKoefficient_NewYear());
    this->setkolvoKomplectov_NewYear(pnrm.getKolvoKomplectov_NewYear());
    this->setPeriodReglament_NewYear(pnrm.getPeriodReglament_NewYear());
    this->setPrimechanye(pnrm.getPrimechanye());
  }

  std::string& Pole_Norma::parsString( const std::string& str ) {
    std::stringstream buf(str);
    std::vector<std::string>* v = new std::vector<std::string>();
    std::string* sx = new std::string;
    for(std::string s; buf >> s;)
      {
        v->push_back(s);
      }
    for(unsigned int i = 1; i < v->size() - 1; ++i)
      {
        *sx += v->at(i);
      }
    return *sx;
  }

QString& Pole_Norma::parsString(const QString& str)
  {
    QString buf = str;
    QStringList strList = buf.split( " ", Qt::SkipEmptyParts );
    QString* s = new QString();
    for(int i = 1; i < strList.size() - 1; ++i)
      {
        s->append(strList.at(i));
        if(i != (strList.size() - 2)) s->append(' ');
      }
    return *s;
  }

  int Pole_Norma::parsStringInt( const std::string& str ) {
    std::stringstream s(str);
    std::string b1, b2;
    int x = 0;
    s >> b1 >> x >> b2;
    return x;
  }

int Pole_Norma::parsStringInt(const QString& str)
  {
    QString buf = str;
    int x = 0;
    QStringList sl = buf.split( " ", Qt::SkipEmptyParts );
    return x = sl.at(1).toInt();
  }

  double Pole_Norma::parsStringDouble( const std::string& str ) {
    std::stringstream s(str);
    std::string b1, b2;
    double d = 0.;
    s >> b1 >> d >> b2;
    return d;
  }

double Pole_Norma::parsStringDouble(const QString& str)
  {
    QString buf = str;
    double d = 0.;
    QStringList sl = buf.split( " ", Qt::SkipEmptyParts );
    return d = sl.at(1).toDouble();
  }

std::ostream& Pole_Norma::poleNormaCout(std::ostream& out) const
  {
    this->poleNioCout(out);
    out << "\n";
    out << "<InvNumNio> " << this->getInvNumNio().toStdString() << " </InvNumNio>\n";
    out << "<NaimenovanieNio> " << this->getNaimenovanieNio().toStdString() << " </NaimenovanieNio>\n";
    out << "<SpirtPoInstr> " << this->getKolvoSpirtaPoInstr() << " </SpirtPoInstr>\n";
    out << "<KolvoSpirtaKoefficient> " << this->getKolvoSpirtaKoefficient() << " </KolvoSpirtaKoefficient>\n";
    out << "<PeriodReglament> " << this->getperiodReglament().toStdString() << " </PeriodReglament>\n";
    out << "<KolvoSpirtaPoInstr_NewYear> " << this->getkolvoSpirtaPoInstr_NewYear() << " </KolvoSpirtaPoInstr_NewYear>\n";
    out << "<KolvoSpirtaKoefficient_NewYear> " << this->getKolvoSpirtaKoefficient_NewYear() << " </KolvoSpirtaKoefficient_NewYear>\n";
    out << "<KolvoKomplectov_NewYear> " << this->getKolvoKomplectov_NewYear() << " </KolvoKomplectov_NewYear>\n";
    out << "<PeriodReglament_NewYear> " << this->getPeriodReglament_NewYear().toStdString() << " </PeriodReglament_NewYear>\n";
    out << "<Primechanye> " << this->getPrimechanye().toStdString() << " </Primechanye>\n";
    return out;
  }

std::istream& Pole_Norma::poleNormaCin(std::istream& in)
  {
    this->poleNioCin(in);
    std::string str1;
    std::string str2;
    std::string str3;
    std::string str4;
    std::string str5;
    std::string str6;
    std::string str7;
    std::string str8;
    std::string str9;
    std::string str10;

    std::getline(in,str1);
    std::getline(in,str2);
    std::getline(in,str3);
    std::getline(in,str4);
    std::getline(in,str5);
    std::getline(in,str6);
    std::getline(in,str7);
    std::getline(in,str8);
    std::getline(in,str9);
    std::getline(in,str10);

    std::string invNum = this->parsString(str1);
    this->setInvNumNio(invNum);

    std::string naimenovNio = this->parsString(str2);
    this->setNaimenovanieNio(naimenovNio);

    double spirtPoInstr = this->parsStringDouble(str3);
    this->setKolvoSpirtaPoInstr(spirtPoInstr);

    double spirtPoInstrKoeff = this->parsStringDouble(str4);
    this->setKolvoSpirtaKoefficient(spirtPoInstrKoeff);

    std::string periodRegl = this->parsString(str5);
    this->setPeriodReglament(periodRegl);

    double spirtPoInstrNewYear = this->parsStringDouble(str6);
    this->setKolvoSpirtaPoInstr_NewYear(spirtPoInstrNewYear);

    double spirtPoInstrKoeffNewYear = this->parsStringDouble(str7);
    this->setKolvoSpirtaKoefficient_NewYear(spirtPoInstrKoeffNewYear);

    int kolvoKomolNewYear = this->parsStringInt(str8);
    this->setkolvoKomplectov_NewYear(kolvoKomolNewYear);

    std::string reglamentNewYear = this->parsString(str9);
    this->setPeriodReglament_NewYear(reglamentNewYear);

    std::string primechanye = this->parsString(str10);
    this->setPrimechanye(primechanye);

    return in;
  }

QTextStream& Pole_Norma::poleNormaCout(QTextStream& out) const
  {
    this->poleNioCout(out);
    out << "\n";
    out << "<InvNumNio> " << this->getInvNumNio() << " </InvNumNio>\n";
    out << "<NaimenovanieNio> " << this->getNaimenovanieNio() << " </NaimenovanieNio>\n";
    out << "<SpirtPoInstr> " << this->getKolvoSpirtaPoInstr() << " </SpirtPoInstr>\n";
    out << "<KolvoSpirtaKoefficient> " << this->getKolvoSpirtaKoefficient() << " </KolvoSpirtaKoefficient>\n";
    out << "<PeriodReglament> " << this->getperiodReglament() << " </PeriodReglament>\n";
    out << "<KolvoSpirtaPoInstr_NewYear> " << this->getkolvoSpirtaPoInstr_NewYear() << " </KolvoSpirtaPoInstr_NewYear>\n";
    out << "<KolvoSpirtaKoefficient_NewYear> " << this->getKolvoSpirtaKoefficient_NewYear() << " </KolvoSpirtaKoefficient_NewYear>\n";
    out << "<KolvoKomplectov_NewYear> " << this->getKolvoKomplectov_NewYear() << " </KolvoKomplectov_NewYear>\n";
    out << "<PeriodReglament_NewYear> " << this->getPeriodReglament_NewYear() << " </PeriodReglament_NewYear>\n";
    out << "<Primechanye> " << this->getPrimechanye() << " </Primechanye>\n";
    return out;
  }

QTextStream& Pole_Norma::poleNormaCin(QTextStream& in)
  {
    this->poleNioCin(in);
    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString str5;
    QString str6;
    QString str7;
    QString str8;
    QString str9;
    QString str10;

    in.readLineInto(&str1);
    in.readLineInto(&str2);
    in.readLineInto(&str3);
    in.readLineInto(&str4);
    in.readLineInto(&str5);
    in.readLineInto(&str6);
    in.readLineInto(&str7);
    in.readLineInto(&str8);
    in.readLineInto(&str9);
    in.readLineInto(&str10);

    QString invNum = this->parsString(str1);
    this->setInvNumNio(invNum);

    QString naimenovNio = this->parsString(str2);
    this->setNaimenovanieNio(naimenovNio);

    double spirtPoInstr = this->parsStringDouble(str3);
    this->setKolvoSpirtaPoInstr(spirtPoInstr);

    double spirtPoInstrKoeff = this->parsStringDouble(str4);
    this->setKolvoSpirtaKoefficient(spirtPoInstrKoeff);

    QString periodRegl = this->parsString(str5);
    this->setPeriodReglament(periodRegl);

    double spirtPoInstrNewYear = this->parsStringDouble(str6);
    this->setKolvoSpirtaPoInstr_NewYear(spirtPoInstrNewYear);

    double spirtPoInstrKoeffNewYear = this->parsStringDouble(str7);
    this->setKolvoSpirtaKoefficient_NewYear(spirtPoInstrKoeffNewYear);

    int kolvoKomolNewYear = this->parsStringInt(str8);
    this->setkolvoKomplectov_NewYear(kolvoKomolNewYear);

    QString reglamentNewYear = this->parsString(str9);
    this->setPeriodReglament_NewYear(reglamentNewYear);

    QString primechanye = this->parsString(str10);
    this->setPrimechanye(primechanye);

    return in;
  }

std::istream& operator >> (std::istream& in, Pole_Norma& plNr)
  {
    return plNr.poleNormaCin(in);
  }

QTextStream& operator << (QTextStream& out, const Pole_Norma& plNr)
  {
    return plNr.poleNormaCout(out);
  }

QTextStream& operator >> (QTextStream& in, Pole_Norma& plNr)
  {
    return plNr.poleNormaCin(in);
  }

std::ostream& operator << (std::ostream& out, const Pole_Norma& plNr)
  {
    return plNr.poleNormaCout(out);
  }

void Pole_Norma::setNaimenovanieNio(const QString& naimenov)
  {
    this->naimenovanieNio = naimenov;
  }

void Pole_Norma::setNaimenovanieNio( const std::string& naimenov ) {
  this->setNaimenovanieNio( QString::fromStdString( naimenov ) );
}

void Pole_Norma::setInvNumNio(const QString& invNum)
  {
    this->invNumNio = invNum;
  }

void Pole_Norma::setInvNumNio( const std::string& invNum ) { this->setInvNumNio( QString::fromStdString( invNum ) ); }

void Pole_Norma::setKolvoSpirtaPoInstr(double kolvo)
  {
    this->kolvoSpirtaPoInstr = kolvo;
  }

void Pole_Norma::setKolvoSpirtaKoefficient(double kolvo)
  {
    this->kolvoSpirtaKoefficient = kolvo;
  }

void Pole_Norma::setPeriodReglament(const QString& reglament)
  {
    this->periodReglament = reglament;
  }

void Pole_Norma::setPeriodReglament( const std::string& reglament ) {
  this->setPeriodReglament( QString::fromStdString( reglament ) );
}

void Pole_Norma::setKolvoSpirtaPoInstr_NewYear(double kolvo)
  {
    this->kolvoSpirtaPoInstr_NewYear = kolvo;
  }

void Pole_Norma::setKolvoSpirtaKoefficient_NewYear(double kolvo)
  {
    this->kolvoSpirtaKoefficient_NewYear = kolvo;
  }

void Pole_Norma::setkolvoKomplectov_NewYear(int kolvo)
  {
    this->kolvoKomplectov_NewYear = kolvo;
  }

void Pole_Norma::setPeriodReglament_NewYear(const QString& reglament)
  {
    this->periodReglament_NewYear = reglament;
  }

void Pole_Norma::setPeriodReglament_NewYear( const std::string& reglament ) {
  this->setPeriodReglament_NewYear( QString::fromStdString( reglament ) );
}

void Pole_Norma::setPrimechanye(const QString& primech)
  {
    this->primechanye = primech;
  }

void Pole_Norma::setPrimechanye( const std::string& primech ) {
  this->setPrimechanye( QString::fromStdString( primech ) );
}
