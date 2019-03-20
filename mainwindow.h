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


  void on_btEq_clicked();
  void on_btDel_clicked();
  void on_btClr_clicked();
};

#endif // MAINWINDOW_H
