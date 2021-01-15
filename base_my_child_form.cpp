#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include "base_my_child_form.h"
#include "model_nio_document.h"


Base_My_Child_Form::Base_My_Child_Form(QWidget* parent) : QWidget(parent)
  {
  }

Base_My_Child_Form::~Base_My_Child_Form()
  {
  }

void Base_My_Child_Form::new_file()
  {
    this->isUntitled = true;
  }

bool Base_My_Child_Form::loadFile(const QString& fileName)
  {
    return true;
  }

bool Base_My_Child_Form::save()
  {
    if(this->isUntitled)
      {
        return this->save_as();
      }
    else
      {
        return this->save_file(this->curFile);
      }
  }

bool Base_My_Child_Form::save_as()
  {
    return true;
  }

bool Base_My_Child_Form::open()
  {
    return true;
  }

bool Base_My_Child_Form::save_file(const QString& fileName)
  {
    if(!fileName.isNull()) return true;
    return false;
  }

bool Base_My_Child_Form::addRow()
  {
    //небходимо обращение к конкретной модели. метод переопределен в классах-наследниках
    return true;
  }

bool Base_My_Child_Form::delRow()
  {
    //небходимо обращение к конкретной модели. метод переопределен в классах-наследниках
    return true;
  }

bool Base_My_Child_Form::plot()
  {
    return true;
  }

void Base_My_Child_Form::document_was_modified()
  {
    this->setWindowModified(this->isWindowModified());
  }

void Base_My_Child_Form::closeEvent(QCloseEvent* event)
  {

  }

bool Base_My_Child_Form::maybe_save()
  {
    //TODO !!!
    //проверить его работу!!!
    if(!this->isWindowModified()) return true;

    QMessageBox* messageBox = new QMessageBox(
                                QMessageBox::Warning,
                                tr("Файл %1 не сохранен").arg(this->current_file()),
                                tr("Файл %1 не сохранен").arg(this->current_file()),
                                QMessageBox::Cancel | QMessageBox::Discard | QMessageBox::Ok,
                                this);
    messageBox->setButtonText(QMessageBox::Cancel, tr("ОТМЕНИТЬ"));
    messageBox->setButtonText(QMessageBox::Discard, tr("ЗАКРЫТЬ"));
    messageBox->setButtonText(QMessageBox::Ok, tr("СОХРАНИТЬ"));
    switch(messageBox->exec())
      {
      case QMessageBox::Save:
        {
          return this->save();
        }
      case QMessageBox::Cancel:
        {
          return false;
        }
      default:
        break;
      }
    return true;
  }

void Base_My_Child_Form::set_current_file(const QString& fileName)
  {
    //TODO !!!
    //проверку???
    //  this->set_current_file(fileName);
    this->curFile = fileName;
  }

void Base_My_Child_Form::setIsUntitled(bool bl)
  {
    this->isUntitled = bl;
  }


void Base_My_Child_Form::paintEvent(QPaintEvent* event)
  {
  }
