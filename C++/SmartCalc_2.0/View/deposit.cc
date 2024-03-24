#include "View/deposit.h"

#include "ui_deposit.h"

namespace s21 {

Deposit::Deposit(QWidget *parent, Controller *c)
    : QWidget(parent), ui(new Ui::Deposit), controller(c) {
  ui->setupUi(this);

  connect(ui->pushButton_calculate, SIGNAL(clicked()), this,
          SLOT(on_pushButton_calculate_clicked()));
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_pushButton_calculate_clicked() {
  QDate replenishment = ui->replenishment_date->date();
  Date first_replenishment =
      Date(replenishment.day(), replenishment.month(), replenishment.year(), 0,
           ui->replenishment_amount->text().toDouble(), 0);
  define_periodicity(&first_replenishment,
                     ui->replenishment_periodicity->currentText());

  QDate withdrawal = ui->withdrawal_date->date();
  Date first_withdrawal =
      Date(withdrawal.day(), withdrawal.month(), withdrawal.year(), 0,
           -(ui->withdrawal_amount->text().toDouble()), 0);
  define_periodicity(&first_withdrawal,
                     ui->withdrawal_periodicity->currentText());

  QDate start_date = ui->beginning->date();
  Date start = Date(start_date.day(), start_date.month(), start_date.year(), 0,
                    ui->deposit_amount->text().toDouble(), 0);
  define_periodicity(&start, ui->periodicity->currentText());

  double interest_rate = ui->interest_rate->text().toDouble();
  int capitalization = ui->capitalization->isChecked();

  int current = 0;
  int term = ui->term->text().toDouble();
  if (ui->days->isChecked() == true) {
    current = term;
  } else if (ui->months->isChecked() == true) {
    current = controller->MonthToDays(term);
  } else if (ui->years->isChecked() == true) {
    current = controller->MonthToDays(term * 12);
  }

  DepositResult result = controller->DepositCalc(
      ui->tax_rate->text().toDouble(), start, first_replenishment,
      first_withdrawal, interest_rate, capitalization, current);

  ui->accrued_interest->setText(
      QString::number(result.accrued_interest, 'f', 2));
  ui->tax_amount->setText(QString::number(result.tax_amount, 'f', 2));
  ui->end_deposit->setText(QString::number(result.end_deposit, 'f', 2));
}

void Deposit::define_periodicity(Date *d, QString periodicity) {
  if (periodicity == "every day") {
    d->periodicity = kEVERY_DAY;
  } else if (periodicity == "every week") {
    d->periodicity = kEVERY_WEEK;
  } else if (periodicity == "every month") {
    d->periodicity = kEVERY_MONTH;
  } else if (periodicity == "every quarter") {
    d->periodicity = kEVERY_QUARTER;
  } else if (periodicity == "every half year") {
    d->periodicity = kEVERY_HALF_YEAR;
  } else if (periodicity == "every year") {
    d->periodicity = kEVERY_YEAR;
  } else if (periodicity == "at the end of the term") {
    d->periodicity = kAT_THE_END;
  }
}

} // namespace s21
