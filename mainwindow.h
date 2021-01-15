#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vybor_documenta.h"

namespace Ui
{
  class MainWindow;
}

class Base_My_Child_Form;
class MyChild_NIO_Form;
class MyChild_Norma_Form;
class QMdiSubWindow;
class QSignalMapper;


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  //TODO ????!!!!
  void save_as(); //полиморфизм..
  void save_in_mwindow(); //???
  bool open_file(const QString& fileName);

protected:
  void closeEvent(QCloseEvent* event) override; //перехват сообщения о закрытии программы, виртуальный метод базового класса QWidget

private:
  void init();
// TODO !!!
  Base_My_Child_Form* activ_mdi_child() const;
  //через базовый класс...!!! QMdiSubWindow и приведение к нужному типу !!!
  QMdiSubWindow* find_mdi_child(const QString& file_name) const;
  void write_settings();
  void read_settings();
  //ф-я открыть файл в нужном обьекте
  bool openFileChild(Base_My_Child_Form* child, const QString& fileName) const;
  //TODO !!!
  bool load_file(const QString& fileName);
//  void prependToRecentFiles(const QString& fileName);

private slots:
// TODO !!!
  //создать суб-окно нио
  MyChild_NIO_Form* createChildNioForm();
  //создать суб-окно норма расхода
  MyChild_Norma_Form* createChildNormForm();
  void setActiveSubWindow(QWidget*);
  void update_menus();
  //кнопка выход
  void on_action_quit_triggered();
  //кнопка новый файл
  void on_action_new_triggered();
  //кнопка сохранить
  void on_action_save_triggered();
  //кнопка сохранить как
  void on_action_save_as_triggered();
  //кнопка открыть
  void on_action_open_triggered();
  //открыть документ из окна выбора
  void open_mwindow();
  //добавить строку
  void on_addRow_triggered();
  //удаление строки
  void on_actionDelRow_triggered();

  void on_actionPrint_triggered();

  private:
  Ui::MainWindow *ui;
  QString current_file = "";
  QSignalMapper* windowMapper;
  Vybor_Documenta* vybor_documenta;
};

#endif // MAINWINDOW_H
