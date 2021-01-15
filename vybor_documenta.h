#ifndef VYBOR_DOCUMENTA_H
#define VYBOR_DOCUMENTA_H

#include <QDialog>

namespace Ui
{
  class Vybor_Documenta;
}

class Vybor_Documenta : public QDialog
{
  Q_OBJECT

public:
  explicit Vybor_Documenta(QWidget *parent = nullptr);
  ~Vybor_Documenta();

private slots:
  void on_pushBtnNioYearNew_clicked();
  void on_pushBtnNioYearOpen_clicked();
  void on_pushBtnNormaNew_clicked();
  void on_pushBtnNormaOpen_clicked();

signals:
  void vyborNioForm();
  void vyborNormaForm();
  void vyborNioFormOpen();
  void vyborNormaFormOpen();

private:
  Ui::Vybor_Documenta *ui;

protected:
  void closeEvent(QCloseEvent *event) override;
};

#endif // VYBOR_DOCUMENTA_H
