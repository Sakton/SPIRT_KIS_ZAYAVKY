#include "printpagenorma.h"
#include <QPrinter>
#include <QPainter>
#include <QPen>
#include <QMargins>
#include <QVector>
#include <QLine>
#include <QFont>
#include <QtPrintSupport/QPrintPreviewDialog>
#include "model_norma_document.h"

PrintPageNorma::PrintPageNorma(const Model_Norma_Document* modelNorDoc, QWidget* parent) : QWidget(parent), modelNormaDocument{modelNorDoc}
  {
  }

PrintPageNorma::~PrintPageNorma()
  {
    delete this->printer;
    delete this->previewDialog;
  }

void PrintPageNorma::drawDocumentNorma()
  {
    this->init();
  }

void PrintPageNorma::previevDocNorma(QPrinter* printer)
  {
    this->painter = new QPainter(printer);

    int currentIndex = 0;
    for(int page = 0; page < this->getPagesCount(); ++page)
      {
        this->drawFormNorma();
        this->drawTextNorma();
        for(int row = 0; row < this->ROWS_IN_FORM_NORMA; ++row)
          {
            if(currentIndex < this->getRowsDocNorma())
              {
                this->drawInformation(currentIndex, row);
                ++currentIndex;
                if(currentIndex == (this->getRowsDocNorma()))
                  {
                    if((row + 1) < this->ROWS_IN_FORM_NORMA)
                      {
                        this->drawItogoNorma((row + 1));
                      }
                    else
                      {
                        printer->newPage();
                        this->drawItogoNorma(0);
                      }
                  }
              }
            else
              {
                break;
              }
            if(row == this->ROWS_IN_FORM_NORMA)
              {
                printer->newPage();
              }
          }
        //удаление лишняя страница
        if(currentIndex < this->getRowsDocNorma())
          {
            printer->newPage();
          }
      }
    delete this->painter;
  }

void PrintPageNorma::init()
  {
    // принтер настройки
    //    this->printer = new QPrinter(QPrinter::PrinterResolution);
    //    this->printer->setOrientation(QPrinter::Landscape);
    //    this->printer->setPageSize(QPrinter::A4);
    //    this->printer->setPaperSize(QSize(297, 420), QPrinter::Millimeter);
    //    this->printer->setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);
    //    // диалоговое окно
    //    this->previewDialog = new QPrintPreviewDialog(this->printer, this);
    //    this->previewDialog->setMinimumWidth(1000);
    //    this->previewDialog->setMinimumHeight(800);
    //    this->connect(this->previewDialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(previevDocNorma(QPrinter*)));
    //    this->previewDialog->exec();
  }

void PrintPageNorma::drawFormNorma()
  {
    QPen p = QPen(Qt::black);
    p.setWidth(5);
    this->painter->setPen(p);
    QRect rect = this->painter->viewport() - this->margin;
    this->painter->drawRect(rect);
    QVector<QLine>* vectorLines = new QVector<QLine>();
    //horisontal lines
    vectorLines->push_back(QLine(
                             QPoint(rect.x(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK),
                             QPoint(rect.x() + rect.width(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK)));
    vectorLines->push_back(QLine(
                             QPoint(rect.x(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK*2),
                             QPoint(rect.x() + rect.width(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK*2)));
    vectorLines->push_back(QLine(
                             QPoint(rect.x(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE),
                             QPoint(rect.x() + rect.width(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE)));
    vectorLines->push_back(QLine(
                             QPoint(rect.x(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_LINES_NUMERATION_COLUMNS),
                             QPoint(rect.x() + rect.width(),
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE + this->HEIGHT_LINES_NUMERATION_COLUMNS)));
    for(int i = 0; i < this->ROWS_IN_FORM_NORMA; ++i)
      {
        vectorLines->push_back(QLine(
                                 QPoint(rect.x(),
                                        rect.y() +
                                        this->HEIGHT_ZAGOLOVOK +
                                        this->HEIGHT_HEADER_TABLE +
                                        this->HEIGHT_LINES_NUMERATION_COLUMNS +
                                        this->HEIGHT_ROWS_TABLE * i),
                                 QPoint(rect.x() + rect.width(),
                                        rect.y() +
                                        this->HEIGHT_ZAGOLOVOK +
                                        this->HEIGHT_HEADER_TABLE +
                                        this->HEIGHT_LINES_NUMERATION_COLUMNS +
                                        this->HEIGHT_ROWS_TABLE * i)));
      }
    //vertical lines
    vectorLines->push_back(QLine(
                             QPoint(rect.x() + this->WIDTH_COLUMH_NUM_PP,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK),
                             QPoint(rect.x() + this->WIDTH_COLUMH_NUM_PP,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK),
                             QPoint(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO + this->WIDTH_COLUMN_INV_NUM,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/2),
                             QPoint(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO + this->WIDTH_COLUMN_INV_NUM,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                                    rect.y() + rect.height())));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT,
                                    rect.y() + rect.height())));
    //средние линии шапки
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/2),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/2)));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3)));
    vectorLines->push_back(QLine(
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3),
                             QPoint(rect.x() +
                                    this->WIDTH_COLUMH_NUM_PP +
                                    this->WIDTH_COLUMN_INDEX_NIO +
                                    this->WIDTH_COLUMN_INV_NUM +
                                    this->WIDTH_COLUMN_NAIMENOVANY +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT +
                                    this->WIDTH_COLUMN_ZERO_9 +
                                    this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                    this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                    this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                    this->WIDTH_COLUMN_REGLAMENT,
                                    rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3)));
    //drawForm
    for(QLine line : *vectorLines)
      {
        this->painter->drawLine(line);
      }
    delete vectorLines;
  }

