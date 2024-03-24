#include "graph.h"

#include <iostream>

#include "ui_graph.h"

namespace s21 {

Graph::Graph(QWidget *parent, Controller *c)
    : QDialog(parent), ui(new Ui::Graph), controller(c) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

bool Graph::CheckAxis(QString *axis) {
  QByteArray ba = (*axis).toLocal8Bit();
  char *axis_char = ba.data();

  for (size_t i = 0; i < strlen(axis_char); ++i) {
    if (!isdigit(axis_char[i])) {
      if (!(axis_char[i] == '-' && i == 0)) {
        return false;
      }
    }
  }
  return true;
}

bool Graph::CheckAllAxes(QString xBegin_str, QString xEnd_str,
                         QString yBegin_str, QString yEnd_str) {
  if (!CheckAxis(&xBegin_str) || !CheckAxis(&xEnd_str) ||
      !CheckAxis(&yBegin_str) || !CheckAxis(&yEnd_str)) {
    return false;
  }
  return true;
}

void Graph::PrintGraph(Controller *controller, QString xBegin_str,
                       QString xEnd_str, QString yBegin_str, QString yEnd_str,
                       QString function) {
  ui->widget->clearGraphs();
  if (CheckAllAxes(xBegin_str, xEnd_str, yBegin_str, yEnd_str)) {
    h = 0.01;
    if (xBegin_str != nullptr && xEnd_str != nullptr) {
      xBegin = xBegin_str.toDouble();
      xEnd = xEnd_str.toDouble();
    }

    if (yBegin_str != nullptr && yEnd_str != nullptr) {
      yBegin = yBegin_str.toDouble();
      yEnd = yEnd_str.toDouble();
    }

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

    QByteArray to_char = function.toLocal8Bit();
    char *char_function = to_char.data();

    for (X = xBegin; X <= xEnd; X += h) {
      x.push_back(X);
      result = std::stod(controller->ResultForGraph(char_function, X));
      y.push_back(result);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
  }
}

} // namespace s21
