#include <QDebug>
#include <QStyleOptionComboBox>
#include <iostream> //????
#include <QKeyEvent>
#include "model_nio_document.h"
#include "pole_nio.h"

//TODO унаследовать от базового класса модели

Model_Nio_Document::Model_Nio_Document(QObject *parent) : QAbstractTableModel(parent)
  {
    this->doc = new Document_nio_year();

    //***********for Tests************************
//      doc->setOtdel(QString("OTPI"));
//      doc->setYear(2017);
//      QVector<double> spirt;
//      for(int i = 0; i < 11; ++i)
//        {
//          spirt.clear();
//          for(int j = 0; j < 12; ++j)
//            {
//              spirt.push_back(0.1*(j+1)*(i+1));
//            }
//          Pole_Nio* p = new Pole_Nio(tr("PoleNio в дамике создано %1").arg(i),(i + 1), spirt);
//          p->setKolichestvoKomlectov(123);
//          doc->setPoles(*p);
//          delete p;
//        }


//    QFile file(QString("rs.nio"));
//    if(!file.open(QFile::ReadOnly | QFile::Text))
//      {
//      }
//    QTextStream s(stdout);
//    QTextStream inpt(&file);
//    s << "DO:  \n";
//    inpt >> *this->doc; // работает!!!

    //***********for Tests************************
  }

Model_Nio_Document::~Model_Nio_Document()
  {
    delete this->doc;
  }

QVariant Model_Nio_Document::headerData(int section, Qt::Orientation orientation, int role) const
  {
    //TODO
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
      {
        switch (section)
          {
          case 0:
            return QString("№\nп.п.");
          case 1:
            return QString("НИО");
          case 2:
            return QString("Кол-во");
          case 3:
            return QString("1\nЯнварь");
          case 4:
            return QString("2\nФевраль");
          case 5:
            return QString("3\nМарт");
          case 6:
            return QString("4\nАпрель");
          case 7:
            return QString("5\nМай");
          case 8:
            return QString("6\nИюнь");
          case 9:
            return QString("7\nИюль");
          case 10:
            return QString("8\nАвгуст");
          case 11:
            return QString("9\nСентябрь");
          case 12:
            return QString("10\nОктябрь");
          case 13:
            return QString("11\nНоябрь");
          case 14:
            return QString("12\nДекабрь");
          case 15:
            return QString("На\nгод");
          }
      }
    return QVariant();
  }

int Model_Nio_Document::rowCount(const QModelIndex &parent) const
  {
    if (parent.isValid())
      return 0;
    return this->doc->getRowPoles();
  }

int Model_Nio_Document::columnCount(const QModelIndex &parent) const
  {
    if (parent.isValid())
      return 0;
    return this->columns;
  }

QVariant Model_Nio_Document::data(const QModelIndex &index, int role) const
  {
    if (!index.isValid() || (index.row() < 0) || (index.row() > this->doc->getRowPoles()) || (index.column() < 0) || (index.column() > this->columns))
      {
        return QVariant();
      }
    const Pole_Nio &item = this->doc->getPoles().at(index.row()); //ссылку на поля документа, использую далее

    if(role == Qt::SizeHintRole)
      {
        QStyleOptionComboBox option;
        switch(index.column())
          {
          case 0:
            {
              /*option.currentText.length() = headerData(0, Qt::Horizontal, Qt::DisplayRole).toString().length();*/
            }
          }
      }

    if(role == (Qt::DisplayRole)) // /* | Qt::EditRole*/!!!!
      {
        switch(index.column())
          {
          case 0: //№ п.п
            return index.row()+1;
          case 1: // НИО
            return item.getIndexNio();
          case 2: // Кол-во
            return item.getKolichestvoKomplectov();
          case 3: // Январь
            return item.getNormaMonth().at(0); //FIXME по месяцам как нить в цикл захуярить ???
          case 4: // Февраль
            return item.getNormaMonth().at(1);
          case 5: // Март
            return item.getNormaMonth().at(2);
          case 6: // Апрель
            return item.getNormaMonth().at(3);
          case 7: // Май
            return item.getNormaMonth().at(4);
          case 8: // Июнь
            return item.getNormaMonth().at(5);
          case 9: // Июль
            return item.getNormaMonth().at(6);
          case 10: // Август
            return item.getNormaMonth().at(7);
          case 11: // Сентябрь
            return item.getNormaMonth().at(8);
          case 12: // Октябрь
            return item.getNormaMonth().at(9);
          case 13: // Ноябрь
            return item.getNormaMonth().at(10);
          case 14: // Декабрь
            return item.getNormaMonth().at(11);
          case 15: // Сумма на год....
            return item.summa_spirt_na_god_po_stroke_nio();
          default:
            return QVariant();
          }
      }
    // FIXME: Implement me!
    return QVariant();
  }

