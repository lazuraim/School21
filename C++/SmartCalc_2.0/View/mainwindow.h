#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include <View/credit.h>
#include <View/deposit.h>
#include <View/graph.h>

#include "Controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(Controller *c = nullptr, QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void without_changes();
  void digits();
  void unary_operations();
  void binary_operations();
  void dot();
  void x_button();
  void result();
  void left_bracket();
  void right_bracket();
  void AC();
  void CE();
  void minus();
  void on_pushButton_graph_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
  void Reset();
  void ResetFlags();

private:
  Ui::MainWindow *ui;
  Graph *graph;
  Credit *credit;
  Deposit *deposit;
  Controller *controller;
  bool digit = false;
  bool dot_set = false;
  bool x_set = false;
  bool unary_operation = false;
  bool binary_operation = false;
  bool right_bracket_set = false;
  bool error = false;
  bool refreshed = false;

signals:
  void DataForGraph(QString xBegin_str, QString xEnd_str, QString yBegin_str,
                    QString yEnd_str, QString function);
};

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H
