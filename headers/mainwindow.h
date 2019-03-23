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
  QString SpecialbtClicked(QString);


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
  void on_Pi_clicked();
  void on_btSin_clicked();
  void on_NFact_clicked();
  void on_Log_clicked();
  void on_Ln_clicked();
  void on_btCos_clicked();
  void on_btTan_clicked();
  void on_InverseX_clicked();
};

#endif // MAINWINDOW_H