bool Model_Nio_Document::setData(const QModelIndex &index, const QVariant &value, int role)
  {
    if (data(index, role) != value)
      {
        // !!!!!!!! at() - возвращает CONST !!! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!!!! надо []!!!
        // TODO поле не приватно!!!
        Pole_Nio &item = this->doc->setPolesFromEdit()[index.row()];

        if(role == Qt::EditRole)
          {
            switch(index.column())
              {
              case 0:
                return false;
              case 1:
                {
                  item.setIndexNio(value.toString());
                  return true;
                }
              case 2:
                {
                  item.setKolichestvoKomlectov(value.toInt());
                  this->doc->setItogo();
                  emit myChangeSignal();
                  return true;
                }
              case 15:
                {
                  // код ??? пересчитывает сама почему-то.... потому что метод дата пересчитывает...
                  // тут опцию, если ввели количество, то распределить по месяцам.
                  // надо-ли?
                  return true;
                }
              default:
                {
                  if(((index.column()-3) >= 0) && ((index.column()-3) < this->monate))
                    {
                      item.setNormaMonthFromIndex(index.column()-3,value.toDouble());
                      //TODO пока как-то так... подумать как...
                      this->doc->setItogo();
                      emit myChangeSignal();
                      return true;
                    }
                }
              }
          }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
      }
    return false;
  }

Qt::ItemFlags Model_Nio_Document::flags(const QModelIndex &index) const
  {
    if (!index.isValid())
      return Qt::NoItemFlags;

    return  Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
  }

bool Model_Nio_Document::insertRows(int row, int count, const QModelIndex &parent)
  {
    // TODO кривоват возврат значения
    beginInsertRows(parent, row, row + count - 1);
    Pole_Nio* pNio = new Pole_Nio();
    this->doc->setPoles(*pNio);
    this->doc->setItogo();
    emit myChangeSignal();
    endInsertRows();
    return true;
  }

bool Model_Nio_Document::removeRows(int row, int count, const QModelIndex &parent)
  {
    if(row >= 0)
      {
        beginRemoveRows(parent, row, row + count - 1);
        this->doc->deletePoles(row);
        this->doc->setItogo();
        emit myChangeSignal();
        endRemoveRows();
        return true;
      }
    return false;
  }

const Pole_Nio& Model_Nio_Document::getItogoPoleNio() const
  {
    return this->doc->getItogoPoNio();
  }

void Model_Nio_Document::setDocumentRead(const Document_nio_year& dNio)
  {
    this->beginResetModel(); // начало перезагрузки модели !!!!!!!
    this->doc->setPoles(dNio.getPoles());
    this->doc->setOtdel(dNio.getOtdel());
    this->doc->setYear(dNio.getYear());
    this->endResetModel(); // конец перезагрузки модели !!!!!!!!!!
    emit myChangeSignal();
  }

void Model_Nio_Document::setOtdel(const QString& otdel)
  {
    this->doc->setOtdel(otdel);
  }

void Model_Nio_Document::setDate(int year)
  {
    this->doc->setYear(year);
  }

//bool Model_Nio_Document::removeColumns(int column, int count, const QModelIndex &parent)
//{
//  beginRemoveColumns(parent, column, column + count - 1);
//  endRemoveColumns();
//}
