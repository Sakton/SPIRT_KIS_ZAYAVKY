#ifndef BASE_MY_CHILD_FORM_H
#define BASE_MY_CHILD_FORM_H
#include <QWidget>

class Base_My_Child_Form : public QWidget
{
  Q_OBJECT
protected:
  QString curFile;
  bool isUntitled;
//запрет на создание protected
  Base_My_Child_Form(QWidget* parent = nullptr);
  virtual ~Base_My_Child_Form();

public:
  virtual void new_file();
  virtual bool loadFile(const QString& fileName);
  virtual bool save();
  virtual bool save_as();
  virtual bool open();
  virtual bool save_file(const QString& fileName);
  virtual bool addRow();
  virtual bool delRow();
  virtual bool plot();

  //getters
  QString current_file() { return this->curFile; }
  bool getUntitled() { return this->isUntitled; }
  //setters
  void set_current_file(const QString&);
  void setIsUntitled(bool);


protected slots:
  virtual void document_was_modified();

  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent* event) override;
  virtual bool maybe_save();
  virtual void paintEvent(QPaintEvent* event) override;

//  virtual QString stripped_name(const QString&) = 0;

  // QWidget interface
  protected:

  };

#endif // BASE_MY_CHILD_FORM_H
