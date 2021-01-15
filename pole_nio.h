#ifndef POLE_NIO_H
#define POLE_NIO_H
#include <QVector>
#include <QTextStream>
#include <iostream>

class Pole_Nio
  {
  protected:
    QString indexNio;
    int kolichestvoKomplectov;
  private:
    //рабочий вычислительный класс
    QVector<double> norma_month;
    bool is_equal(const double &x,const double &y) const; //ф-я сравнения 2 дабл для оператора ==
    bool sravnenye_vectorov(const QVector<double> &a, const QVector<double> &b) const; //ф-я сравнения 2 векторов для оператора ==
  public:

    static constexpr int month = 12;

    Pole_Nio(QString indxNio = "", int komplekty = 0, QVector<double> v = QVector<double>(month));
    Pole_Nio(const Pole_Nio &a);

    ~Pole_Nio();

    Pole_Nio& operator + (const Pole_Nio &a);
    Pole_Nio& operator - (const Pole_Nio &a);
    Pole_Nio& operator = (const Pole_Nio &a);
    bool operator == (const Pole_Nio &a);
    bool operator != (const Pole_Nio &a);
    bool operator < (const Pole_Nio &a);
    //  для поддержки QSort и вообще sort //не реализована !!!!!!!!!!!!!!!! пока
    //  friend Pole_Nio& operator + (const Pole_Nio &a, const Pole_Nio &b); //тоже работает
    /*virtual */std::ostream& poleNioCout(std::ostream& out) const;
    /*virtual */std::istream& poleNioCin(std::istream& in);
    /*virtual */QTextStream& poleNioCout(QTextStream& out) const;
    /*virtual */QTextStream& poleNioCin(QTextStream& in);
    friend std::ostream& operator << (std::ostream& out, const Pole_Nio& a);
    friend QTextStream& operator << (QTextStream& out, const Pole_Nio& a);
    friend QTextStream& operator >> (QTextStream& inpt, Pole_Nio& a);
    friend std::istream& operator >> (std::istream& inpt, Pole_Nio& a);

    //setters
    void setIndexNio(const QString name);
    void setIndexNio(const std::string& name);
    void setNormaMonth(const QVector<double> &v);
    void setNormaMonth(const std::vector<double>& v);
    void setKolichestvoKomlectov(int x);
    void setNormaMonthFromIndex(int index, double znach);
    //getters
    const QString getIndexNio() const { return this->indexNio; }
    int getKolichestvoKomplectov() const { return this->kolichestvoKomplectov; }
    const QVector<double>& getNormaMonth() const { return this->norma_month; }
    double summa_spirt_na_god_po_stroke_nio() const;
    void raspredelit_po_mesyatsam_is_obschey(double litres_year);
    //  или распределить автоматически по 12 месяцам, или вручную, запись в поле
    void print(std::vector<std::string>* v);
  };

//  Pole_Nio& operator + (const Pole_Nio &a, const Pole_Nio &b); //тоже работает

std::ostream& operator << (std::ostream &, const Pole_Nio& a);
std::istream& operator >> (std::istream& inpt, Pole_Nio& a);
QTextStream& operator << (QTextStream& out, const Pole_Nio& a);
QTextStream& operator >> (QTextStream& inpt, Pole_Nio& a);

#endif // POLE_NIO_H
