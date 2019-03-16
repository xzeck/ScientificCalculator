#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

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

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::NumPressed()
{
  QPushButton *button = (QPushButton *)sender();

  ui->Display->setText(ui->Display->text() + button->text());

}

void MainWindow::on_btEq_clicked()
{
  parser p;
  p.RPN(ui->Display->text());
}
