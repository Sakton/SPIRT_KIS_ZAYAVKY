#ifndef PRINTPAGENORMA_H
#define PRINTPAGENORMA_H
#include <QWidget>

class Model_Norma_Document;
class QPrinter;
class QPainter;
class QPrintPreviewDialog;
class QMargins;

class PrintPageNorma : public QWidget
  {
    Q_OBJECT

    const QMargins margin = {150, 10, 10, 10};
    //constants
    static constexpr int ROWS_IN_FORM_NORMA = 22;
    // высоты
    static constexpr int HEIGHT_ZAGOLOVOK = 550;
    static constexpr int HEIGHT_HEADER_TABLE = 550;
    static constexpr int HEIGHT_LINES_NUMERATION_COLUMNS = 100;
    static constexpr int HEIGHT_ROWS_TABLE = 255;
    //длины
    static constexpr int WIDTH_COLUMH_NUM_PP = 255;
    static constexpr int WIDTH_COLUMN_INDEX_NIO = 1300;
                     //instructions
    static constexpr int WIDTH_COLUMN_INV_NUM = 1000;
    static constexpr int WIDTH_COLUMN_NAIMENOVANY = 1000;
                     //year
    static constexpr int WIDTH_COLUMN_KOLVO_SPIRTA_PO_INDEX_V_GOD = 480;
    static constexpr int WIDTH_COLUMN_SPIRT_V_GOD_S_KOEFFICIENT = 425;
    static constexpr int WIDTH_COLUMN_KOLVO_KOMPLETOV = 510;
    static constexpr int WIDTH_COLUMN_REGLAMENT = 600;

    static constexpr int WIDTH_COLUMN_ZERO_9 = 460;
    //static constexpr int WIDTH_COLUMN_PRIMECHANY = 956;

    const Model_Norma_Document* modelNormaDocument;
    QPrinter* printer;
    QPainter* painter;
    QPrintPreviewDialog* previewDialog;

  private:
    void init();
    void drawFormNorma();
    void drawTextNorma();
    void drawInformation(int index, int row);
    void drawItogoNorma(int row);
    int getRowsDocNorma();
    int getPagesCount();

  public:
    PrintPageNorma(const Model_Norma_Document* modelNorDoc, QWidget* parent = nullptr);
    ~PrintPageNorma();

    void drawDocumentNorma();

  public slots:
    void previevDocNorma(QPrinter* printer);
  };

#endif // PRINTPAGENORMA_H
