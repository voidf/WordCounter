#include "Logger.h"
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
bitset<10> b1(3);
bitset<20> b2;
signed main()
try
{
    for (auto i : b2)
        cout << i;
    cout << endl;
    return 0;
}
catch (exception &e)
{
    cerr << e.what() << endl;
    return 1;
}