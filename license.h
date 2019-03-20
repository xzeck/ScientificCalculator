#ifndef LICENSE_H
#define LICENSE_H

#include <QDialog>

namespace Ui {
  class license;
}

class license : public QDialog
{
  Q_OBJECT

public:
  explicit license(QWidget *parent = nullptr);
  ~license();

private:
  Ui::license *ui;
};
extern QString License;
#endif // LICENSE_H
