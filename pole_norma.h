#ifndef POLE_NORMA_H
#define POLE_NORMA_H
#include <QTextStream>
#include "pole_nio.h"


class Pole_Norma : public Pole_Nio
  {
    QString invNumNio;
    QString naimenovanieNio;

    double kolvoSpirtaPoInstr;
    double kolvoSpirtaKoefficient;
    QString periodReglament;

    double kolvoSpirtaPoInstr_NewYear;
    double kolvoSpirtaKoefficient_NewYear;
    int kolvoKomplectov_NewYear;
    QString periodReglament_NewYear;

    QString primechanye;

  public:
    Pole_Norma(QString indexNio = "", int kolichestvoKompectov = 0, QVector<double> v = QVector<double>(month));
    Pole_Norma(const Pole_Nio& pnio);
    Pole_Norma(const Pole_Norma& pnrm);

    std::ostream& poleNormaCout(std::ostream& out) const;
    std::istream& poleNormaCin(std::istream& in);
    QTextStream& poleNormaCout(QTextStream& out) const;
    QTextStream& poleNormaCin(QTextStream& in);
    friend std::ostream& operator << (std::ostream& out, const Pole_Norma& plNr);
    friend std::istream& operator >> (std::istream& in, Pole_Norma& plNr);
    friend QTextStream& operator << (QTextStream& out, const Pole_Norma& plNr);
    friend QTextStream& operator >> (QTextStream& in, Pole_Norma& plNr);

    //getters
    const QString getNaimenovanieNio() const { return this->naimenovanieNio; }
    const QString getInvNumNio() const { return this->invNumNio; }

    double getKolvoSpirtaPoInstr() const { return this->kolvoSpirtaPoInstr; }
    double getKolvoSpirtaKoefficient() const { return this->kolvoSpirtaKoefficient; }
    int getKolvoKomplectov() const { return this->kolichestvoKomplectov; }
    const QString getperiodReglament() const { return this->periodReglament; }

    double getkolvoSpirtaPoInstr_NewYear() const { return this->kolvoSpirtaPoInstr_NewYear; }
    double getKolvoSpirtaKoefficient_NewYear() const { return this->kolvoSpirtaKoefficient_NewYear; }
    int getKolvoKomplectov_NewYear() const { return this->kolvoKomplectov_NewYear; }
    const QString getPeriodReglament_NewYear() const { return this->periodReglament_NewYear; }

    const QString getPrimechanye() const { return this->primechanye; }
    //setters
    void setInvNumNio(const QString& invNum);
    void setInvNumNio(const std::string& invNum);
    void setNaimenovanieNio(const QString& naimenov);
    void setNaimenovanieNio(const std::string& naimenov);

    void setKolvoSpirtaPoInstr(double kolvo);
    void setKolvoSpirtaKoefficient(double kolvo);
    void setPeriodReglament(const QString& reglament);
    void setPeriodReglament(const std::string& reglament);

    void setKolvoSpirtaPoInstr_NewYear(double kolvo);
    void setKolvoSpirtaKoefficient_NewYear(double kolvo);
    void setkolvoKomplectov_NewYear(int kolvo);
    void setPeriodReglament_NewYear(const QString& reglament);
    void setPeriodReglament_NewYear(const std::string& reglament);

    void setPrimechanye(const QString& primech);
    void setPrimechanye(const std::string& primech);

//    void setkolvoSpirtaPoInstr(); ???
  private:
    std::string& parsString(const std::string& str);
    QString& parsString(const QString& str);
    int parsStringInt(const std::string& str);
    int parsStringInt(const QString& str);
    double parsStringDouble(const std::string& str);
    double parsStringDouble(const QString& str);
  };

std::ostream& operator <<(std::ostream& out, const Pole_Norma& plNr);
std::istream& operator >>(std::istream& in, Pole_Norma& plNr);
QTextStream& operator <<(QTextStream& out, const Pole_Norma& plNr);
QTextStream& operator >>(QTextStream& in, Pole_Norma& plNr);

#endif // POLE_NORMA_H
