#include "calculator.h"

Calculator::Calculator(QWidget *parent)
{
    QChar actions[4][4] =
        {
            {'7', '8', '9', '/'},
            {'4', '5', '6', '*'},
            {'1', '2', '3', '-'},
            {'0', '.', '=', '+'},
        };

    current = &operation.first;
    label = new QLabel(*current);
    label->setMinimumSize(150, 50);
    QFont font = label->font();
    font.setPointSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(label, 0, 0, 1, 4, Qt::AlignRight);
    layout->addWidget(createButton("CE"), 1, 3);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            layout->addWidget(createButton(actions[i][j]), i + 2, j);

    setLayout(layout);
}

QPushButton *Calculator::createButton(QString str)
{
    QPushButton *btn = new QPushButton(str);
    btn->setMinimumSize(40, 40);
    connect(btn, SIGNAL(clicked()), SLOT(buttonClicked()));
    return btn;
}

void Calculator::buttonClicked()
{
    QString str = ((QPushButton *)sender())->text();

    if (str == "CE")
    {
        clear();
        return;
    }
    else if (str[0].isDigit())
    {
        current->push_back(str[0]);
        format(current);
    }
    else if (str == ".")
    {
        if (!current->contains('.'))
            current->push_back(str[0]);
    }
    else if (str == "=")
    {
        calculate();
    }
    else // if operator
    {
        if (operation.hasOP())
        {
            calculate();
        }
        else
        {
            operation.setOP(str[0]);
            current = &operation.second;
        }
    }

    label->setText(*current);
}

void Calculator::calculate()
{
    operation.first = QString::number(operation.calc());
    operation.second = "0";
    operation.op = Operation::NONE;
    current = &operation.first;
}

void Calculator::format(QString *str)
{
    str->remove(QRegExp("^[0]*"));
    if (str->isEmpty())
        *str = "0";
    if ((*str)[0] == '.')
        str->push_front('0');
}

void Calculator::clear()
{
    operation.clr();
    label->setText("0");
}

double Operation::calc()
{
    double res = 0.0f;
    switch (op)
    {
    case ADD:
        res = first.toDouble() + second.toDouble();
        break;
    case SUB:
        res = first.toDouble() - second.toDouble();
        break;
    case MUL:
        res = first.toDouble() * second.toDouble();
        break;
    case DIV:
        res = first.toDouble() / second.toDouble();
        break;
    }
    return res;
}

void Operation::setOP(QChar _operator)
{
    if (_operator == '+')
        op = Operator::ADD;
    else if (_operator == '-')
        op = Operator::SUB;
    else if (_operator == '*')
        op = Operator::MUL;
    else if (_operator == '/')
        op = Operator::DIV;
    else
        op = Operator::NONE;
}

void Operation::clr()
{
    first = "0";
    second = "0";
    op = Operation::NONE;
}