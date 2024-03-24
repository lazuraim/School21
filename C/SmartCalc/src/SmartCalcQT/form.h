#ifndef FORM_H
#define FORM_H

#include <QWidget>


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private:
    Ui::Form *ui;
    double xBegin, xEnd, yBegin, yEnd, h, X, result;
    QVector<double> x, y;

public slots:
    void graph(QString xBegin_str, QString xEnd_str, QString yBegin_str, QString yEnd_str, QString function);
};

#endif // FORM_H
