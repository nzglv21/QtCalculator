#ifndef POLIZ_H
#define POLIZ_H

#include "lex.h"
#include "vector"
#include "QString"

using std::vector;
class POLIZ
{
    vector<LexBox> poliz;
    vector<LexBox> stack;

    const QString &source_expr;
    int priority(LexType);
    void flush_stack(LexBox&);
public:
    POLIZ(const QString&);

    void build();
    double execute();




};

#endif // POLIZ_H
