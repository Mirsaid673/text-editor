#pragma once

#include <QtWidgets>
#include <QStack>

struct Operation
{
    QString first = "0";
    QString second = "0";
    enum Operator
    {
        NONE,
        ADD,
        SUB,
        MUL,
        DIV,
    } op = NONE;

    double calc();
    void clr();
    void setOP(QChar _operator);
    bool hasOP() { return op != NONE; }
};

class Calculator : public QWidget
{
    Q_OBJECT
private:
    QLabel *label;

    Operation operation;
    QString *current;

public:
    Calculator(QWidget *parent = nullptr);

    QPushButton *createButton(QString symbol);
    void clear();

public slots:
    void buttonClicked();
    void calculate();
    void format(QString *str);
};