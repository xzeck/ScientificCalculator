#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paranthesischecker.h"
#include "parser.h"
#include "license.h"


#include <evaluateexpression.h>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>



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
  QPushButton *button = dynamic_cast<QPushButton *>(sender());

  ui->Display->setText(ui->Display->text() + button->text());

}

void MainWindow::on_btEq_clicked()
{

  Checker c(ui->Display->text());
  Eval E;
  QString ExpressionToParse ="(";
  ExpressionToParse += ui->Display->text();
  ExpressionToParse += ")";

  Parse P(ExpressionToParse);

  if(c.HasBalancedParanthesis())
    {
      P.ParseFunction();
      QString Val = E.FinalVal();
      HistoryString += ui->Display->text() + " = " + Val+"\n";
      ui->Display->setText(Val);
      ui->HistoryLabel->setText(HistoryString);
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

void MainWindow::on_btClr_clicked()
{
    ui->Display->clear();
}

void MainWindow::on_actionAbout_triggered()
{
  QMessageBox Message;
    QRect  Geo = MainWindow::geometry();
    int MBoxWidth = Geo.width()/4;
    int MBoxHeight = Geo.height()/4;

    int X = Geo.x() + Geo.width()/2 - (MBoxWidth/2);
    int Y = Geo.y() + Geo.height()/2 - (MBoxHeight/2);
    Message.setGeometry(X,Y,MBoxWidth, MBoxHeight);
    Message.setInformativeText("Project : Scientific Calculator\n\nAjay Nair : 402\n"\
                               "Gladson Daniel Roy : 413\nHrishikesh Nair : 418");
    Message.setIcon(Message.Information);
    Message.button(Message.Ok);
  Message.exec();
}

void MainWindow::on_actionAjay_Nair_triggered()
{
  if(!QDesktopServices::openUrl(QUrl("https://github.com/xzeck/",QUrl::TolerantMode)))
     {
       QMessageBox Message;
       QRect  Geo = MainWindow::geometry();
       int MBoxWidth = Geo.width()/4;
       int MBoxHeight = Geo.height()/4;

       int X = Geo.x() + Geo.width()/2 - (MBoxWidth/2);
       int Y = Geo.y() + Geo.height()/2 - (MBoxHeight/2);
       Message.setGeometry(X,Y,MBoxWidth, MBoxHeight);
       Message.setInformativeText("Sorry the URL cannot be opened at this instance because a browswer"\
                                  "cannot be found.\nYou can view the profile at \nhttps://github.com/xzeck/");

       Message.setWindowTitle("cannot open browser");
       Message.setIcon(Message.Information);
       Message.button(Message.Ok);
       Message.exec();
 }
}

void MainWindow::on_actionHrishikesh_Nair_triggered()
{
  if(!QDesktopServices::openUrl(QUrl("https://github.com/DarkStar24",QUrl::TolerantMode)))
      {
        QMessageBox Message;
        QRect  Geo = MainWindow::geometry();
        int MBoxWidth = Geo.width()/4;
        int MBoxHeight = Geo.height()/4;

        int X = Geo.x() +  Geo.width()/2 - (MBoxWidth/2);
        int Y = Geo.y() + Geo.height()/2 - (MBoxHeight/2);
        Message.setGeometry(X,Y,MBoxWidth, MBoxHeight);
        Message.setInformativeText("Sorry the URL cannot be opened at this instance because a browswer"\
                                   "cannot be found.\nYou can view the profile at \nhttps://github.com/DarkStar24");

        Message.setWindowTitle("cannot open browser");
        Message.setIcon(Message.Information);
        Message.button(Message.Ok);
        Message.exec();
  }
}

void MainWindow::on_actionLicense_triggered()
{
  license l;
  l.setModal(true);
  l.exec();
}
