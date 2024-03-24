#include "form.h"

#include "mainwindow.h"
#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
}

Form::~Form() { delete ui; }

void Form::graph(QString xBegin_str, QString xEnd_str, QString yBegin_str,
                 QString yEnd_str, QString function) {
  ui->widget->clearGraphs();
  h = 0.01;

  xBegin = xBegin_str.toDouble();
  xEnd = xEnd_str.toDouble();
  yBegin = yBegin_str.toDouble();
  yEnd = yEnd_str.toDouble();

  ui->widget->xAxis->setRange(xBegin, xEnd);  // масштаб координатной оси
  ui->widget->yAxis->setRange(yBegin, yEnd);

  QByteArray to_char = function.toLocal8Bit();
  char *char_function = to_char.data();

  for (X = xBegin; X <= xEnd; X += h) {
    x.push_back(X);
    result = s21_result(char_function, X);
    y.push_back(result);
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}
