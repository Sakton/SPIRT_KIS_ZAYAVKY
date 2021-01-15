#include "printpagenio.h"
#include <QDebug>
#include <QPainter>
#include <QPrinter>
#include <QLine>
#include <QPen>
#include <QBrush>
#include <QFontMetrics>
#include <QVector>
#include <QPoint>
#include <cmath>
#include <QtPrintSupport/QPrintPreviewDialog>
#include "model_nio_document.h"
#include "pole_nio.h"

PrintPageNio::PrintPageNio(const Model_Nio_Document& model, QWidget* parent): QWidget(parent), modelNioDocument{model}
  {
  }

PrintPageNio::~PrintPageNio()
  {
    delete this->printDialog;
    delete this->printer;
  }

void PrintPageNio::previevDocNio(QPrinter* printer)
  {
    this->painter = new QPainter(printer);
    this->currentIndex = 0;
    for(int pages = 0; pages < this->getPageCount(); ++pages)
      {
        this->drawFormsNio();
        this->drawTextNio();
        for(int rows = 0; (rows < this->COUNT_ROWS_IN_FORMS_NIO); ++rows)
          {
            if(this->currentIndex < this->getRows())
              {
                this->drawInformation(this->currentIndex, rows);
                ++this->currentIndex; // за циклами стоит, глобальный индекс в переделах метода
                if(this->currentIndex == (this->getRows()))
                  {
                    if((rows + 1) < this->COUNT_ROWS_IN_FORMS_NIO)
                      {
                        this->drawItogoNio((rows + 1));
                      }
                    else
                      {
                        printer->newPage();
                        this->drawItogoNio(0);
                      }
                  }
              }
            else
              {
                break;
              }
          }
        if(this->currentIndex < this->getRows())
          {
            printer->newPage();
          }
      }
    delete this->painter;
  }

void PrintPageNio::drawDocumentNio()
  {
    this->init();
  }

void PrintPageNio::drawTextNio()
  {
    QRect rect = this->painter->viewport() - this->margin;
    QFont font1 = QFont("arial",16,QFont::Bold);

    this->painter->setFont(font1);
    this->painter->drawText(rect.x(),
                            rect.y(),
                            rect.width(),
                            rect.y() + this->HEIGHT_ZAGOLOVOK/2,
                            Qt::AlignBottom | Qt::AlignHCenter,
                            tr("%1").arg(this->modelNioDocument.getDocumentNioYear()->getOtdel()));
    this->painter->drawText(rect.x(),
                            rect.y() + this->HEIGHT_ZAGOLOVOK/2,
                            rect.width(),
                            rect.y() + this->HEIGHT_ZAGOLOVOK/2,
                            Qt::AlignTop | Qt::AlignHCenter,
                            tr("НИО на %1 год").arg(this->modelNioDocument.getDocumentNioYear()->getYear()));

    QFont font2 = QFont("arial",12,QFont::Bold);
    this->painter->setFont(font2);
    this->painter->drawText(rect.x(),
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_YACHEYKA_NUM_PP,
                            this->HEIGHT_HEADER_TABLE,
                            Qt::AlignCenter,
                            tr("№\nп.п."));
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_YACHEYKA_NIO,
                            this->HEIGHT_HEADER_TABLE,
                            Qt::AlignCenter,
                            tr("НИО"));
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_YACHEYKA_KOLICHESTVO,
                            this->HEIGHT_HEADER_TABLE,
                            Qt::AlignCenter,
                            tr("Кол-во"));
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR,
                            this->HEIGHT_HEADER_TABLE/2,
                            Qt::AlignCenter,
                            tr("Месяцы"));
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            (rect.x() + rect.width()) - (rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR),
                            this->HEIGHT_HEADER_TABLE,
                            Qt::AlignCenter,
                            tr("На\nгод"));
    for(int i = 0; i < this->MONATS_IN_YEAR; ++i)
      {
        this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * i,
                                rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/2,
                                this->WIDTH_YACHEYKA_TABLE_MONATS,
                                this->HEIGHT_HEADER_TABLE/2,
                                Qt::AlignCenter,
                                tr("%1").arg(i + 1));
      }
  }

