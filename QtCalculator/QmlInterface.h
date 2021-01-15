#define IMPORT_MODULE
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

struct __Base
{
    char _type;
    __Base(char t) : _type(t) {}
    virtual ~__Base() = default;
};

template <typename T>
struct _wrapper : __Base
{
    T _content;
    _wrapper(char _t) : __Base(_t){}
    _wrapper(char _t, T &_c) : __Base(_t), _content(_c) {}
    _wrapper(char _t, T &&_c) : __Base(_t), _content(_c) {}
};


using I256 = BigIntegerDomain::BigInteger<256>;
using VPtr = std::shared_ptr<__Base>;
#define vector OrderedList::OrderedList // 所以还是用自己的
#define list LinkedList::LinkedList
#define getI(a) dynamic_cast<_wrapper<I256>*>(a.get())->_content
#define getF(a) dynamic_cast<_wrapper<double>*>(a.get())->_content
#define I2str(a) dynamic_cast<_wrapper<I256>*>(a.get())->_content.toDecimal().c_str() // 参数是VPtr
#define F2str(a) QString::number(dynamic_cast<_wrapper<double>*>(a.get())->_content,10,8)


//struct MT
//{
//    char a;
//    BigIntegerDomain::BigInteger<256> b;
//    double c;
//    //    MT(const char _a,BigIntegerDomain::BigInteger<256> &_b, double _c):a(_a),b(_b),c(_c){}
//    MT(char _a, BigIntegerDomain::BigInteger<256> &_b, double _c) : a(_a), b(_b), c(_c) {}
//    MT(char &&_a, BigIntegerDomain::BigInteger<256> &&_b, double _c) : a(_a), b(_b), c(_c) {}
//    MT() : a(0), b(0), c(0) {}
//};

extern QObject *rootobj;
class QmlInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString _query_expression READ rfurl WRITE wfurl)

public:
    explicit QmlInterface(QObject *parent = nullptr) : QObject(parent) {}
    QString rfurl() const { return _query_expression; }
    void wfurl(QString s) { _query_expression = s; }
    void echo_wrapper(VPtr &_p)
    {
        if (_p->_type == 'I')
            qDebug()<<dynamic_cast<_wrapper<I256>*>(_p.get())->_content.toDecimal().c_str();
    //        qDebug()<<I2str(_p);
        else if(_p->_type == 'F')
            qDebug()<<dynamic_cast<_wrapper<double>*>(_p.get())->_content;
    //        qDebug()<<F2str(_p);
        else
            qDebug()<<_p->_type;
    }


public:
    Q_INVOKABLE void handle_exp(QVariant q)
    try
    {
        QString s = q.toString().simplified()
                .replace(QString("（"),QString("("))
                .replace(QString("）"),QString(")"))
                .replace(QString(" "),QString(""));
        auto minus_tag = false;
        auto float_tag = false;
        vector<VPtr> suffix_exp;
        vector<VPtr> _calc_stack;
        vector<char> operators;
        BST::BST<VPtr> B;

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
                            suffix_exp.append(VPtr(new _wrapper<double>('F', cur)));
//                            suffix_exp.direct_append('F', BigIntegerDomain::BigInteger<256>(), cur);
                        }
                        else
                        {
                            I256 cur;
                            cur.fromDecimal(handler);
                            qDebug() << cur.toDecimal().c_str();
                            if (minus_tag)
                                cur = -cur;
                            suffix_exp.append(VPtr(new _wrapper<I256>('I',cur)));
//                            suffix_exp.direct_append('I', cur, 0.0);
                        }
                        float_tag = minus_tag = false;
                        handler.clear();
                    }

                    if (i == ')')
                    {
                        while (!operators.empty() and operators.back() != '(')
                        {
                            suffix_exp.append(VPtr(new _wrapper<char>(operators.pop())));
//                            suffix_exp.direct_append(operators.pop(), BigIntegerDomain::BigInteger<256>(), 0.0);
                        }
                        if (operators.empty())
                        {
                            QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant(
                                "【运行错误】操作符栈为空但正要弹栈"
                                "请检查表达式"
                            )));
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
                            suffix_exp.append(VPtr(new _wrapper<char>(operators.pop())));
