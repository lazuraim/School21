#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_DEPOSIT_H
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_DEPOSIT_H

#include <QDateEdit>
#include <QWidget>

#include "Controller/controller.h"

namespace Ui {
class Deposit;
}

namespace s21 {

class Deposit : public QWidget {
  Q_OBJECT

public:
  explicit Deposit(QWidget *parent = nullptr, Controller *controller = nullptr);
  ~Deposit();

private:
  Ui::Deposit *ui;
  Controller *controller;

private slots:
  void on_pushButton_calculate_clicked();
  void define_periodicity(s21::Date *d, QString periodicity);
};

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_DEPOSIT_H