void PrintPageNio::drawInformation(int index, int numRow)
  {
    QRect rect = this->painter->viewport() - this->margin;
    QFont font = QFont("arial", 11, QFont::Normal);
    this->painter->setFont(font);
    this->painter->drawText(rect.x(),
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                            this->WIDTH_YACHEYKA_NUM_PP,
                            this->HEIGHT_ROW,
                            Qt::AlignCenter,
                            tr("%1").arg(index + 1));
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                            this->WIDTH_YACHEYKA_NIO,
                            this->HEIGHT_ROW,
                            Qt::AlignVCenter | Qt::AlignLeft,
                            tr(" %1").arg(this->modelNioDocument.getDocumentNioYear()->getPoles().at(index).getIndexNio()));
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                            this->WIDTH_YACHEYKA_KOLICHESTVO,
                            this->HEIGHT_ROW,
                            Qt::AlignCenter,
                            tr("%1").arg(this->modelNioDocument.getDocumentNioYear()->getPoles().at(index).getKolichestvoKomplectov()));
    for(int i = 0; i < this->MONATS_IN_YEAR; ++i)
      {
        this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * i,
                                rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                                this->WIDTH_YACHEYKA_TABLE_MONATS,
                                this->HEIGHT_ROW,
                                Qt::AlignCenter,
                                tr("%1").arg(this->modelNioDocument.getDocumentNioYear()->getPoles().at(index).getNormaMonth().at(i)));
      }
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                            (rect.x() + rect.width()) - (rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR),
                            this->HEIGHT_ROW,
                            Qt::AlignCenter,
                            tr("%1").arg(this->modelNioDocument.getDocumentNioYear()->getPoles().at(index).summa_spirt_na_god_po_stroke_nio()));
  }

void PrintPageNio::drawItogoNio(int numRow)
  {
    QRect rect = this->painter->viewport() - this->margin;
    QFont font = QFont("arial", 10, QFont::Bold);
    this->painter->setFont(font);
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                            this->WIDTH_YACHEYKA_NIO,
                            this->HEIGHT_ROW,
                            Qt::AlignVCenter | Qt::AlignRight,
                            tr("%1 ").arg(this->modelNioDocument.getDocumentNioYear()->getItogoPoNio().getIndexNio()));
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                            this->WIDTH_YACHEYKA_KOLICHESTVO,
                            this->HEIGHT_ROW,
                            Qt::AlignCenter,
                            tr("%1").arg(this->modelNioDocument.getDocumentNioYear()->getItogoPoNio().getKolichestvoKomplectov()));
    for(int i = 0; i < this->MONATS_IN_YEAR; ++i)
      {
        this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * i,
                                rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                                this->WIDTH_YACHEYKA_TABLE_MONATS,
                                this->HEIGHT_ROW,
                                Qt::AlignCenter,
                                tr("%1").arg(this->modelNioDocument.getDocumentNioYear()->getItogoPoNio().getNormaMonth().at(i)));
      }
    this->painter->drawText(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * numRow,
                            (rect.x() + rect.width()) - (rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO + this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR),
                            this->HEIGHT_ROW,
                            Qt::AlignCenter,
                            tr("%1").arg(this->modelNioDocument.getDocumentNioYear()->getItogoPoNio().summa_spirt_na_god_po_stroke_nio()));

  }

