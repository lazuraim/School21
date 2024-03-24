#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::CalcDeposit deposit;
  s21::Controller controller(&model, &deposit);
  s21::MainWindow view(&controller);
  view.show();
  return a.exec();
}
