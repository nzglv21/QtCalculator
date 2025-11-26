#include "lex.h"
#include "QDebug"
#include <iostream>

Lex::Lex(const std::string& expr):f(expr), iter(f.begin()) {}

void Lex::getChar()
{
        c  = (*iter);
        iter++;
}

void Lex::putChar(){
    c = (*(--iter));
}

bool Lex::isDigit(){
    int digit = c - '0';
    return (digit >= 0) && (digit <= 9);
}

LexBox Lex::getOpLexBox(){
    for(int i=0; i<operations.size(); ++i)
        if (c == operations[i]){
            return LexBox(operationsType[i], 0.0, getPriority(c));
        }
    return LexBox(LexType::EPS);
}

bool Lex::isOperation(){
    for (char op :operations){
        if (c == op)
            return true;
    }
    return false;
}

int Lex::getPriority(char op)
{
    switch(op){
    case '+':case '-': return 1;

    case '*':case '/':case '%': return 2;

    default: return 0; // числа и EPS
    }
}


LexBox Lex::getLex(){
    enum state {
        S,        //initial state
        I,         //integer state
        F,          //Fractional
    };
    double number = 0.0;
    double fr = 0.0;
    double power = 10.0;
    int sign = 1;

    state CS = S;
    getChar();
    while (true){
        switch(CS){
        case S:{
            if (c == '%'){
                return getOpLexBox();
            }
            if (isOperation() && prev_lex == LexType::Number){
                prev_lex =  getOpLexBox().type;
                return getOpLexBox();
            }
            else if (c == '-' && prev_lex != LexType::Number){ //унарный минус
                sign = -1;
                getChar();
                break;
            }

            if (isDigit()){
                CS = I;
                number*=10;
                number+= c-'0';
                getChar();
                break;
            }

            if (c == '\0')
                return LexBox(LexType::EPS);
        }
        case I:{//integer
            if (isDigit()){
                number*=10;
                number+= c - '0';
                getChar();
                break;
            }
            if (isOperation()){
                putChar();
                prev_lex = LexType::Number;
                return LexBox(LexType::Number, number*sign);
            }
            if (c == '.'){
                getChar();
                CS = F;
                break;
            }
            if (c == '\0'){
                putChar();
                return LexBox(LexType::Number, number*sign);
            }
        }
        case F:{
            if (isDigit()){
                std::cout << c << "float" << number + (double(c - '0'))/double(power) << (double(c - '0'))/double(power);
                number += (double(c - '0')) / double(power);
                power *= 10;
                getChar();
                break;
            }
            if (c != '\0')
                putChar();

            prev_lex = LexType::Number;

            return LexBox(
                    LexType::Number
                    , number*sign);
        }
        }
    }
}

void LexBox::print()
{
    if (type == LexType::Number)
        qDebug() << QString::number(value, 'f');
    else{
        qDebug() << operations[type] << "oper";
    }
}
