#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <qqml.h>
#include <QString>
#include <QChar>
#include <string>
class Calculator : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString expression READ expression WRITE setExpression NOTIFY expressionChanged FINAL)
    QString expr;

public:
    explicit Calculator(QObject *parent = nullptr);

    QString expression() const;
    void setExpression(const QString &newExpression);

public slots:
    void onButtonPressed(const QString& text);
    void onOperationButtonPressed(const QString& op); //+ - / *
    void onNumberButtonPressed(const QString& number); // '8', '9' ...
    void onPointButtonPressed(); // '.'
    void onResultButtonPressed();
    void onClearButtonPressed();
    void onBackspaceButtonPressed();

signals:
    void expressionChanged(const QString &newExpression);
private:
    QString m_expression;
    QString::iterator getLastExpression();
    bool isOperation(QChar c) const;
    bool isDigit(QChar c) const;
    void trimZeros(QString &input);
};

#endif // CALCULATOR_H
