#include <bits/stdc++.h>
#include <bits/extc++.h>
#include "BigInteger.h"
using namespace std;
string s;

struct _base
{
    char _type;
    _base(char t) : _type(t) {}
    virtual ~_base() = default;
};

template <typename T>
struct _wrapper : _base
{
    T _content;
    _wrapper(char _t, T _c) : _base(_t), _content(_c) {}
};

signed main()
try
{
    std::unique_ptr<_base> p(new _wrapper<double>('d', 1.10));
    std::cout << dynamic_cast<_wrapper<double>*>(p.get())->_content;
}
catch (exception &e)
{
    cerr << e.what() << endl;
    return 1;
}