//                            suffix_exp.direct_append(operators.pop(), BigIntegerDomain::BigInteger<256>(), 0.0);
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
//                suffix_exp.direct_append('F', BigIntegerDomain::BigInteger<256>(), cur);
                suffix_exp.append(VPtr(new _wrapper<double>('F', cur)));

            }
            else
            {
                I256 cur;
                cur.fromDecimal(handler);
                if (minus_tag)
                    cur = -cur;
                suffix_exp.append(VPtr(new _wrapper<I256>('I',cur)));
//                suffix_exp.direct_append('I', cur, 0.0);
            }
            float_tag = minus_tag = false;
            handler.clear();
        }
        while (!operators.empty())
            suffix_exp.append(VPtr(new _wrapper<char>(operators.pop())));
//            suffix_exp.direct_append(operators.pop(), BigIntegerDomain::BigInteger<256>(), 0.0);

        vector<std::shared_ptr<BST::BST<VPtr>::Content>> _pointer_stack;
        for (auto &i : suffix_exp)
        {
            if (i->_type == 'I' or i->_type == 'F')
            {
                //                _calc_stack.direct_append(i, j, k);
//                auto tpp = B.direct_generate_content(i, j, k);
                auto tpp = B.generate_content(i);
                _pointer_stack.append(tpp);
            }
            else
            {

//                auto parent = B.direct_generate_content(i, j, k);
                auto parent = B.generate_content(i);

                if (_pointer_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant(
                        "【运行错误】_pointer_stack为空但正要弹栈(B)"
                        "你是不是往表达式里塞了一堆运算符？"
                    )));
                    return;
                }
                auto oprb = _pointer_stack.pop();
                if (_pointer_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant(
                        "【运行错误】_pointer_stack为空但正要弹栈(A)"
                        "你是不是往表达式里塞了一堆运算符？"
                    )));
                    return;
                }
                auto opra = _pointer_stack.pop();
                B.lconnect(parent, opra);
                B.rconnect(parent, oprb);
                _pointer_stack.append(parent);
            }
        }
        if (_pointer_stack.empty())
        {
            QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant(
                "【运行错误】_pointer_stack为空但正要弹栈(tpp)"
                "你是不是往表达式里塞了一堆运算符？"
            )));
        }
        auto tpp = _pointer_stack.pop();
        B.lconnect(B._header, tpp);
        B.update_beginnings();
        for (auto &i : suffix_exp)
        {
//            qDebug() << i << " " << j.toDecimal().c_str() << " " << k;
            qDebug("from 249");
            echo_wrapper(i);
            if (i->_type == 'I' or i->_type == 'F')
                _calc_stack.append(i);
//                _calc_stack.direct_append(i, j, k);
            else
            {
                if (_calc_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant(
                        "【运行错误】_calc_stack为空但正要弹栈(259)"
                        "你是不是往表达式里塞什么不可计算的东西？"
                    )));
                    return;
                }
                auto oprb = _calc_stack.pop();
                if (_calc_stack.empty())
                {
                    QMetaObject::invokeMethod(calc_result, "warning", Q_ARG(QVariant, QVariant(
                        "【运行错误】_calc_stack为空但正要弹栈(268)"
                        "你是不是往表达式里塞什么不可计算的东西？"
                    )));
                    return;
                }
                auto opra = _calc_stack.pop();
                if (opra->_type == 'F' or oprb->_type == 'F')
                {
                    double __a = (
                        opra->_type=='F'?
                        dynamic_cast<_wrapper<double>*>(opra.get())->_content:
                        dynamic_cast<_wrapper<I256>*>(opra.get())->_content.toDouble()
                    ),     __b = (
                        oprb->_type=='F'?
                        dynamic_cast<_wrapper<double>*>(oprb.get())->_content:
                        dynamic_cast<_wrapper<I256>*>(oprb.get())->_content.toDouble()
                    );
//                    if (opra.a == 'F' and oprb.a == 'F')
//                        __a = opra.c, __b = oprb.c;
//                    else if (opra.a == 'F' and oprb.a == 'I')
//                        __a = opra.c, __b = oprb.b.toDouble();
//                    else if (opra.a == 'I' and oprb.a == 'F')
//                        __a = opra.b.toDouble(), __b = oprb.c;
//                    else
//                        __a = opra.b.toDouble(), __b = oprb.b.toDouble();
                    double __res;
                    switch (i->_type)
                    {
                    case '+':
//                        _calc_stack.direct_append('F', j, __a + __b);
                        __res = __a + __b;
                        break;
                    case '-':
//                        _calc_stack.direct_append('F', j, __a - __b);
                        __res = __a - __b;
                        break;
                    case '*':
//                        _calc_stack.direct_append('F', j, __a * __b);
                        __res = __a * __b;
                        break;
                    case '/':
//                        _calc_stack.direct_append('F', j, __a / __b);
                        __res = __a / __b;
                        break;
                    default:
                        break;
                    }
                    _calc_stack.append(VPtr(new _wrapper<double>('F',__res)));
                }
                else
                {
//                    qDebug() << opra.b.toDecimal().c_str() << oprb.b.toDecimal().c_str();
                    qDebug("from 320");
                    echo_wrapper(opra);
                    echo_wrapper(oprb);
                    switch (i->_type)
                    {
                    case '+':
                        _calc_stack.append(VPtr(new _wrapper<I256>('I', dynamic_cast<_wrapper<I256>*>(opra.get())->_content + dynamic_cast<_wrapper<I256>*>(oprb.get())->_content)));
                        break;
                    case '-':
                        _calc_stack.append(VPtr(new _wrapper<I256>('I', dynamic_cast<_wrapper<I256>*>(opra.get())->_content - dynamic_cast<_wrapper<I256>*>(oprb.get())->_content)));
                        break;
                    case '*':
                        _calc_stack.append(VPtr(new _wrapper<I256>('I', dynamic_cast<_wrapper<I256>*>(opra.get())->_content * dynamic_cast<_wrapper<I256>*>(oprb.get())->_content)));
                        break;
                    case '/':
                        _calc_stack.append(VPtr(new _wrapper<I256>('I', dynamic_cast<_wrapper<I256>*>(opra.get())->_content / dynamic_cast<_wrapper<I256>*>(oprb.get())->_content)));
                        break;
                    case '%':
                        _calc_stack.append(VPtr(new _wrapper<I256>('I', dynamic_cast<_wrapper<I256>*>(opra.get())->_content % dynamic_cast<_wrapper<I256>*>(oprb.get())->_content)));
                        break;
                    default:
                        break;
                    }
                }
            }
            qDebug("from 345");
            echo_wrapper(i);
        }
        //        qDebug() << "======";
        QString res;
        if (_calc_stack.back()->_type == 'I')
            res.append(I2str(_calc_stack.back()));
        else
            res = F2str(_calc_stack.back());
