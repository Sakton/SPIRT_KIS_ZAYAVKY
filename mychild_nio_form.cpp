#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrinter>
#include "mychild_nio_form.h"
#include "ui_mychild_nio_form.h"
#include "model_nio_document.h"
#include "delegate_nio_table.h"
#include "printpagenio.h"

MyChild_NIO_Form::MyChild_NIO_Form(QWidget* parent) : Base_My_Child_Form(parent), ui(new Ui::MyChild_NIO_Form)
  {
    this->ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setIsUntitled(true);
    //TODO ???
    this->setModel_InForm(this->nioModel = new Model_Nio_Document()); // FIXME организовать установку ?????????
    this->connect(this->nioModel,
                  SIGNAL(myChangeSignal()),
                  this,
                  SLOT(myItogoSlot()));
  }

MyChild_NIO_Form::~MyChild_NIO_Form()
  {
    delete this->ui;
    delete this->nioModel;
    delete this->delegatNioTable;
  }

void MyChild_NIO_Form::new_file()
  {
    Base_My_Child_Form::new_file();


//    this->nioModel = new Model_Nio_Document();
//    this->setModel_InForm(this->nioModel);


    static int sequenceNumber = 0;
    this->curFile = tr("New_Nio_Document_%1.nio").arg(sequenceNumber++);
    setWindowTitle(this->curFile + "[*]");
  }

bool MyChild_NIO_Form::loadFile(const QString &fileName)
  {
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
      {
        QMessageBox::warning(this, tr("ОШИБКА ОТКРЫТИЯ ФАЙЛА"), tr("Файл: %1 не открыт: %2 ;").arg(fileName).arg(file.errorString()), QMessageBox::Ok);
        return false;
      }
    //TODO
    QTextStream inpt(&file);
    Document_nio_year* d = new Document_nio_year();
    inpt >> *d;
    file.close();
    this->nioModel->setDocumentRead(*d); // в этом методе идет перезагрузка модели
    this->setModel_InForm(this->nioModel); // переустановка модели для полей не из таблицы
    this->curFile = fileName;
    this->setIsUntitled(false);
    delete d;
    return true;
  }

bool MyChild_NIO_Form::save_file(const QString &fileName)
  {
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
      {
        QMessageBox::warning(this, tr("ОШИБКА СОХРАНЕНИЯ"), tr("Не могу соxранить файл: %1").arg(fileName), QMessageBox::Ok);
        return false;
      }
    QTextStream stream(&file);
    stream << *this->nioModel->getDocumentNioYear();
    file.close();
    this->curFile = fileName;
    this->setIsUntitled(false);
    return true;
  }

bool MyChild_NIO_Form::open()
  {
    //какой то код
    return true;
  }

void MyChild_NIO_Form::setModel_InForm(Model_Nio_Document* doc)
  {
    this->ui->table_nio->setModel(doc);
    this->ui->table_nio->setItemDelegate(this->delegatNioTable = new Delegate_Nio_Table(this));
    this->ui->otdelLineEdit->setText(doc->getDocumentNioYear()->getOtdel());
    this->ui->dateEdit_year->setDate(QDate(doc->getDocumentNioYear()->getYear(),QDate().currentDate().month(), QDate().currentDate().day()));
    this->ui->table_nio->resizeColumnsToContents();
    //this->ui->table_nio->resizeRowsToContents();
    QVector<int> sizes = {30   //№ п.п
                          ,280 //НИО
                          ,60 //Кол-во
                          ,55  //Январь
                          ,55  //Февраль
                          ,55  //Март
                          ,55  //Апрель
                          ,55  //Май
                          ,55  //Июнь
                          ,55  //Июль
                          ,50  //Август
                          ,60  //Сентябрь
                          ,55  //Октябрь
                          ,55  //Ноябрь
                          ,55  //Декабрь
                          ,55  //На год
                         };
    for(int i = 0; i < sizes.size(); ++i)
      {
        this->ui->table_nio->setColumnWidth(i,sizes.at(i));
      }
  }


void MyChild_NIO_Form::myItogoSlot()
  {
    if(!this->nioModel->getItogoPoleNio().getNormaMonth().isEmpty())
      {
        this->ui->spinBox_Kolvo->setValue(static_cast<int>(this->nioModel->getItogoPoleNio().getKolichestvoKomplectov()));
        this->ui->doubleSpinBox_Jan->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(0));
        this->ui->doubleSpinBox_Feb->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(1));
        this->ui->doubleSpinBox_Mar->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(2));
        this->ui->doubleSpinBox_Apr->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(3));
        this->ui->doubleSpinBox_May->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(4));
        this->ui->doubleSpinBox_Jun->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(5));
        this->ui->doubleSpinBox_Jul->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(6));
        this->ui->doubleSpinBox_Avg->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(7));
        this->ui->doubleSpinBox_Sept->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(8));
        this->ui->doubleSpinBox_Oct->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(9));
        this->ui->doubleSpinBox_Now->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(10));
        this->ui->doubleSpinBox_Dec->setValue(this->nioModel->getItogoPoleNio().getNormaMonth().at(11));
        this->ui->doubleSpinBox_Year->setValue(this->nioModel->getSpirtYear());
      }
  }
//***********************************



bool MyChild_NIO_Form::addRow()
  {
    //FIXME !!!
    //получаю общее количество строк
    int row = this->nioModel->rowCount();
    //вставить строку номер (нумерация идет от нуля, поэтому row в индексе это номер след строки)
    this->nioModel->insertRow(row);
    //Обновляет область, занятую данным индексом.
    this->ui->table_nio->update();
    //Позволяет модели знать, что она должна представить кэшируемую информацию постоянному хранению.
    //Эта функция обычно используется для редактирования строки.
    //Возвращает true, если нет никакой ошибки; иначе возвращает false
    return this->nioModel->submit();
  }

bool MyChild_NIO_Form::delRow()
  {
    int row = this->ui->table_nio->selectionModel()->currentIndex().row();
    if(row >= 0)
      {
        QMessageBox* bx = new QMessageBox(QMessageBox::Warning,tr("УДАЛЕНИЕ СТРОКИ"),
                                          tr("Выделенная строка будет безвозвратно удалена"),
                                          QMessageBox::Cancel | QMessageBox::Ok);
        bx->setButtonText(QMessageBox::Cancel, tr("ОТМЕНА"));
        bx->setButtonText(QMessageBox::Ok, tr("УДАЛИТЬ"));
        if(bx->exec() == QMessageBox::Ok)
          {
            //TODO !!! бля долго искал!!!
            this->nioModel->removeRow(row);
            this->ui->table_nio->update();
            delete bx;
            return this->nioModel->submit();
          }
      }
    return false;
  }

bool MyChild_NIO_Form::save_as()
  {
    QString fileName = QFileDialog::getSaveFileName(this, "СОХРАНИТЬ ФАЙЛ", "", "(spirt (*.nio))");
    if(fileName.isEmpty())
      {
        return false;
      }
    return this->save_file(fileName);
  }

void MyChild_NIO_Form::on_otdelLineEdit_editingFinished()
  {
    this->nioModel->setOtdel(this->ui->otdelLineEdit->text());
  }

void MyChild_NIO_Form::on_dateEdit_year_editingFinished()
{
    this->nioModel->setDate(this->ui->dateEdit_year->date().year());
}

bool MyChild_NIO_Form::plot()
  {
    Base_My_Child_Form::plot();
    PrintPageNio* printNio = new PrintPageNio(*this->nioModel, this);
    printNio->drawDocumentNio();
    delete printNio;
    return true;
  }