void PrintPageNorma::drawTextNorma()
  {
    QRect rect = this->painter->viewport() - this->margin;
    QFont f1 = QFont("arial",16,QFont::Bold);
    this->painter->setFont(f1);
    this->painter->drawText(rect.x(),
                            rect.y(),
                            rect.width(),
                            this->HEIGHT_ZAGOLOVOK,
                            Qt::AlignCenter,
                            tr("Норма расхода\nэтилового спирта на эксплуатацию НИО\nпо отделу (сектору): %1 КИС - 416 на %2 г.")
                            .arg(this->modelNormaDocument->getDocumentNorma()->getOtdel())
                            .arg(this->modelNormaDocument->getDocumentNorma()->getYear()));
    QFont f2 = QFont("arial",12,QFont::Bold);
    this->painter->setFont(f2);
    this->painter->drawText(rect.x(),
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_COLUMH_NUM_PP,
                            this->HEIGHT_HEADER_TABLE,
                            Qt::AlignCenter,
                            tr("№\nп.п."));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_COLUMN_INDEX_NIO,
                            this->HEIGHT_HEADER_TABLE,
                            Qt::AlignCenter,
                            tr("ИНДЕКС НИО"));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_COLUMN_INV_NUM + this->WIDTH_COLUMN_NAIMENOVANY,
                            this->HEIGHT_HEADER_TABLE/2,
                            Qt::AlignCenter,
                            tr("ИНСТРУКЦИЯ"));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/2,
                            this->WIDTH_COLUMN_INV_NUM,
                            this->HEIGHT_HEADER_TABLE/2,
                            Qt::AlignCenter,
                            tr("ИНВЕНТ. №"));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO + this->WIDTH_COLUMN_INV_NUM,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/2,
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            this->HEIGHT_HEADER_TABLE/2,
                            Qt::AlignCenter,
                            tr("НАИМЕНОВАНИЕ"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_HEADER_TABLE/3,
                            Qt::AlignCenter,
                            tr("%1 год").arg(this->modelNormaDocument->getDocumentNorma()->getYear()));
    QFont f3 = QFont("arial",10,QFont::Bold);
    this->painter->setFont(f3);
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Кол-во\nспирта\nпо инстр.\nв год"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Кол-во\nспирта\nс уч.коэф.\nв год"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Кол-во\nкомпл-ов"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Пеорио-\nдичность\n(регла-\nмент)"));
    this->painter->setFont(f2);
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_HEADER_TABLE/3,
                            Qt::AlignCenter,
                            tr("%1 год").arg(this->modelNormaDocument->getDocumentNorma()->getYear() + 1));
    this->painter->setFont(f3);
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Кол-во\nспирта\nпо инстр.\nв год"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Кол-во\nспирта\nс уч.коэф.\nв год"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Кол-во\nкомпл-ов"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE/3,
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_HEADER_TABLE*2/3,
                            Qt::AlignCenter,
                            tr("Пеорио-\nдичность\n(регла-\nмент)"));
    this->painter->setFont(f2);
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT,
                            rect.y() + this->HEIGHT_ZAGOLOVOK,
                            (rect.width()) - (this->WIDTH_COLUMH_NUM_PP +
                                                         this->WIDTH_COLUMN_INDEX_NIO +
                                                         this->WIDTH_COLUMN_INV_NUM +
                                                         this->WIDTH_COLUMN_NAIMENOVANY +
                                                         this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                                         this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                                         this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                                         this->WIDTH_COLUMN_REGLAMENT +
                                                         this->WIDTH_COLUMN_ZERO_9 +
                                                         this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                                         this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                                         this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                                         this->WIDTH_COLUMN_REGLAMENT),
                            this->HEIGHT_HEADER_TABLE,
                            Qt::AlignCenter,
                            tr("ПРИМЕЧАНИЕ"));
    //нумерация столбцов
    this->painter->setFont(f3);
    this->painter->drawText(rect.x(),
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMH_NUM_PP,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("1"));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_INDEX_NIO,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("2"));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_INV_NUM,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("3"));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO + this->WIDTH_COLUMN_INV_NUM,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("4"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("5"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("6"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("7"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("8"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_ZERO_9,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("9"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("10"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("11"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("12"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("13"));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT,
                            rect.y() + this->HEIGHT_ZAGOLOVOK + this->HEIGHT_HEADER_TABLE,
                            (rect.width()) - (this->WIDTH_COLUMH_NUM_PP +
                                                         this->WIDTH_COLUMN_INDEX_NIO +
                                                         this->WIDTH_COLUMN_INV_NUM +
                                                         this->WIDTH_COLUMN_NAIMENOVANY +
                                                         this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                                         this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                                         this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                                         this->WIDTH_COLUMN_REGLAMENT +
                                                         this->WIDTH_COLUMN_ZERO_9 +
                                                         this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                                         this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                                         this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                                         this->WIDTH_COLUMN_REGLAMENT),
                            this->HEIGHT_LINES_NUMERATION_COLUMNS,
                            Qt::AlignCenter,
                            tr("14"));
  }

void PrintPageNorma::drawInformation(int index, int row)
  {
    QRect rect = this->painter->viewport() - this->margin;
    QFont f = QFont("arial",12,QFont::Normal);
    this->painter->setFont(f);
    this->painter->drawText(rect.x(),
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMH_NUM_PP,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr("%1").arg(index + 1));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_INDEX_NIO,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignVCenter | Qt::AlignLeft,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getIndexNio()));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_INV_NUM,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignVCenter | Qt::AlignLeft,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getInvNumNio()));
    this->painter->drawText(rect.x() + this->WIDTH_COLUMH_NUM_PP + this->WIDTH_COLUMN_INDEX_NIO + this->WIDTH_COLUMN_INV_NUM,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignVCenter | Qt::AlignLeft,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getNaimenovanieNio()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getKolvoSpirtaPoInstr()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getKolvoSpirtaKoefficient()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getKolvoKomplectov()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getperiodReglament()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getkolvoSpirtaPoInstr_NewYear()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getKolvoSpirtaKoefficient_NewYear()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getKolvoKomplectov_NewYear()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_REGLAMENT,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getPeriodReglament_NewYear()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9 +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_REGLAMENT,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            (rect.x() + rect.width()) - (rect.x() +
                                                         this->WIDTH_COLUMH_NUM_PP +
                                                         this->WIDTH_COLUMN_INDEX_NIO +
                                                         this->WIDTH_COLUMN_INV_NUM +
                                                         this->WIDTH_COLUMN_NAIMENOVANY +
                                                         this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                                         this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                                         this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                                         this->WIDTH_COLUMN_REGLAMENT +
                                                         this->WIDTH_COLUMN_ZERO_9 +
                                                         this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                                                         this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                                                         this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                                                         this->WIDTH_COLUMN_REGLAMENT),
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignVCenter | Qt::AlignLeft,
                            tr(" %1").arg(this->modelNormaDocument->getDocumentNorma()->getPolesNorma().at(index).getPrimechanye()));
  }

void PrintPageNorma::drawItogoNorma(int row)
  {
    QRect rect = this->painter->viewport() - this->margin;
    QFont f = QFont("arial",12,QFont::Bold);
    this->painter->setFont(f);
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignVCenter | Qt::AlignRight,
                            tr("ИТОГО: "));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr("%1").arg(this->modelNormaDocument->getDocument().summSpirtCurrentYear()));
    this->painter->drawText(rect.x() +
                            this->WIDTH_COLUMH_NUM_PP +
                            this->WIDTH_COLUMN_INDEX_NIO +
                            this->WIDTH_COLUMN_INV_NUM +
                            this->WIDTH_COLUMN_NAIMENOVANY +
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD +
                            this->WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT +
                            this->WIDTH_COLUMN_KOLVO_KOMPLETOV +
                            this->WIDTH_COLUMN_REGLAMENT +
                            this->WIDTH_COLUMN_ZERO_9,
                            rect.y() +
                            this->HEIGHT_ZAGOLOVOK +
                            this->HEIGHT_HEADER_TABLE +
                            this->HEIGHT_LINES_NUMERATION_COLUMNS +
                            this->HEIGHT_ROWS_TABLE * row,
                            this->WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD,
                            this->HEIGHT_ROWS_TABLE,
                            Qt::AlignCenter,
                            tr("%1").arg(this->modelNormaDocument->getDocument().summSpirtNewYear()));
  }

int PrintPageNorma::getRowsDocNorma()
  {
    return this->modelNormaDocument->getDocumentNorma()->getPolesNorma().size();
  }

int PrintPageNorma::getPagesCount()
  {
    if(this->getRowsDocNorma()%this->ROWS_IN_FORM_NORMA != 0)
      {
        return this->getRowsDocNorma()%this->ROWS_IN_FORM_NORMA + 1;
      }
    return this->getRowsDocNorma()%this->ROWS_IN_FORM_NORMA;
  }
