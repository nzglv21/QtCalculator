#include "poliz.h"
#include "QDebug"



void POLIZ::flush_stack(LexBox & cur_op)
{
    if (stack.empty()){
        stack.push_back(cur_op);
        return;
    }

    while (!stack.empty() && stack[stack.size()-1].priority >= cur_op.priority ){
        poliz.push_back(stack[stack.size()-1]);
        stack.pop_back();
    }
    stack.push_back(cur_op);
}

POLIZ::POLIZ(const QString &expr):source_expr(expr), poliz(), stack()
{}

void POLIZ::build()
{
    Lex scanner(source_expr.toUtf8().toStdString());

    LexBox lb;
    qDebug() << "LEXBOX";

    while ((lb=scanner.getLex()).type != LexType::EPS){
        lb.print();
        if (lb.type == LexType::Number){
            poliz.push_back(lb);
        }
        else{
            flush_stack(lb);
        }
    }

    qDebug() << "FINISH";

    while (!stack.empty()){
        poliz.push_back(stack[stack.size()-1]);
        stack.pop_back();
    }
    qDebug() << "_____";

    for (LexBox& l: poliz){
        l.print();
    }
}

double POLIZ::execute()
{
    vector<double> st;

    for (LexBox& lex: poliz){
        if (lex.type == LexType::Number){
            st.push_back(lex.value);
            continue;
        }
        if (lex.type == LexType::Precent){
            *st.rbegin() /= 100;
            continue;
        }

        if (st.size() < 2){
            break;
        }

        double b = *st.rbegin(); st.pop_back();
        double a = *st.rbegin(); st.pop_back();
        double res = 0.0;

        switch (lex.type) {
        case LexType::Plus: res = a + b; break;

        case LexType::Minus: res = a - b;break;
        case LexType::Mult: res = a*b;break;
        case LexType::Div:
            if (b == 0)
                throw std::runtime_error("Division by zero");
            res = a/ b;
            break;
        default:
            qDebug() << "Undefinded operation";
        }

        st.push_back(res);

    }

    return st[0];
}


