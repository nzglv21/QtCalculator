#ifndef LEX_H
#define LEX_H
#include <QString>
#include <QChar>
#include <string>

using std::vector;
using std::string;

enum LexType{
    Plus,   // плюс
    Minus,  // минус
    Mult, //*
    Div,    // делить
    Precent,
    EPS, //Пустой символ
    Number

};


const vector<char> operations = {
    '+',
    '-',
    '*',
    '/',
    '%'
};

const vector<LexType> operationsType = {
    LexType::Plus,
    LexType::Minus,
    LexType::Mult,
    LexType::Div,
    LexType::Precent
};

class LexBox{
public:
    LexType type;
    double value;
    int priority;
    LexBox(LexType t = LexType::EPS, double v = 0.0, int priority = 0) :
        type(t),
        value(v),
        priority(priority) {}
    void print();
};

class Lex
{
    string f;
    string::iterator iter;
    char c; //текущий символ
    LexType prev_lex = LexType::EPS;

    bool isDigit();
    bool isOperation();
    int getPriority(char);
    LexBox getOpLexBox();


public:

    Lex(const string&);
    void getChar(); //обновить текущий символ
    void putChar(); //сдвинуться назад
    LexBox getLex();
};

#endif // LEX_H
