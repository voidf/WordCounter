﻿#define IMPORT_MODULE
#ifndef QmlInterface_H
#define QmlInterface_H
#include <unordered_map>
#include "BigInteger.cpp"
#include "OrderedList.cpp"
#include "LinkedList.cpp"
#include "BST.cpp"
#include <QJsonDocument>
#include <QDebug>
#include <QString>
#include <QObject>

#include <string>
#include <QObject>
#include <QUrl>
#include <QVariant>

struct MT
{
    char a;
    BigIntegerDomain::BigInteger<256> b;
    double c;
    //    MT(const char _a,BigIntegerDomain::BigInteger<256> &_b, double _c):a(_a),b(_b),c(_c){}
    MT(char _a, BigIntegerDomain::BigInteger<256> &_b, double _c) : a(_a), b(_b), c(_c) {}
    MT(char &&_a, BigIntegerDomain::BigInteger<256> &&_b, double _c) : a(_a), b(_b), c(_c) {}
    MT() : a(0), b(0), c(0) {}
};

extern QObject *rootobj;
class QmlInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString _query_expression READ rfurl WRITE wfurl)
    //    Q_PROPERTY(QString _default_codec READ rdc WRITE wdc)

public:
    explicit QmlInterface(QObject *parent = nullptr) : QObject(parent) {}

    QString rfurl() const { return _query_expression; }
    void wfurl(QString s) { _query_expression = s; }

    //    QString rdc() const { return _default_codec; }
    //    void wdc(QString tdc) { _default_codec = tdc; }

