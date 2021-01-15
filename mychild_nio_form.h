#ifndef MYCHILD_NIO_FORM_H
#define MYCHILD_NIO_FORM_H

#include <QWidget>
#include "base_my_child_form.h"

namespace Ui
  {
    class MyChild_NIO_Form;
  }

class Model_Nio_Document;
class Delegate_Nio_Table;

class MyChild_NIO_Form : public Base_My_Child_Form
  {
    Q_OBJECT

  private:
    Ui::MyChild_NIO_Form* ui;
    Model_Nio_Document* nioModel;
    Delegate_Nio_Table* delegatNioTable;

  public:
    explicit MyChild_NIO_Form(QWidget* parent = nullptr);
    ~MyChild_NIO_Form() override;
    void new_file() override; //не реализована
    bool loadFile(const QString& fileName) override;
    bool save_file(const QString& fileName) override;
    QString user_friendly_current_file(); //???
    bool open() override;
    bool addRow() override;
    bool delRow() override;
    bool save_as() override;
    bool plot() override;

  private:
    void setModel_InForm(Model_Nio_Document *doc);

  public slots:
    void myItogoSlot();

  private slots:
    void on_otdelLineEdit_editingFinished();
    void on_dateEdit_year_editingFinished();

  };

#endif // MYCHILD_NIO_FORM_H
