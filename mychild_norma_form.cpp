#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "mychild_norma_form.h"
#include "ui_mychild_norma_form.h"
#include "model_norma_document.h"
#include "delegate_norma_table.h"
#include "document_norma.h"
#include "printpagenorma.h"


MyChild_Norma_Form::MyChild_Norma_Form(QWidget *parent) : Base_My_Child_Form(parent), ui(new Ui::MyChild_Norma_Form)
  {
    ui->setupUi(this);
    this->setModelInForm(this->modelNorma = new Model_Norma_Document(this));
    this->connect(this->modelNorma,
                  SIGNAL(myChangeNormaSignal()),
                  this,
                  SLOT(myChangeNormaSlot()));
  }

MyChild_Norma_Form::~MyChild_Norma_Form()
  {
    delete ui;
    delete this->modelNorma;
    delete this->delegateNorma;
  }

void MyChild_Norma_Form::setModelInForm(Model_Norma_Document *model)
  {
    this->ui->tableNormaNio->setModel(model);
    this->ui->tableNormaNio->setItemDelegate(this->delegateNorma = new Delegate_Norma_Table(this));
    this->ui->tableNormaNio->setAutoFillBackground(true);
    this->ui->OtdelLineEdit->setText(model->getDocumentNorma()->getOtdel());
    this->ui->dateTimeEdit->setDate(QDate(model->getDocumentNorma()->getYear(),QDate().currentDate().month(),QDate().currentDate().day()));
    this->ui->tableNormaNio->resizeColumnsToContents();
    QVector<int> sizes1 = {30, 150, 110, 150, 70, 70, 70, 70, 10, 70, 70, 70, 70, 70};
    for(int i = 0; i < 14; ++i)
      {
        this->ui->tableNormaNio->setColumnWidth(i,sizes1.at(i));
      }
    //первоначальная установка дат в лейблах
    this->ui->labelCurrentYear->setText(tr("на %1 год").arg(this->ui->dateTimeEdit->date().year()));
    this->ui->labelNewYear->setText(tr("на %1 год").arg(this->ui->dateTimeEdit->date().year()+1));
    this->ui->labelItogoCurrYear->setText(tr("ИТОГО на %1 год").arg(this->ui->dateTimeEdit->date().year()));
    this->ui->labelItogoNewYear->setText(tr("ИТОГО на %1 год").arg(this->ui->dateTimeEdit->date().year()+1));
  }

void MyChild_Norma_Form::closeEvent(QCloseEvent *event)
  {
  }

void MyChild_Norma_Form::new_file()
  {
    Base_My_Child_Form::new_file();
    static int sequenceNumber = 0;
    this->curFile = tr("New_Norma_Document %1.norma").arg(sequenceNumber++);
    setWindowTitle(this->curFile + "[*]");
  }

bool MyChild_Norma_Form::loadFile(const QString &fileName)
  {
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
      {
        QMessageBox::warning(this, tr("ОШИБКА ОТКРЫТИЯ ФАЙЛА"), tr("Не удалось открыть файл %1").arg(fileName), QMessageBox::Ok);
        return false;
      }
    // FIXME выброс исключения должен быть
    Document_Norma* dnrm = new Document_Norma();
    QTextStream in(&file);
    in >> *dnrm;
    file.close();
    this->modelNorma->setDocumentNormaRead(*dnrm);
    this->setModelInForm(this->modelNorma);
    this->curFile = fileName;
    this->setIsUntitled(false);
    delete dnrm;
    return true;
  }

bool MyChild_Norma_Form::open()
  {
    // ???
    return true;
  }

bool MyChild_Norma_Form::save_file(const QString &fileName)
  {
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
      {
        QMessageBox::warning(this, tr("ОШИБКА СОХРАНЕНИЯ"), tr("Не могу соранить файл: %1").arg(fileName), QMessageBox::Ok);
        return false;
      }
    QTextStream stream(&file);
    stream << *this->modelNorma->getDocumentNorma();
    file.close();
    this->curFile = fileName;
    this->setIsUntitled(false);
    return true;
  }

void MyChild_Norma_Form::on_dateTimeEdit_dateChanged(const QDate &dat)
  {
    this->ui->labelCurrentYear->setText(tr("на %1 год").arg(dat.year()));
    this->ui->labelNewYear->setText(tr("на %1 год").arg(dat.year() + 1));
    this->ui->labelItogoCurrYear->setText(tr("ИТОГО на %1 год").arg(dat.year()));
    this->ui->labelItogoNewYear->setText(tr("ИТОГО на %1 год").arg(dat.year() + 1));
  }

void MyChild_Norma_Form::myChangeNormaSlot()
  {
    this->ui->SbItogoCurYear->setValue(this->modelNorma->getDocument().summSpirtCurrentYear());
    this->ui->SbItogoNewYear->setValue(this->modelNorma->getDocument().summSpirtNewYear());
  }

bool MyChild_Norma_Form::addRow()
  {
    int row = this->modelNorma->rowCount();
    return this->modelNorma->insertRow(row);
  }

bool MyChild_Norma_Form::delRow()
  {
    int row = this->ui->tableNormaNio->selectionModel()->currentIndex().row();
    if(row >= 0)
      {
        QMessageBox* bx = new QMessageBox(QMessageBox::Warning,tr("УДАЛЕНИЕ СТРОКИ"),
                                          tr("Выделенная строка будет безвозвратно удалена"),
                                          QMessageBox::Cancel | QMessageBox::Ok);
        bx->setButtonText(QMessageBox::Cancel, tr("ОТМЕНА"));
        bx->setButtonText(QMessageBox::Ok, tr("УДАЛИТЬ"));
        if(bx->exec() == QMessageBox::Ok)
          {
            delete bx;
            return  this->modelNorma->removeRow(row);
          }
      }
    return false;
  }

bool MyChild_Norma_Form::save_as()
  {
    QString fileName = QFileDialog::getSaveFileName(this, "СОХРАНИТЬ ФАЙЛ", "", "(spirt (*.norma))");
    if(fileName.isEmpty())
      {
        return false;
      }
    return this->save_file(fileName);
  }

void MyChild_Norma_Form::on_OtdelLineEdit_editingFinished()
  {
    this->modelNorma->setOtdel(this->ui->OtdelLineEdit->text());
  }

void MyChild_Norma_Form::on_dateTimeEdit_editingFinished()
  {
    this->modelNorma->setDate(this->ui->dateTimeEdit->date().year());
  }


bool MyChild_Norma_Form::plot()
  {
    Base_My_Child_Form::plot();
    PrintPageNorma* printPageNorma = new PrintPageNorma(this->modelNorma, this);
    printPageNorma->drawDocumentNorma();
    delete printPageNorma;
    return true;
  }