public:
    Q_INVOKABLE void handle_exp(QVariant q)
    try
    {
        QString s = q.toString().simplified();
        auto minus_tag = false;
        auto float_tag = false;
        OrderedList::OrderedList<MT> suffix_exp;
        OrderedList::OrderedList<MT> _calc_stack;
        OrderedList::OrderedList<char> operators;
        BST::BST<MT> B;

        std::string handler;
        auto calc_result = rootobj->findChild<QObject *>("calc_result");
        for (auto i : s)
        {
            //            qDebug() << i;
            if (_operators.indexOf(i) != -1) // 处理操作符
            {
                if (handler.length() == 0 and i == '-')
                    minus_tag ^= 1;
                else
                {
                    if (i == '-' and (handler.back() == 'e' or handler.back() == 'E'))
                    {
                        handler.push_back('-');
                        continue;
                    }
                    if (handler.length())
                    {
                        if (float_tag)
                        {
                            char *p;
                            double cur = strtod(handler.c_str(), &p);
                            if (minus_tag)
                                cur = -cur;
                            suffix_exp.direct_append('F', BigIntegerDomain::BigInteger<256>(), cur);
                        }
                        else
                        {
                            BigIntegerDomain::BigInteger<256> cur;
                            cur.fromDecimal(handler);
                            qDebug() << cur.toDecimal().c_str();
                            if (minus_tag)
                                cur = -cur;
                            suffix_exp.direct_append('I', cur, 0.0);
                        }
                        float_tag = minus_tag = false;
                        handler.clear();
                    }

                    if (i == ')')
                    {
                        while (!operators.empty() and operators.back() != '(')
                        {
                            suffix_exp.direct_append(operators.pop(), BigIntegerDomain::BigInteger<256>(), 0.0);
                        }
                        if (operators.empty())
                        {
                            QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant("表达式非法")));
                            return;
                        }
                        operators.pop();
                    }
                    else if (i == '(')
                    {
                        operators.direct_append('(');
                    }
                    else
                    {
                        while (!operators.empty() and _operator_priority[operators.back()] >= _operator_priority[i.toLatin1()])
                        {
                            suffix_exp.direct_append(operators.pop(), BigIntegerDomain::BigInteger<256>(), 0.0);
                        }
                        operators.direct_append(i.toLatin1());
                    }
                }
            }
            else
            {
                if (_symbols.indexOf(i) != -1)
                    float_tag = true;
                handler.push_back(i.toLatin1());
            }
        }

        if (handler.length() != 0)
        {
            if (float_tag)
            {
                char *p;
                double cur = strtod(handler.c_str(), &p);
                if (minus_tag)
                    cur = -cur;
                suffix_exp.direct_append('F', BigIntegerDomain::BigInteger<256>(), cur);
            }
            else
            {
                BigIntegerDomain::BigInteger<256> cur;
                cur.fromDecimal(handler);
                if (minus_tag)
                    cur = -cur;
                suffix_exp.direct_append('I', cur, 0.0);
            }
            float_tag = minus_tag = false;
            handler.clear();
        }
        while (!operators.empty())
            suffix_exp.direct_append(operators.pop(), BigIntegerDomain::BigInteger<256>(), 0.0);

        auto first_build = true;
        OrderedList::OrderedList<std::shared_ptr<BST::BST<MT>::Content>> _pointer_stack;
        for (auto &[i, j, k] : suffix_exp)
        {
            if (i == 'I' or i == 'F')
            {
                //                _calc_stack.direct_append(i, j, k);
                auto tpp = B.direct_generate_content(i, j, k);
                _pointer_stack.append(tpp);
            }
            else
            {
                //                if (first_build)
                //                {
                //                    first_build = false;
                //                    auto p = B.direct_insert_left(B._header, i, j, k);
                auto parent = B.direct_generate_content(i, j, k);

                if (_pointer_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant("表达式非法")));
                    return;
                }
                auto oprb = _pointer_stack.pop();
                //                    B.insert_left(p, _calc_stack.pop());
                if (_pointer_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant("表达式非法")));
                    return;
                }
                auto opra = _pointer_stack.pop();
                B.lconnect(parent, opra);
                B.rconnect(parent, oprb);
                _pointer_stack.append(parent);
                //                    B.insert_right(p, _calc_stack.pop());
                //                }
                //                else
                //                {
                //                    auto p = B.direct_insert_left(B._header, i, j, k);
                //                    B.insert_right(p, _calc_stack.pop());
                //                }
            }
            //            qDebug() << i << " " << j.toDecimal().c_str() << " " << k;
        }
        if (_pointer_stack.empty())
        {
            QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant("表达式非法")));
            return;
        }
        auto tpp = _pointer_stack.pop();
        B.lconnect(B._header, tpp);
        B.update_beginnings();
        for (auto &[i, j, k] : suffix_exp)
        {
            qDebug() << i << " " << j.toDecimal().c_str() << " " << k;
            if (i == 'I' or i == 'F')
                _calc_stack.direct_append(i, j, k);
            else
            {
                if (_calc_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant("表达式非法")));
                    return;
                }
                auto oprb = _calc_stack.pop();
                if (_calc_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant("表达式非法")));
                    return;
                }
                auto opra = _calc_stack.pop();
                if (oprb.a == 'F' or oprb.a == 'F')
                {
                    double __a = 0, __b = 0;
                    if (opra.a == 'F' and oprb.a == 'F')
                        __a = opra.c, __b = oprb.c;
                    else if (opra.a == 'F' and oprb.a == 'I')
                        __a = opra.c, __b = oprb.b.toDouble();
                    else if (opra.a == 'I' and oprb.a == 'F')
                        __a = opra.b.toDouble(), __b = oprb.c;
                    else
                        __a = opra.b.toDouble(), __b = oprb.b.toDouble();
                    switch (i)
                    {
                    case '+':
                        _calc_stack.direct_append('F', j, __a + __b);
                        break;
                    case '-':
                        _calc_stack.direct_append('F', j, __a - __b);
                        break;
                    case '*':
                        _calc_stack.direct_append('F', j, __a * __b);
                        break;
                    case '/':
                        _calc_stack.direct_append('F', j, __a / __b);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    qDebug() << opra.b.toDecimal().c_str() << oprb.b.toDecimal().c_str();
                    switch (i)
                    {
                    case '+':
                        _calc_stack.direct_append('I', opra.b + oprb.b, k);
                        break;
                    case '-':
                        _calc_stack.direct_append('I', opra.b - oprb.b, k);
                        break;
                    case '*':
                        _calc_stack.direct_append('I', opra.b * oprb.b, k);
                        break;
                    case '/':
                        _calc_stack.direct_append('I', opra.b / oprb.b, k);
                        break;
                    case '%':
                        _calc_stack.direct_append('I', opra.b % oprb.b, k);
                        break;
                    default:
                        break;
                    }
                }
            }
            qDebug() << i << " " << j.toDecimal().c_str() << " " << k;
        }
        //        qDebug() << "======";
        QString res;
        if (_calc_stack.back().a == 'I')
            res.append(_calc_stack.back().b.toDecimal().c_str());
        else
            res = QString::number(_calc_stack.back().c, 10, 8);

        QObject *view_area = rootobj->findChild<QObject *>("input_window");
        qDebug() << res;
        QVariant fst(res);
        QMetaObject::invokeMethod(view_area, "set_res", Q_ARG(QVariant, fst));
        QString a1, a2, a3;
        for (auto &[i, j, k] : B)
        {
            //            qDebug() << i << " " << j.toDecimal().c_str() << " " << k;
            if (i == 'I')
                a1.append(j.toDecimal().c_str());
            else if (i == 'F')
                a1.append(QString::number(k, 10, 8));
            else
                a1.append(i);
            a1.append(' ');
        }
        for (auto a = B.preotbegin(); a != B.end(); B.preotmove(a))
        {
            auto &[i, j, k] = *a;
            if (i == 'I')
                a2.append(j.toDecimal().c_str());
            else if (i == 'F')
                a2.append(QString::number(k, 10, 8));
            else
                a2.append(i);
            a2.append(' ');
        }
        for (auto a = B.postotbegin(); a != B.end(); B.postotmove(a))
        {
            auto &[i, j, k] = *a;
            if (i == 'I')
                a3.append(j.toDecimal().c_str());
            else if (i == 'F')
                a3.append(QString::number(k, 10, 8));
            else
                a3.append(i);
            a3.append(' ');
        }

        QMetaObject::invokeMethod(calc_result, "set_res", Q_ARG(QVariant, a1), Q_ARG(QVariant, a2), Q_ARG(QVariant, a3));
        QObject *sketch = rootobj->findChild<QObject *>("sketch");
        QMetaObject::invokeMethod(sketch, "clear_son");
        LinkedList::LinkedList<std::tuple<std::shared_ptr<BST::BST<MT>::Content>, int, int, int, int>> l;
        l.append(std::make_tuple(B._root, -1, -1, -1, -1));
        int dep = 100;
        while (!l.empty())
        {
            auto [cur, curx, cury, px, py] = l.pop();
            //            qDebug() << curx << cury << px << py;
            QString outputstr;
            auto &[i, j, k] = *cur;
            if (i == 'I')
                outputstr.append(j.toDecimal().c_str());
            else if (i == 'F')
                outputstr.append(QString::number(k, 10, 8));
            else
                outputstr.append(i);
            if (px == -1)
            {
                px = curx = 800;
                py = cury = 80;
                qDebug() << "SEND:VERTEX:" << px << py << outputstr;
                QMetaObject::invokeMethod(sketch, "add_son", Q_ARG(QVariant, px), Q_ARG(QVariant, py), Q_ARG(QVariant, outputstr));
            }
            else
            {
                qDebug() << "SEND:VERTEX:" << curx << cury << outputstr;
                QMetaObject::invokeMethod(sketch, "add_son", Q_ARG(QVariant, curx), Q_ARG(QVariant, cury), Q_ARG(QVariant, outputstr));
                qDebug() << "SEND:EDGE:" << curx << cury << px << py;
                QMetaObject::invokeMethod(sketch, "add_edge", Q_ARG(QVariant, curx), Q_ARG(QVariant, cury), Q_ARG(QVariant, px), Q_ARG(QVariant, py));
            }

            if (cur->lchild)
                l.append(std::make_tuple(cur->lchild, curx - 100 * 500 / (cury + 180), cury + dep, curx, cury));
            if (cur->rchild)
                l.append(std::make_tuple(cur->rchild, curx + 100 * 500 / (cury + 180), cury + dep, curx, cury));
        }
        qDebug() << "DONE";
        //                std::cout << (*a).ii << '\t' << (*a).sbc << std::endl;
    }
    catch (std::exception &e)
    {
        qDebug() << e.what();
    }

    //Q_INVOKABLE void add_rule(QVariant ad); //传列表用QVariantList，键值对用QVariantMap

private:
    QString _operators = "+-*/%()";
    QString _symbols = ".eE";
    //    OrderedList::OrderedList<int> _operator_priority{50,50,70,70,70,1,100};
    std::map<char, int> _operator_priority = {
        {'+', 50},
        {'-', 50},
        {'*', 70},
        {'/', 70},
        {'%', 70},
        {'(', 1},
        {')', 100}};
    QString _query_expression;
    QObject *_obj;
};

#endif // QDATAMGR_H \
            //3*(114+514)/1919.810
