#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>
#include <QDate>

extern "C" {
    #include "../s21_credit_calc.h"
}

enum {
    annuity = 0,
    differentiated = 1,
};

namespace Ui {
class Credit;
}

class Credit : public QWidget
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

private:
    Ui::Credit *ui;

private slots:
    void on_pushButton_annuity_clicked();
    void on_pushButton_differentiated_clicked();
    void credit_calc(int type);
    void show_months(int term);
};

#endif // CREDIT_H
