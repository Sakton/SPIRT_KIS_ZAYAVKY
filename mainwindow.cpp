#include "mainwindow.h"

#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QPoint>
#include <QRegularExpression>
#include <QSettings>
#include <QSignalMapper>
#include <QSize>
#include <QString>
#include <QStyleFactory>
#include <QWidget>

#include "base_my_child_form.h"
#include "mychild_nio_form.h"
#include "mychild_norma_form.h"
#include "ui_mainwindow.h"
#include "vybor_documenta.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
  {
    //разобраться с маппером
    this->ui->setupUi(this);
    setWindowTitle("SPIRT_OTPI_416");
    this->setCentralWidget(this->ui->my_mdi);
    // this->connect(this->ui->my_mdi, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(update_menus()));
    this->windowMapper = new QSignalMapper(this);
    this->init();
    this->connect(this->windowMapper,
                  SIGNAL(mapped(QWidget*)),
                  this,
                  SLOT(setActiveSubWindow(QWidget*)));
    this->connect(this->vybor_documenta,
                  SIGNAL(vyborNioForm()),
                  this,
                  SLOT(createChildNioForm()));
    this->connect(this->vybor_documenta,
                  SIGNAL(vyborNormaForm()),
                  this,
                  SLOT(createChildNormForm()));
    // TODO ???
    this->connect(this->vybor_documenta,
                  SIGNAL(vyborNioFormOpen()),
                  this,
                  SLOT(open_mwindow()));
    // TODO ???
    this->connect(this->vybor_documenta,
                  SIGNAL(vyborNormaFormOpen()),
                  this,
                  SLOT(open_mwindow()));
  }

MainWindow::~MainWindow()
  {
    delete ui;
    delete this->vybor_documenta;
  }

void MainWindow::save_in_mwindow()
  {
    if(this->activ_mdi_child() && this->activ_mdi_child()->save())
      {
        this->ui->statusBar->showMessage("Файл сохранен");
      }
  }

void MainWindow::save_as()
  {
    Base_My_Child_Form *child = this->activ_mdi_child();
    if(child && child->save_as())
      {
        this->ui->statusBar->showMessage("Файл сохранен");
      }
  }

void MainWindow::closeEvent(QCloseEvent* event)
  {
    this->ui->my_mdi->closeActiveSubWindow();
    if(this->ui->my_mdi->currentSubWindow())
      {
        event->ignore();
      }
    else
      {
        this->write_settings();
        event->accept();
      }
  }

void MainWindow::init()
  {
    this->vybor_documenta = new Vybor_Documenta(this);
    this->vybor_documenta->move((this->x() + (this->width()/3)),
                                (this->y() + (this->height()/2) - (this->vybor_documenta->height()/4)));
    this->vybor_documenta->show();
  }

Base_My_Child_Form* MainWindow::activ_mdi_child() const
  {
    if(QMdiSubWindow* window = this->ui->my_mdi->activeSubWindow())
      {
        return qobject_cast<Base_My_Child_Form*>(window->widget()); //метод виджет !!!!
      }
    return nullptr;
  }

void MainWindow::write_settings()
  {
    QSettings settings("КИС-416", "Спирт_заявка");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
  }

void MainWindow::read_settings()
  {
    QSettings settings("КИС-416", "Спирт_заявка");
    QPoint pos = settings.value("pos", QPoint(200,200)).toPoint();
    QSize size = settings.value("size", QSize(1000,800)).toSize();
    this->move(pos);
    this->resize(size);
  }

void MainWindow::open_mwindow()
  {
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("nio, norma (*.nio *.norma)"));
    if(!fileName.isEmpty())
      {
        this->open_file(fileName);
      }
  }

bool MainWindow::open_file(const QString &fileName)
  {
    if(QMdiSubWindow* existing = this->find_mdi_child(fileName)) //TODO не работает условие
      {
        this->setActiveSubWindow(existing); // TODO нахуя???
        return true;
      }
    const bool succeeded = this->load_file(fileName);
    if(succeeded) this->ui->statusBar->showMessage(tr("Файл %1 загружен").arg(fileName), 5000);
    this->current_file = fileName;
    return succeeded;
  }

