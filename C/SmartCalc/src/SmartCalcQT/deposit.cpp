#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QWidget(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);

  connect(ui->pushButton_calculate, SIGNAL(clicked()), this,
          SLOT(on_pushButton_calculate_clicked()));
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_pushButton_calculate_clicked() {
  QDate replenishment_date = ui->replenishment_date->date();
  date first_replenishment = {0, 0, 0, 0, 0, 0};
  first_replenishment.day = replenishment_date.day();
  first_replenishment.month = replenishment_date.month();
  first_replenishment.year = replenishment_date.year();
  first_replenishment.amount = ui->replenishment_amount->text().toDouble();
  define_periodicity(&first_replenishment,
                     ui->replenishment_periodicity->currentText());

  QDate withdrawal_date = ui->withdrawal_date->date();
  date first_withdrawal = {0, 0, 0, 0, 0, 0};
  first_withdrawal.day = withdrawal_date.day();
  first_withdrawal.month = withdrawal_date.month();
  first_withdrawal.year = withdrawal_date.year();
  first_withdrawal.amount = ui->withdrawal_amount->text().toDouble();
  first_withdrawal.amount = -first_withdrawal.amount;
  define_periodicity(&first_withdrawal,
                     ui->withdrawal_periodicity->currentText());

  QDate start_date = ui->beginning->date();
  date start = {0, 0, 0, 0, 0, 0};
  start.day = start_date.day();
  start.month = start_date.month();
  start.year = start_date.year();
  start.amount = ui->deposit_amount->text().toDouble();
  define_periodicity(&start, ui->periodicity->currentText());

  term t = {ui->tax_rate->text().toDouble(),
            0,
            0,
            0,
            start,
            first_replenishment,
            first_withdrawal,
            0,
            0,
            0,
            0,
            0};
  double interest_rate = ui->interest_rate->text().toDouble();
  int capitalization = ui->capitalization->isChecked();
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  int term = ui->term->text().toDouble();
  if (ui->days->isChecked() == true) {
    t.current = term;
  } else if (ui->months->isChecked() == true) {
    t.current = months_to_days(&t, term);
  } else if (ui->years->isChecked() == true) {
    t.current = months_to_days(&t, term * 12);
  }
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ui->accrued_interest->setText(QString::number(accrued_interest, 'f', 2));
  ui->tax_amount->setText(QString::number(t.tax_amount, 'f', 2));
  ui->end_deposit->setText(QString::number(t.end_deposit, 'f', 2));
}

void Deposit::define_periodicity(date *d, QString periodicity) {
  if (periodicity == "every day") {
    d->periodicity = every_day;
  } else if (periodicity == "every week") {
    d->periodicity = every_week;
  } else if (periodicity == "every month") {
    d->periodicity = every_month;
  } else if (periodicity == "every quarter") {
    d->periodicity = every_quarter;
  } else if (periodicity == "every half year") {
    d->periodicity = every_half_year;
  } else if (periodicity == "every year") {
    d->periodicity = every_year;
  } else if (periodicity == "at the end of the term") {
    d->periodicity = at_the_end;
  }
}