//            res = QString::number(_calc_stack.back().c, 10, 8);

        QObject *view_area = rootobj->findChild<QObject *>("input_window");
        qDebug() << res;
        QVariant fst(res);
        QMetaObject::invokeMethod(view_area, "set_res", Q_ARG(QVariant, fst));
        QString a1, a2, a3;
        for (auto &i : B)
        {
            //            qDebug() << i << " " << j.toDecimal().c_str() << " " << k;
            if (i->_type == 'I')
                a1.append(I2str(i));
//                a1.append(j.toDecimal().c_str());
            else if (i->_type == 'F')
                a1.append(F2str(i));
            else
                a1.append(i->_type);
            a1.append(' ');
        }
        for (auto a = B.preotbegin(); a != B.end(); B.preotmove(a))
        {
            auto &i = *a;
            if (i->_type == 'I')
                a2.append(I2str(i));
            else if (i->_type == 'F')
                a2.append(F2str(i));
            else
                a2.append(i->_type);
            a2.append(' ');
        }
        for (auto a = B.postotbegin(); a != B.end(); B.postotmove(a))
        {
            auto &i = *a;
            if (i->_type == 'I')
                a3.append(I2str(i));
            else if (i->_type == 'F')
                a3.append(F2str(i));
            else
                a3.append(i->_type);
            a3.append(' ');
        }

        QMetaObject::invokeMethod(calc_result, "set_res", Q_ARG(QVariant, a1), Q_ARG(QVariant, a2), Q_ARG(QVariant, a3));
        QObject *sketch = rootobj->findChild<QObject *>("sketch");
        QMetaObject::invokeMethod(sketch, "clear_son");
        list<std::tuple<std::shared_ptr<BST::BST<VPtr>::Content>, int, int, int, int>> l;
        l.append(std::make_tuple(B._root, -1, -1, -1, -1));
        int dep = 100;
        while (!l.empty())
        {
            auto [cur, curx, cury, px, py] = l.pop();
            //            qDebug() << curx << cury << px << py;
            QString outputstr;
            auto &i = *cur;
            if (i->_type == 'I')
                outputstr.append(I2str(i));
            else if (i->_type == 'F')
                outputstr.append(F2str(i));
            else
                outputstr.append(i->_type);
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
