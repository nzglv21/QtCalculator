#include "calculator.h"
#include "lex.h"
#include "QDebug"
#include <iostream>
#include "poliz.h"


void Calculator::trimZeros(QString &input)
{

    // Если нет точки — ничего не делаем
    if (!input.contains('.'))
        return;

    // Удаляем конечные нули
    while (input.endsWith('0'))
        input.chop(1);

    // Если теперь строка заканчивается на точку — удаляем и её
    if (input.endsWith('.'))
        input.chop(1);

    // Если получилось пусто — вернуть "0"
    if (input.isEmpty())
        input += '0';

}

Calculator::Calculator(QObject *parent)
    : QObject{parent}
    ,m_expression("0")
{}

void Calculator::onButtonPressed(const QString &text)
{

}

void Calculator::onOperationButtonPressed(const QString &op)
{
    QString::iterator last_sym = m_expression.end()-1;

    qDebug() << *last_sym << op;

    if (isDigit(*last_sym) || (*last_sym=='.') || (*last_sym == '%')){
        m_expression += op[0];
        emit expressionChanged(m_expression);
        return;
    }

    //Тот же знак, ничего не делаем
    if (*last_sym == op[0])
        return;

    //если два последние это операции, то заменяем опа символа на новый
    if (last_sym!=m_expression.begin()
            && (isOperation(*last_sym))
            && isOperation(*(last_sym-1))
        && ((*(last_sym - 1) != '%'))
        ){
        m_expression.chop(1);
        --last_sym;
        *last_sym = op[0];
        emit expressionChanged(m_expression);
        return;

    }


    // 5*-4 = -20
    if (op[0] == '-' && (*last_sym == '*' || *last_sym=='\\' )){
        m_expression += op[0];
        emit expressionChanged(m_expression);
        return;
    }


    //просто заменяем знак
    *last_sym = op[0];
    emit expressionChanged(m_expression);
    return;

}

void Calculator::onNumberButtonPressed(const QString &number)
{
    QString::iterator begin = getLastExpression(); //указывает либо на операцию, либо на начало слова
    QString::iterator end = m_expression.end();
    QChar n = number[0];

    if (begin == nullptr){
        m_expression += n;
        emit expressionChanged(m_expression);
        return;
    }

    if (*begin == '0' && begin+1 == end){ //последнее выражение просто 0. 0->num
        *begin = n;
        emit expressionChanged(m_expression);
        return;
    }

    m_expression += n;
    emit expressionChanged(m_expression);
}

// Point Button Pressed 5345.345
void Calculator::onPointButtonPressed()
{
    QString::iterator p = getLastExpression();

    qDebug() << *p;

    if (p == m_expression.end()){
        m_expression.append('0');
        m_expression.append('.');
        emit expressionChanged(m_expression);
    }

    //Check, that point is yet
    while (p != m_expression.end()){
        if (*p == '.')
            return;
        ++p;
    }

    //if no, append
    m_expression.append('.');
    emit expressionChanged(m_expression);
    return;
}

//Считаем результат
void Calculator::onResultButtonPressed()
{
    //Собираем ПОЛИЗ
    POLIZ p(m_expression);
    p.build();

    //Выполняем
    try {
        double result = p.execute();
        m_expression = QString::number(result, 'f', 10);
        trimZeros(m_expression);
        emit expressionChanged(m_expression);
        qDebug() << result;
    }
    catch (const std::exception &e) {
        setExpression(QString(e.what()));
        m_expression = QString("0");
        qDebug() << "Error:" << e.what();
    }
    catch (...) {
        qDebug() << "Unknown error";
    }


}

void Calculator::onClearButtonPressed()
{
    setExpression(QString("0"));
}

void Calculator::onBackspaceButtonPressed()
{
    //Стираем пока не остался один символ
    if (m_expression.length() > 1){
        m_expression.chop(1);
        emit expressionChanged(m_expression);
        return;
    }

    //Последний символ заменяем на 0
    setExpression("0");

}



QString::iterator Calculator::getLastExpression()
{
    QString::iterator p= m_expression.end();
    QString::iterator begin = m_expression.begin();
    while((p != begin) && !isOperation(*p))
        --p;
    if (isOperation(*p))
        ++p;
    return p;
}

bool Calculator::isOperation(QChar c) const
{
    for (const char& op: operations){
        if (op == c)
            return true;
    }
    return false;
}

bool Calculator::isDigit(QChar c) const
{
    return (c >= '0') && (c <= '9');
}


QString Calculator::expression() const
{
    return m_expression;
}

void Calculator::setExpression(const QString &newExpression)
{
    if (m_expression == newExpression)
        return;
    m_expression = newExpression;
    emit expressionChanged(m_expression);
}
