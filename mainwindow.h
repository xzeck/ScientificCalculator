#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QString HistoryString = "";

private slots:
  void NumPressed();
  void SpecialbtClicked(QString);


  void on_btEq_clicked();
  void on_btDel_clicked();
  void on_btClr_clicked();
  void on_actionAbout_triggered();
  void on_actionAjay_Nair_triggered();
  void on_actionHrishikesh_Nair_triggered();
  void on_actionLicense_triggered();
  void on_XraiseY_clicked();
  void on_Xraise2_clicked();
  void on_Xraise3_clicked();
  void on_SQRT_clicked();
};

#endif // MAINWINDOW_H
