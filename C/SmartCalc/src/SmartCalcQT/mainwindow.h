#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "qcustomplot.h"
#include <credit.h>
#include <deposit.h>
#include <form.h>

extern "C" {
    #include "../s21_SmartCalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void without_changes();
    void dot();
    void result();
    void AC();
    void CE();
    void plus_minus();
    void on_pushButton_graph_clicked();
    void on_pushButton_credit_clicked();
    void on_pushButton_deposit_clicked();

private:
    Ui::MainWindow *ui;
    Form *form;
    Credit *credit;
    Deposit *deposit;

signals:
    void DataForGraph(QString xBegin_str, QString xEnd_str, QString yBegin_str, QString yEnd_str, QString function);

};
#endif // MAINWINDOW_H
