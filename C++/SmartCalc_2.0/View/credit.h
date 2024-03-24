#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_CREDIT_H
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_CREDIT_H

#include <QDate>
#include <QWidget>

#include "Controller/controller.h"

namespace Ui {
class Credit;
}

namespace s21 {

class Credit : public QWidget {
  Q_OBJECT

public:
  explicit Credit(QWidget *parent = nullptr, Controller *c = nullptr);
  ~Credit();

private:
  Ui::Credit *ui;
  Controller *controller;

private slots:
  void on_pushButton_annuity_clicked();
  void on_pushButton_differentiated_clicked();
  void CreditView(int type);
  void ShowMonths(int term);
};

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_CREDIT_H
