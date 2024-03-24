#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>
#include <QDateEdit>

extern "C" {
    #include "../s21_deposit_calc.h"
}

namespace Ui {
class Deposit;
}

class Deposit : public QWidget
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

private:
    Ui::Deposit *ui;

private slots:
    void on_pushButton_calculate_clicked();
    void define_periodicity(date *d, QString periodicity);
};

#endif // DEPOSIT_H
