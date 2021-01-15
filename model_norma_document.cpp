#include <QDebug>
#include <limits>
#include <QMessageBox>
#include <QDebug>
#include "model_norma_document.h"
#include "pole_norma.h"

Model_Norma_Document::Model_Norma_Document(QObject *parent) : QAbstractTableModel(parent)
  {
    this->documentNorma = new Document_Norma();
    // *************tests************
    //    for(int j = 0; j < 10; ++j)
    //      {
    //        Pole_Norma* ppn = new Pole_Norma();
    //        QVector<double>* pv = new QVector<double>();
    //        for(int i = 0; i < 12; ++i)
    //          {
    //            pv->push_back((i+j+1)*0.1);
    //          }
    //        ppn->setNormaMonth(*pv);
    //        ppn->setInvNumNio(tr("Инв. № %1").arg(j));
    //        ppn->setIndexNio(tr("Индекс НИО %1").arg(j));
    //        ppn->setNaimenovanieNio(tr("Наименование НИО %1").arg(j));
    //        ppn->setKolvoSpirtaPoInstr(ppn->summa_spirt_na_god_po_stroke_nio());
    //        ppn->setKolvoSpirtaKoefficient(0);
    //        ppn->setKolichestvoKomlectov(j);
    //        ppn->setPeriodReglament(tr("%1 раз в год").arg(j));
    //        ppn->setKolvoSpirtaPoInstr_NewYear(10*j);
    //        ppn->setKolvoSpirtaKoefficient_NewYear(0);
    //        ppn->setkolvoKomplectov_NewYear(2*j);
    //        ppn->setPeriodReglament_NewYear(tr("%1 раз в год").arg(10*j));
    //        ppn->setPrimechanye(tr("Примечание № %1").arg(j));
    //        this->documentNorma->addPole(*ppn);
    //        delete pv;
    //        delete ppn;
    //      }
    // *************tests************
  }

Model_Norma_Document::~Model_Norma_Document()
  {
    delete this->documentNorma;
  }

int Model_Norma_Document::rowCount(const QModelIndex &parent) const
  {
    /*
      Возвращает число рядов при данном родителе. Когда родитель действителен, это означает, что rowCount возвращает число детей родителя.
Этот метод возвращает количество строк (фактически число потомков)
для указанного модельного индекса. В табличных (и списковых) моделях у всех
элементов индекс родителя принимает недопустимое значение,
поэтому если индекс содержит именно такое значение, то мы воз-
вращаем общее количество строк в таблице (или списке).
     */
    if(parent.isValid())
      {
        return 0;
      }
    return this->documentNorma->getPolesNorma().size();
  }

int Model_Norma_Document::columnCount(const QModelIndex &parent) const
  {
    if(parent.isValid())
      {
        return 0;
      }
    return this->columnCounts;
  }

QVariant Model_Norma_Document::data(const QModelIndex &index, int role) const
  {
    if(!index.isValid() || (index.row() < 0) || (index.row() > this->documentNorma->getPolesNorma().size()) || (index.column() < 0) || (index.column() > this->columnCounts))
      {
        return QVariant();
      }
    const Pole_Norma& item = this->documentNorma->getPolesNorma().at(index.row());
    if(role == Qt::DisplayRole)
      {
        switch(index.column())
          {
          case 0: return index.row()+1;
          case 1: return item.getIndexNio();
          case 2: return item.getInvNumNio();
          case 3: return item.getNaimenovanieNio();
          case 4:
            {
              if(item.summa_spirt_na_god_po_stroke_nio() < std::numeric_limits<double>::min())
                {
                  return item.getKolvoSpirtaPoInstr();
                }
              else
                {
                  return item.summa_spirt_na_god_po_stroke_nio();
                }
            }
          case 5: return item.getKolvoSpirtaKoefficient();
          case 6: return item.getKolvoKomplectov();
          case 7: return item.getperiodReglament();
          case 8: return QVariant();
          case 9: return item.getkolvoSpirtaPoInstr_NewYear();
          case 10: return item.getKolvoSpirtaKoefficient_NewYear();
          case 11: return item.getKolvoKomplectov_NewYear();
          case 12: return item.getPeriodReglament_NewYear();
          case 13: return item.getPrimechanye();
          default: return QVariant();
          }
      }
    return QVariant();
  }

