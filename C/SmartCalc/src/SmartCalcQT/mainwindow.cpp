#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  form = new Form();
  connect(this, &MainWindow::DataForGraph, form, &Form::graph);

  credit = new Credit();
  connect(ui->pushButton_credit, SIGNAL(clicked()), credit,
          SLOT(on_pushButton_credit_clicked()));

  deposit = new Deposit();
  connect(ui->pushButton_deposit, SIGNAL(clicked()), deposit,
          SLOT(on_pushButton_deposit_clicked()));

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(without_changes()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_power, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(without_changes()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(without_changes()));
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(without_changes()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(AC()));
  connect(ui->pushButton_CE, SIGNAL(clicked()), this, SLOT(CE()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(result()));
  connect(ui->pushButton_pl_min, SIGNAL(clicked()), this, SLOT(plus_minus()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::without_changes() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->result_show->text() == "0") {
    ui->result_show->setText(button->text());
  } else {
    ui->result_show->setText(ui->result_show->text() + button->text());
  }
}

void MainWindow::plus_minus() {
  if (ui->result_show->text() == "0") {
    ui->result_show->setText("-");
  } else if (!(ui->result_show->text().endsWith('-'))) {
    ui->result_show->setText(ui->result_show->text() + "-");
  } else {
    QString res = ui->result_show->text();
    res.chop(1);
    ui->result_show->setText(res);
  }
}

void MainWindow::result() {
  double x = ui->x_value->text().toDouble();
  QString str_show = ui->result_show->text();
  QByteArray ba = str_show.toLocal8Bit();
  char *str_char = ba.data();
  QString res_string = QString::number(s21_result(str_char, x), 'f', 7);
  if (s21_check_str(str_char)) {
    ui->result_show->setText("error");
  } else {
    ui->result_show->setText(res_string);
  }
}

void MainWindow::dot() {
  QPushButton *button = (QPushButton *)sender();
  if (!(ui->result_show->text().endsWith('.'))) {
    ui->result_show->setText(ui->result_show->text() + button->text());
  }
}

void MainWindow::AC() { ui->result_show->setText("0"); }

void MainWindow::CE() {
  QString res = ui->result_show->text();
  res.chop(1);
  ui->result_show->setText(ui->result_show->text());
}

void MainWindow::on_pushButton_graph_clicked() {
  emit DataForGraph(ui->min_x->text(), ui->max_x->text(), ui->min_y->text(),
                    ui->max_y->text(), ui->result_show->text());
  form->show();
}

void MainWindow::on_pushButton_credit_clicked() { credit->show(); }

void MainWindow::on_pushButton_deposit_clicked() { deposit->show(); }
