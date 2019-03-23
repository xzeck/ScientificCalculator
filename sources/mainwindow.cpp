#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/paranthesischecker.h"
#include "headers/parser.h"
#include "headers/license.h"
#include "headers/evaluateexpression.h"


#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <math.h>
#include <QString>




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

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::NumPressed()
{

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


void MainWindow::on_XraiseY_clicked()
{
     ui->Display->setText(ui->Display->text() + "^");
}

QString MainWindow::SpecialbtClicked(QString Exp)
{

    Checker c(Exp);
    Eval E;
    QString ExpressionToParse ="(";
    ExpressionToParse += Exp;
    ExpressionToParse += ")";
    QString Val;

    Parse P(ExpressionToParse);

    if(c.HasBalancedParanthesis())
      {
        P.ParseFunction();
        Val = E.FinalVal();
        //HistoryString += Exp + " = " + Val+"\n";
        //ui->Display->setText(Val);
        //ui->HistoryLabel->setText(HistoryString);
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

    return Val;
}

void MainWindow::on_Xraise2_clicked()
{

  QString Exp = ui->Display->text() + "^2";
  QString Val = SpecialbtClicked(Exp);
  HistoryString += Exp + " = " + Val+"\n";
  ui->Display->setText(Val);
  ui->HistoryLabel->setText(HistoryString);

}

void MainWindow::on_Xraise3_clicked()
{
  QString Exp = ui->Display->text() + "^3";
  QString Val = SpecialbtClicked(Exp);
  HistoryString += Exp + " = " + Val+"\n";
  ui->Display->setText(Val);
  ui->HistoryLabel->setText(HistoryString);

}

void MainWindow::on_SQRT_clicked()
{
  QString Exp = ui->Display->text();
  QString Val = SpecialbtClicked(Exp);
  ui->Display->setText(QString::number(sqrtf64(Val.toDouble())));
  HistoryString += "SQRT(" + Exp +") = " + Val + "\n";
  ui->HistoryLabel->setText(HistoryString);
}

void MainWindow::on_Pi_clicked()
{
    ui->Display->setText(ui->Display->text() + "3.141");
}

void MainWindow::on_NFact_clicked()
{
    qint64 Number = ui->Display->text().toLong();
    qint64 factorial = 1;

    for (qint64 i =1; i<=Number; i++)
      {
        factorial *= i;
      }

    ui->Display->setText(QString::number(factorial));
    HistoryString += QString::number(Number) + "! = " + QString::number(factorial) + "\n";
    ui->HistoryLabel->setText(HistoryString);
}

void MainWindow::on_Log_clicked()
{
  double number = ui->Display->text().toDouble();

  QString Result = QString::number(logf64(number));

  HistoryString += "LOG(" + QString::number(number) + ") = " + Result;
  ui->Display->setText(Result);
}

void MainWindow::on_Ln_clicked()
{
  double number = ui->Display->text().toDouble();

  QString Result = QString::number(log10(number));

  HistoryString += "Ln(" + QString::number(number) + ") = " + Result;
  ui->Display->setText(Result);
}
void MainWindow::on_btSin_clicked()
{
  QString Exp = ui->Display->text();
  QString Val = SpecialbtClicked(Exp);
  ui->Display->setText(QString::number(sinf64(Val.toDouble())));
  HistoryString += "SIN(" + Exp + ") = " + ui->Display->text() + "\n";
  ui->HistoryLabel->setText(HistoryString);
}

void MainWindow::on_btCos_clicked()
{
  QString Exp = ui->Display->text();
  QString Val = SpecialbtClicked(Exp);
  ui->Display->setText(QString::number(cosf64(Val.toDouble())));
   HistoryString += "COS(" + Exp + ") = " + ui->Display->text() + "\n";
  ui->HistoryLabel->setText(HistoryString);
}

void MainWindow::on_btTan_clicked()
{
  QString Exp = ui->Display->text();
  QString Val = SpecialbtClicked(Exp);
  ui->Display->setText(QString::number(tanf64(Val.toDouble())));
   HistoryString += "TAN(" + Exp + ") = " + ui->Display->text() + "\n";
  ui->HistoryLabel->setText(HistoryString);
}

void MainWindow::on_InverseX_clicked()
{
    QString Exp = ui->Display->text();
    QString Val = SpecialbtClicked(Exp);

    double Result = 1/Val.toDouble();

    ui->Display->setText(QString::number(Result));
    HistoryString += "1/" + Exp + " = " + Val + "\n";
    ui->HistoryLabel->setText(HistoryString);
}
