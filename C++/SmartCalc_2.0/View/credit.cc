#include "View/credit.h"

#include <iostream>

#include "ui_credit.h"

namespace s21 {

Credit::Credit(QWidget *parent, Controller *c)
    : QWidget(parent), ui(new Ui::Credit), controller(c) {
  ui->setupUi(this);

  connect(ui->pushButton_annuity, SIGNAL(clicked()), this,
          SLOT(on_pushButton_annuity_clicked()));
  connect(ui->pushButton_differentiated, SIGNAL(clicked()), this,
          SLOT(on_pushButton_differentiated_clicked()));

  ui->tableWidget->setRowCount(1);
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "month"
                                                           << "payment");
}

Credit::~Credit() { delete ui; }

void Credit::CreditView(int type) {
  double credit_amount = ui->credit_amount->text().toDouble();
  double interest_rate = ui->interest_rate->text().toDouble();
  int term = ui->term->text().toDouble();
  if (ui->years->isChecked() == true) {
    term = term * 12;
  }

  double monthly_payment = 0;
  double total_payment = 0;
  ui->tableWidget->setRowCount(term);

  for (int i = 0; i < term; ++i) {
    monthly_payment =
        controller->CreditCalc(type, credit_amount, interest_rate, term, i);

    total_payment += monthly_payment;
    QTableWidgetItem *item =
        new QTableWidgetItem(QString::number(monthly_payment, 'f', 2));
    ui->tableWidget->setItem(i, 1, item);
  }

  ui->total_payment->setText(QString::number(total_payment, 'f', 2));
  ui->overpayment->setText(
      QString::number(total_payment - credit_amount, 'f', 2));
  ShowMonths(term);
}

void Credit::ShowMonths(int term) {
  QDate date = QDate::currentDate();
  int month = date.month();
  int year = date.year();
  QString format = "MMMM yyyy";
  for (int i = 0; i < term; i++) {
    month = month % 12;
    if (month == 0) {
      month = 12;
    }
    date.setDate(year, month, 1);
    QTableWidgetItem *item = new QTableWidgetItem(date.toString(format));
    ui->tableWidget->setItem(i, 0, item);
    if (month == 12) {
      year++;
    }
    month++;
  }
}

void Credit::on_pushButton_annuity_clicked() { CreditView(kANNUITY); }

void Credit::on_pushButton_differentiated_clicked() {
  CreditView(kDIFFERENTIATED);
}

} // namespace s21