QVariant Model_Norma_Document::headerData(int section, Qt::Orientation orientation, int role) const
  {
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
      {
        switch(section)
          {
          case 0: return QString(tr("№\nп/п"));
          case 1: return QString(tr("Индекс\nНИО"));
          case 2: return QString(tr("Инвент.\n№"));
          case 3: return QString(tr("Наименов."));
          case 4: return QString(tr("Кол-во\nспирта\nпо ин\nв год"));
          case 5: return QString(tr("Кол-во\nспирта\nс учетом\nкоэфф.\nв год"));
          case 6: return QString(tr("Кол-во\nкомпл."));
          case 7: return QString(tr("Перио-\nдичность\n(регламент)"));
          case 8: return QString(tr("*"));
          case 9: return QString(tr("Кол-во\nспирта\nпо ин\nв год"));
          case 10: return QString(tr("Кол-во\nспирта\nс учетом\nкоэфф.\nв год"));
          case 11: return QString(tr("Кол-во\nкомпл."));
          case 12: return QString(tr("Перио-\nдичность\n(регламент)"));
          case 13: return QString(tr("Примечание"));
          default: return QVariant();
          }
      }
    return QVariant();
  }

bool Model_Norma_Document::setData(const QModelIndex &index, const QVariant &value, int role)
  {
    if(data(index, role) != value)
      {
        Pole_Norma& item = this->documentNorma->setPolesFromEdit()[index.row()];
        switch(index.column())
          {
          case 0: return false;
          case 1:
            {
              item.setIndexNio(value.toString());
              return true;
            }
          case 2:
            {
              item.setInvNumNio(value.toString());
              return true;
            }
          case 3:
            {
              item.setNaimenovanieNio(value.toString());
              return true;
            }
          case 4:
            {
              if(item.summa_spirt_na_god_po_stroke_nio() < std::numeric_limits<double>::min())
                {
                  item.setKolvoSpirtaPoInstr(value.toDouble());
                  emit myChangeNormaSignal();
                  return true;
                }
              else
                {
                  QMessageBox* bx = new QMessageBox(QMessageBox::Warning,
                                                    tr("ЗАПРЕТ!!!"),
                                                    tr("Попытка изменить расчетные данные  из формы НИО.\nПоправьте форму НИО для изменения данных."),
                                                    QMessageBox::Cancel);
                  bx->setButtonText(QMessageBox::Cancel, tr("СКРЫТЬ"));
                  bx->setModal(true);
                  bx->show();
                  return false;
                }
            }
          case 5:
            {
              item.setKolvoSpirtaKoefficient(value.toDouble());
              return true;
            }
          case 6:
            {
              item.setKolichestvoKomlectov(value.toInt());
              return true;
            }
          case 7:
            {
              item.setPeriodReglament(value.toString());
              return true;
            }
          case 8:return false;
          case 9:
            {
              item.setKolvoSpirtaPoInstr_NewYear(value.toDouble());
              emit myChangeNormaSignal();
              return true;
            }
          case 10:
            {
              item.setKolvoSpirtaKoefficient_NewYear(value.toDouble());
              return true;
            }
          case 11:
            {
              item.setkolvoKomplectov_NewYear(value.toInt());
              return true;
            }
          case 12:
            {
              item.setPeriodReglament_NewYear(value.toString());
              return true;
            }
          case 13:
            {
              item.setPrimechanye(value.toString());
              return true;
            }
          default: return false;
          }
      }
    return false;
  }

Qt::ItemFlags Model_Norma_Document::flags(const QModelIndex &index) const
  {
    if(!index.isValid())
      {
        return Qt::NoItemFlags;
      }
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
  }

bool Model_Norma_Document::insertRows(int row, int count, const QModelIndex &parent)
  {
    beginInsertRows(parent, row, row + count - 1);
    Pole_Norma* pn = new Pole_Norma();
    this->documentNorma->addPole(*pn);
    endInsertRows();
    emit myChangeNormaSignal();
    return true;
  }

bool Model_Norma_Document::removeRows(int row, int count, const QModelIndex &parent)
  {
    if(row >= 0)
      {
        beginRemoveRows(parent, row, row + count - 1);
        this->documentNorma->deletePole(row);
        emit myChangeNormaSignal();
        endRemoveRows();
        return true;
      }
    return false;
  }

void Model_Norma_Document::setDocumentNormaRead(const Document_Norma& docNorm)
  {
    this->beginResetModel();
    this->documentNorma->setOtdel(docNorm.getOtdel());
    this->documentNorma->addPoles(docNorm.getPolesNorma(), true);
    this->documentNorma->setYear(docNorm.getYear());
    this->endResetModel();
    emit myChangeNormaSignal();
  }

void Model_Norma_Document::setOtdel(const QString& otdel)
  {
    this->documentNorma->setOtdel(otdel);
  }

void Model_Norma_Document::setDate(int year)
  {
    this->documentNorma->setYear(year);
  }
