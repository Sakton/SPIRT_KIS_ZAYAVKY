#ifndef PRINTPAGENIO_H
#define PRINTPAGENIO_H
#include <QtWidgets>

class Model_Nio_Document;
class QPainter;
class QPrinter;
class QPrintPreviewDialog;
class QMargins;

class PrintPageNio : public QWidget
  {
    Q_OBJECT
    // qMake при добавлении Q_OBJECT !!!
    static constexpr int COUNT_POLES_ITOGO = 1;
    static constexpr int COUNT_ROWS_IN_FORMS_NIO = 15;
    static constexpr int HEIGHT_ROWS_PX = 256;
    static constexpr int DELTA_WIDTH_TABLE_TEXT = 310;
    static constexpr int MONATS_IN_YEAR = 12;
    static constexpr int START_LINES_TEXT_Y_TABLE = 1065;
    // ширина ячеек
    static constexpr int WIDTH_YACHEYKA_NUM_PP = 250;
    static constexpr int WIDTH_YACHEYKA_NIO = 1800;
    static constexpr int WIDTH_YACHEYKA_KOLICHESTVO = 400;
    static constexpr int WIDTH_YACHEYKA_TABLE_MONATS = 310;
    // высота ячеек
    static constexpr int HEIGHT_ZAGOLOVOK = 550;
    static constexpr int HEIGHT_HEADER_TABLE = 350;
    static constexpr int HEIGHT_POD_HEADER_MONATS = HEIGHT_HEADER_TABLE/2;
    static constexpr int HEIGHT_ROW = 256;


    const QMargins margin = {150, 10, 10, 10};

    const Model_Nio_Document& modelNioDocument;
    QPrinter* printer;
    QPainter* painter;
    QPrintPreviewDialog* printDialog;
    int pageCount;
    int currentIndex;

  private:
    int ravnenieNaSeredinuX(int coordFirst, int coordSecond, QFont& font, const QString& text);
    int getPageCount();
    int getRows();
    void init();

    void drawFormsNio();
    void drawTextNio();
    void drawInformation(int index, int numRow);
    void drawItogoNio(int numRow);

  public:
    PrintPageNio(const Model_Nio_Document& model, QWidget* parent = nullptr);
    ~PrintPageNio();
    void drawDocumentNio();

  public slots:
    void previevDocNio(QPrinter* printer);
  };

#endif // PRINTPAGENIO_H
