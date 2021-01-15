#include <QDebug>
#include <QCloseEvent>
#include "vybor_documenta.h"
#include "ui_vybor_documenta.h"

Vybor_Documenta::Vybor_Documenta(QWidget *parent) : QDialog(parent), ui(new Ui::Vybor_Documenta)
{
  ui->setupUi(this);
}

Vybor_Documenta::~Vybor_Documenta()
{
  delete ui;
}

void Vybor_Documenta::closeEvent(QCloseEvent *event) // ???? надо ли?
{
  event->accept();
}

void Vybor_Documenta::on_pushBtnNioYearNew_clicked()
{
  emit this->vyborNioForm();
}

void Vybor_Documenta::on_pushBtnNormaNew_clicked()
{
  emit this->vyborNormaForm();
}

void Vybor_Documenta::on_pushBtnNioYearOpen_clicked()
{
  emit this->vyborNioFormOpen();
}

void Vybor_Documenta::on_pushBtnNormaOpen_clicked()
{
  emit this->vyborNormaFormOpen();
}
