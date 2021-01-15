#ifndef MYCHILD_NORMA_FORM_H
#define MYCHILD_NORMA_FORM_H

#include <QWidget>
#include "base_my_child_form.h"

class Model_Norma_Document;
class Delegate_Norma_Table;

namespace Ui
  {
    class MyChild_Norma_Form;
  }

class MyChild_Norma_Form : public Base_My_Child_Form
  {
    Q_OBJECT

  public:
    explicit MyChild_Norma_Form(QWidget *parent = nullptr);
    ~MyChild_Norma_Form();
    void new_file() override;
    bool loadFile(const QString &fileName) override;
    bool open() override;
    bool save_file(const QString &fileName) override;
    bool addRow() override;
    bool delRow() override;
    bool save_as() override;
    bool plot() override;

  private:
    Ui::MyChild_Norma_Form *ui;
    Model_Norma_Document *modelNorma;
    Delegate_Norma_Table *delegateNorma;

  private:
    void setModelInForm(Model_Norma_Document *model);

    // QWidget interface
  protected:
    void closeEvent(QCloseEvent *event) override;

  private slots:
    void on_dateTimeEdit_dateChanged(const QDate &date);


    void on_OtdelLineEdit_editingFinished();

    void on_dateTimeEdit_editingFinished();

  public slots:
    void myChangeNormaSlot();
  };

#endif // MYCHILD_NORMA_FORM_H
