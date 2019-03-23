#include "headers/license.h"
#include "ui_license.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>


QString License;

license::license(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::license)
{
  ui->setupUi(this);

  QFile File(QCoreApplication::applicationDirPath() + "/LICENSE");
  qDebug() << QCoreApplication::applicationDirPath() + "/LICENSE";
  if(!File.open(QIODevice::ReadOnly)) {
      QMessageBox::information(nullptr, "error", File.errorString());
  }

  QTextStream in(&File);
  QString line;

  while(!in.atEnd())
    {
      line = in.readAll();
    }
  File.close();
  ui->licenseTextEdit->setText(line);

}

license::~license()
{
  delete ui;
}
