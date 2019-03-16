#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "InfixToPostfix.h"
#include "paranthesischecker.h"
#include <evaluateexpression.h>

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //TODO : Add CSS to the form
  //TODO : Add Github link
  //TODO : Add a link to view license
  //TODO : Add Quit functionality

  QPushButton *NumButtons[10];
  QPushButton *MathButton;

  for(int i =0; i<10;++i)
    {
      QString ButtonName = "bt" + QString::number(i);
      NumButtons[i] = MainWindow::findChild<QPushButton *>(ButtonName);
      connect(NumButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

  MathButton = MainWindow::findChild<QPushButton *>("btAdd");
  connect(MathButton, SIGNAL(released()), this, SLOT(NumPressed()));

  MathButton = MainWindow::findChild<QPushButton *>("btMul");
  connect(MathButton, SIGNAL(released()), this, SLOT(NumPressed()));

  MathButton = MainWindow::findChild<QPushButton *>("btDiv");
  connect(MathButton, SIGNAL(released()), this, SLOT(NumPressed()));

  MathButton = MainWindow::findChild<QPushButton *>("btSub");
  connect(MathButton, SIGNAL(released()), this, SLOT(NumPressed()));

  MathButton = MainWindow::findChild<QPushButton *>("btDec");
  connect(MathButton, SIGNAL(released()), this,  SLOT(NumPressed()));

  MathButton = MainWindow::findChild<QPushButton *>("btBrac_Right");
  connect(MathButton, SIGNAL(released()), this, SLOT(NumPressed()));

  MathButton = MainWindow::findChild<QPushButton *>("btBrac_Left");
  connect(MathButton, SIGNAL(released()), this, SLOT(NumPressed()));

  //TODO : Connect the signals for the rest of the buttons
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::NumPressed()
{
  //WARNING : Old style casting
  QPushButton *button = (QPushButton *)sender();

  ui->Display->setText(ui->Display->text() + button->text());

}

void MainWindow::on_btEq_clicked()
{
  InfixToPostFix p;
  Checker c(ui->Display->text());
  Eval E;

  if(c.HasBalancedParanthesis())
    {
      p.RPN(ui->Display->text());
      QString Val = E.FinalVal();
      ui->Display->setText(Val);
    }

  else
    {
      //FIXME : Fix the geometry of the Error Box
      QMessageBox MB;
      MB.setText("Syntax Error");
      MB.setIcon(MB.Warning);
      MB.setInformativeText("Entered Input doesn't have balanced paranthesis");
      MB.setGeometry((MainWindow::x()+MainWindow::width()/2), (MainWindow::y()+MainWindow::height()/2),
                     (MainWindow::width()/3), (MainWindow::height()/3));
      MB.exec();
    }

}

void MainWindow::on_btDel_clicked()
{
  QString Display = ui->Display->text();
  std::vector<QString> NewDisplayVec;

  //FIXME : Delete button causes underflow and crash when there's no text in Display

  for(auto x : Display)
    {
      NewDisplayVec.emplace_back(x);
    }

  Display = "";
  for(unsigned long i =0; i<NewDisplayVec.size()-1; i++)
    {
      Display += NewDisplayVec[i];
    }

  ui->Display->setText(Display);
}