QMdiSubWindow* MainWindow::find_mdi_child(const QString& file_name) const
  {
    QString canonicalFilePath = QFileInfo(file_name).canonicalFilePath();
    foreach(QMdiSubWindow* window, this->ui->my_mdi->subWindowList())
      {
        Base_My_Child_Form *child = qobject_cast<Base_My_Child_Form*>(window->widget());
        if(child->current_file() == canonicalFilePath)
          {
            return window;
          }
      }
    return 0;
  }

bool MainWindow::openFileChild(Base_My_Child_Form* child, const QString& fileName) const
  {
    const bool succeeded  = child->loadFile(fileName);
    if(succeeded)
      {
        child->set_current_file(fileName);
        this->ui->my_mdi->addSubWindow(child);
        this->vybor_documenta->close();
        child->setWindowTitle(fileName);
        child->show();
      }
    else
      {
        child->close();
      }
    return succeeded;
  }

  bool MainWindow::load_file( const QString& fileName ) {
    QRegularExpression reNioFile( "*.nio" );
    // reNioFile.setPatternOptions( QRegularExpression::WildcardConversionOption::DefaultWildcardConversion );
    QRegularExpression reNormaFile( "*.norma" );
    // reNormaFile.setPatternSyntax( QRegularExpression::Wildcard );
    if ( reNioFile.match( fileName ).isValid( ) )  // true, если расширение .nio
    {
      MyChild_NIO_Form* child = new MyChild_NIO_Form( );
      return this->openFileChild( child, fileName );
    }
    if ( reNormaFile.match( fileName ).isValid( ) )  // true, если расширение .norma
    {
      MyChild_Norma_Form* child = new MyChild_Norma_Form( );
      return this->openFileChild( child, fileName );
    }
    return false;
  }

//void prependToRecentFiles(const QString& fileName)
//{
//}

MyChild_NIO_Form* MainWindow::createChildNioForm()
  {
    MyChild_NIO_Form* childNio = new MyChild_NIO_Form();
    this->ui->my_mdi->addSubWindow(childNio);
    this->vybor_documenta->close();
    childNio->new_file();
    childNio->show();
    return childNio;
  }

MyChild_Norma_Form* MainWindow::createChildNormForm()
  {
    MyChild_Norma_Form* childNorma = new MyChild_Norma_Form();
    this->ui->my_mdi->addSubWindow(childNorma);
    this->vybor_documenta->close();
    childNorma->new_file();
    childNorma->show();
    return childNorma;
  }

void MainWindow::on_action_quit_triggered()
  {
    this->close();
  }

void MainWindow::on_action_new_triggered()
  {
    if(this->vybor_documenta == nullptr)
      {
        this->vybor_documenta = new Vybor_Documenta(this);
        this->vybor_documenta->show();
      }
    else
      {
        this->vybor_documenta->activateWindow();
        this->vybor_documenta->show();
      }
  }

void MainWindow::update_menus()
  {
  }

void MainWindow::setActiveSubWindow( QWidget* )	 // FIXME ????
{}

void MainWindow::on_action_save_triggered()
  {
    this->save_in_mwindow();
  }

void MainWindow::on_action_save_as_triggered()
  {
    this->save_as();
  }

void MainWindow::on_action_open_triggered()
  {
    this->open_mwindow();
  }

void MainWindow::on_addRow_triggered()
  {
    this->activ_mdi_child()->addRow();
    //activ_mdi_child() - возвращает указатель на базовый класс - вызов метода базового класса - полиморфизм
  }

void MainWindow::on_actionDelRow_triggered()
  {
    this->activ_mdi_child()->delRow();
  }

void MainWindow::on_actionPrint_triggered()
  {
    if(this->activ_mdi_child() && this->activ_mdi_child()->plot())
      {
        this->ui->statusBar->showMessage("Печать документа");
      }
  }
