#include "Logger.h"
#include <bits/stdc++.h>
#include <bits/extc++.h>
// const int f() { return 1; }

// int ff(int &&a){return a=233;}

// signed main()
// {
//     // const std::string s("4589641");
//     using namespace Logger;
//     int ss = 44;
//     notePrint(ss);
//     ff(ss);
//     notePrint(ss);
//     // Logger::notePrint("Yarimasune", std::string("fda"), 114, 2333);
//     // Logger::notePrint(231);
//     // Logger::notePrint(std::string("fda"));
//     // Logger::notePrint(f());
//     return 0;
// }

using namespace std;
class A
{
public:
    A(int n) : num(n) { Out(); }
    A(const A &rhs) : num(rhs.num) { Out(); }
    void Out() { cout << num << endl; }

public:
    int num;
};

class B : public A
{
public:
    B(A &a) : obj(a), A(1) {}
    void Out() { obj.Out(); }

private:
    A obj;
};
signed main()
{
    A a(8);
    B b1(a);
    B b2(b1);
    b2.Out();
    return 0;
}