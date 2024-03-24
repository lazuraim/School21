#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(c) {
  ui->setupUi(this);
  ui->result_show->setText("");
  QApplication::setWindowIcon(QIcon(":/calculator.ico"));

  graph = new Graph();
  connect(ui->pushButton_graph, SIGNAL(clicked()), graph,
          SLOT(on_pushButton_graph_clicked()));

  credit = new Credit(nullptr, controller);
  connect(ui->pushButton_credit, SIGNAL(clicked()), credit,
          SLOT(on_pushButton_credit_clicked()));

  deposit = new Deposit(nullptr, controller);
  connect(ui->pushButton_deposit, SIGNAL(clicked()), deposit,
          SLOT(on_pushButton_deposit_clicked()));

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(binary_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(minus()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(binary_operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(binary_operations()));
  connect(ui->pushButton_power, SIGNAL(clicked()), this,
          SLOT(binary_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(binary_operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(unary_operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(unary_operations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(unary_operations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(unary_operations()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(unary_operations()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(unary_operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(unary_operations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(unary_operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(unary_operations()));

  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(binary_operations()));

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(x_button()));

  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(right_bracket()));
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(left_bracket()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(AC()));
  connect(ui->pushButton_CE, SIGNAL(clicked()), this, SLOT(CE()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(result()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::without_changes() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_show->setText(ui->result_show->text() + button->text());
}

void MainWindow::Reset() {
  if (error) {
    ui->result_show->setText("");
    ResetFlags();
  }
}

void MainWindow::ResetFlags() {
  digit = false;
  dot_set = false;
  unary_operation = false;
  binary_operation = false;
  x_set = false;
  right_bracket_set = false;
  error = false;
  refreshed = false;
}

void MainWindow::x_button() {
  Reset();
  if (!x_set && !digit) {
    without_changes();
    x_set = true;
    unary_operation = false;
    binary_operation = false;
    dot_set = false;
    digit = false;
    right_bracket_set = false;
    error = false;
    refreshed = false;
  }
}

void MainWindow::unary_operations() {
  Reset();
  if (!digit) {
    without_changes();
    digit = false;
    dot_set = false;
    unary_operation = true;
    binary_operation = false;
    x_set = false;
    right_bracket_set = false;
    refreshed = false;
  }
}

void MainWindow::binary_operations() {
  Reset();
  if (!binary_operation && (digit || right_bracket_set || x_set)) {
    without_changes();
    digit = false;
    dot_set = false;
    binary_operation = true;
    unary_operation = false;
    x_set = false;
    right_bracket_set = false;
    refreshed = false;
  }
}

void MainWindow::right_bracket() {
  Reset();
  without_changes();
  digit = false;
  dot_set = false;
  unary_operation = false;
  binary_operation = false;
  x_set = false;
  right_bracket_set = true;
  refreshed = false;
}

void MainWindow::left_bracket() {
  Reset();
  without_changes();
  digit = false;
  dot_set = false;
  unary_operation = false;
  binary_operation = false;
  x_set = false;
  refreshed = false;
}

void MainWindow::digits() {
  Reset();
  if (!x_set && !right_bracket_set) {
    without_changes();
    digit = true;
    unary_operation = false;
    binary_operation = false;
    refreshed = false;
  }
}

void MainWindow::minus() {
  Reset();
  if (!(ui->result_show->text().endsWith('-'))) {
    if (!(ui->result_show->text().endsWith('-'))) {
      ui->result_show->setText(ui->result_show->text() + "-");
    } else {
      QString res = ui->result_show->text();
      res.chop(1);
      ui->result_show->setText(res);
    }

    digit = false;
    dot_set = false;
    binary_operation = true;
    unary_operation = false;
    x_set = false;
    right_bracket_set = false;
    refreshed = false;
  }
}

void MainWindow::result() {
  if (!unary_operation && !binary_operation) {
    double X = ui->x_value->text().toDouble();
    QString X_str = ui->x_value->text();
    QByteArray X_ba = X_str.toLocal8Bit();
    char *X_char = X_ba.data();

    QString str_show = ui->result_show->text();
    QByteArray ba = str_show.toLocal8Bit();
    char *str_char = ba.data();

    QString res =
        QString::fromStdString(controller->Calculate(str_char, X_char, X));
    error = (res == "error") ? true : false;
    ui->result_show->setText(res);
    refreshed = true;
  }
}

void MainWindow::dot() {
  Reset();
  QPushButton *button = (QPushButton *)sender();
  if (!refreshed && !(ui->result_show->text().endsWith('.')) && !dot_set &&
      digit) {
    ui->result_show->setText(ui->result_show->text() + button->text());
  }
  dot_set = true;
}

void MainWindow::AC() {
  ui->result_show->setText("");
  unary_operation = false;
  binary_operation = false;
  digit = false;
  dot_set = false;
  x_set = false;
  right_bracket_set = false;
  refreshed = true;
}

void MainWindow::CE() {
  Reset();
  QString res = ui->result_show->text();
  res.resize(res.size() - 1);
  ui->result_show->setText(res);
}

void MainWindow::on_pushButton_graph_clicked() {
  Graph graph = Graph(nullptr, controller);
  graph.PrintGraph(controller, ui->min_x->text(), ui->max_x->text(),
                   ui->min_y->text(), ui->max_y->text(),
                   ui->result_show->text());
  graph.setModal(true);
  graph.exec();
}

void MainWindow::on_pushButton_credit_clicked() { credit->show(); }

void MainWindow::on_pushButton_deposit_clicked() { deposit->show(); }

} // namespace s21
