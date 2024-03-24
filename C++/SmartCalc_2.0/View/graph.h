#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_GRAPH_H
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_GRAPH_H

#include "Controller/controller.h"
#include "qcustomplot.h"
#include <QDialog>

namespace Ui {
class Graph;
}

namespace s21 {

class Graph : public QDialog {
  Q_OBJECT

public:
  explicit Graph(QWidget *parent = nullptr, Controller *c = nullptr);
  ~Graph();

private:
  Ui::Graph *ui;
  double xBegin = -10, xEnd = 10, yBegin = -10, yEnd = 10, h, X, result;
  QVector<double> x, y;
  Controller *controller;

public slots:
  bool CheckAxis(QString *axis);
  bool CheckAllAxes(QString xBegin_str, QString xEnd_str, QString yBegin_str,
                    QString yEnd_str);
  void PrintGraph(Controller *controller, QString xBegin_str, QString xEnd_str,
                  QString yBegin_str, QString yEnd_str, QString function);
};

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_GRAPH_H