void PrintPageNio::drawFormsNio()
  {
    // берем карандаш и даем его паинтеру
    QPen p = QPen(QColor(Qt::black));
    p.setWidth(5);
    this->painter->setPen(p);
    // рамка
    QRect rect = this->painter->viewport() - this->margin;
    this->painter->drawRect(rect);
    // вектор линий
    QVector<QLine>* linesForms = new QVector<QLine>();
    // горизонтальные прямые
    linesForms->push_back(QLine(
                            QPoint(rect.x(),
                                   rect.y() + this->HEIGHT_ZAGOLOVOK),
                            QPoint(rect.x() + rect.width(),
                                   rect.y() + this->HEIGHT_ZAGOLOVOK))
                          );
    linesForms->push_back(QLine(
                            QPoint(rect.x(),
                                   rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE),
                            QPoint(rect.x() + rect.width(),
                                   rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE))
                          );
    linesForms->push_back(QLine(
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO,
                                   rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_POD_HEADER_MONATS),
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO
                                   + this->WIDTH_YACHEYKA_TABLE_MONATS * this->MONATS_IN_YEAR,
                                   rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_POD_HEADER_MONATS))
                          );
    for(int i = 0; i < this->COUNT_ROWS_IN_FORMS_NIO; ++i)
      {
        linesForms->push_back(QLine(
                                QPoint(rect.x(),
                                       rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * i),
                                QPoint(rect.x() + rect.width(),
                                       rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_ROW * i))
                              );
      }
    // вертикальные прямые
    linesForms->push_back(QLine(
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP,
                                   rect.y() + this->HEIGHT_ZAGOLOVOK),
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP,
                                   rect.height()))
                          );
    linesForms->push_back(QLine(
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO,
                                   rect.y() + this->HEIGHT_ZAGOLOVOK),
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO,
                                   rect.height()))
                          );
    linesForms->push_back(QLine(
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO,
                                   rect.y() + this->HEIGHT_ZAGOLOVOK),
                            QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO,
                                   rect.height()))
                          );
    for(int i = 0; i < (this->MONATS_IN_YEAR + 1); ++i)
      {
        if(i != 12)
          {
            linesForms->push_back(QLine(
                                    QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO
                                           + this->WIDTH_YACHEYKA_TABLE_MONATS * i,
                                           rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_POD_HEADER_MONATS),
                                    QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO
                                           + this->WIDTH_YACHEYKA_TABLE_MONATS * i,
                                           rect.height()))
                                  );
          }
        else
          {
            linesForms->push_back(QLine(
                                    QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO
                                           + this->WIDTH_YACHEYKA_TABLE_MONATS * i,
                                           rect.y() + this->HEIGHT_ZAGOLOVOK),
                                    QPoint(rect.x() + this->WIDTH_YACHEYKA_NUM_PP + this->WIDTH_YACHEYKA_NIO + this->WIDTH_YACHEYKA_KOLICHESTVO
                                           + this->WIDTH_YACHEYKA_TABLE_MONATS * i,
                                           rect.height()))
                                  );
          }
      }
    // отрисовка формы
    for(QLine line : *linesForms)
      {
        this->painter->drawLine(line);
      }
    delete linesForms;
  }
// coordFirstX - координата начала ячейки, coordSecondX - координата конца ячейки
int PrintPageNio::ravnenieNaSeredinuX(int coordFirstX, int coordSecondX, QFont& font, const QString& text)
  {
    QFontMetrics* fontMetrix = new QFontMetrics(font);
    // int widthText = fontMetrix->width(text)*6;
    // int widthText = fontMetrix->;

    //    int deltaX = ( std::abs( coordSecondX - coordFirstX ) - widthText ) / 2;
    //    delete fontMetrix;
    //    return (coordFirstX + deltaX);
    return 0;  // TODO Qt 6 не работает
  }

int PrintPageNio::getPageCount()
  {
    if(int rows = this->modelNioDocument.getDocumentNioYear()->getPoles().size())
      {
        if((rows + this->COUNT_POLES_ITOGO) % this->COUNT_ROWS_IN_FORMS_NIO != 0) //резервирую 1 строчку под поле ИТОГО по НИО
          {
            return ((rows + this->COUNT_POLES_ITOGO)/this->COUNT_ROWS_IN_FORMS_NIO + 1);
          }
        else
          {
            return ((rows + this->COUNT_POLES_ITOGO)/this->COUNT_ROWS_IN_FORMS_NIO);
          }
      }
    return 0;
  }

int PrintPageNio::getRows()
  {
    return this->modelNioDocument.getDocumentNioYear()->getPoles().size();
  }

void PrintPageNio::init()
  {
    // принтер настройки
    this->printer = new QPrinter(QPrinter::PrinterResolution);
    // this->printer->setPageSize(QPrinter::A4);
    this->printer->setFullPage( true );
    this->printer->setOutputFormat( QPrinter::NativeFormat );
    //    this->printer->setPaperSize(QSize(210,297),QPrinter::Millimeter);
    //    this->printer->setPageMargins(0,0,0,0,QPrinter::Millimeter);
    // this->printer->setOrientation(QPrinter::Landscape);
    // диалог печати
    this->printDialog = new QPrintPreviewDialog(this->printer, this);
    this->printDialog->setMinimumWidth(1000);
    this->printDialog->setMinimumHeight(800);
    this->connect(this->printDialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(previevDocNio(QPrinter*)));
    this->printDialog->exec();
  }
