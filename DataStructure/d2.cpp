#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define cls(a) memset(a, 0, sizeof(a))
#define elif else if
#define M 1919810
#define endl '\n'
typedef long long LL;
typedef unsigned long long ULL;

vector<LL> father;
vector<LL> degree;
vector<LL> longest;
vector<LL> shortest;
LL _len;
LL f, t, w;

vector<LL> route;
vector<tuple<LL, LL, LL>> E;
vector<vector<pair<LL, LL>>> vec;
vector<vector<pair<LL, LL>>> cev;
struct edgeCMP
{
    bool operator()(pair<LL, LL> &a, pair<LL, LL> &b)
    {
        return a.second > b.second;
    }
};
priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, edgeCMP> P;
priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, edgeCMP> DP;
queue<LL> Q;

unordered_set<LL> vis, S;

//DEBUG用函数
class info
{
public:
    template <typename FIRST, typename... PACK>
    static void print(FIRST first, PACK... params)
    {
        cout << first;
        print(params...);
    }

    //重载函数版本，递归结束条件
    template <typename T>
    static void print(T end)
    {
        cout << end << endl;
    }
};

template <typename... Motto>
void infoPrint(Motto... a) //RGB format
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //Midori
    cout << "[Info] ";
    info::print(a...);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //Shiro
}
template <typename... Motto>
void notePrint(Motto... a)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //Ao
    cout << "[NOTE] ";
    info::print(a...);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
template <typename... Motto>
void warnPrint(Motto... a)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //Ki
    cout << "[WARN] ";
    info::print(a...);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
template <typename... Motto>
void debugPrint(Motto... a)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "[Debug] ";
    info::print(a...);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
template <typename... Motto>
void errorPrint(Motto... a)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //Aka
    cout << "[ERROR] ";
    info::print(a...);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
template <typename... Motto>
void fatalPrint(Motto... a)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); //Murasaki
    cout << "[FATAL] ";
    info::print(a...);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//DEBUG用函数完

//节点离散化用
unordered_map<LL, LL> _name;
unordered_map<LL, LL> _eman;
LL Discretization(LL x)
{
    if (_name.find(x) == _name.end())
    {
        infoPrint("New node ", x," marked as #",_name.size());
        _name.insert(make_pair(x, _name.size()));
        _eman.insert(make_pair(_eman.size(), x));
    }
    return _name[x];
}

//离散化完毕
LL find(LL cur)
{
    if (father[cur] != cur)
        father[cur] = find(father[cur]);
    return father[cur];
}

bool cmp(const tuple<LL, LL, LL> &a, const tuple<LL, LL, LL> &b)
{
    return get<2>(a) < get<2>(b);
}

void dfs(LL cur)
{
    cout << ' ' << _eman[cur] << ',';
    vis.insert(cur);
    for (auto i : vec[cur])
        if (vis.find(i.first) == vis.end())
            dfs(i.first);
    for (auto i : cev[cur])
        if (vis.find(i.first) == vis.end())
            dfs(i.first);
}

void DFS(LL cur)
{
    vector<LL> callstack;
    callstack.push_back(cur);
    while (callstack.size())
    {
        LL c = callstack.back();
        callstack.pop_back();
        if (vis.find(c) == vis.end())
        {
            cout << ' ' << _eman[c] << ' ';
            vis.insert(c);
            
            for (auto i : vec[c])
                if (vis.find(i.first) == vis.end())
                    callstack.push_back(i.first);
            for (auto i : cev[c])
                if (vis.find(i.first) == vis.end())
                    callstack.push_back(i.first);
        }
    }
}
string confirm;
int main()
{
    try
    {
        infoPrint("Initializing graph edges...");
        notePrint("Each edge you input will be handled as UNDIRECTED EDGE in dfs and MST demonstration, but as DIRECTED EDGE in toposort.");
        notePrint("Type -1 to go to next test");
        while (1)
        {
            cout << "Input the edge format as 'from to weight'>>>";
            cin >> f;
            if (f == -1)
            {
                notePrint("Current node count:", _name.size(), ", go to next test?(Y/n)");
                cin >> confirm;
                if (confirm != "n" && confirm != "N")
                    break;
                else
                    continue;
            }
            else
            {
                cin >> t >> w;
                f = Discretization(f);
                t = Discretization(t);
                E.push_back(make_tuple(f, t, w));
                cout << _eman[f] << "<====(" << w << ")====>" << _eman[t] << "\n";
            }
        }

        _len = _name.size();
        vec.assign(_len, vector<pair<LL, LL>>());
        cev.assign(_len, vector<pair<LL, LL>>());
        route.assign(_len, -1);
        // auto degree = new LL[_len];
        // auto longest = new LL[_len];
        // auto shortest = new LL[_len];
        
        // cls(degree);
        // cls(longest);
        // memset(shortest, 0x3f, sizeof(shortest));
        degree.assign(_len,0);
        longest.assign(_len,0);
        shortest.assign(_len,0x3f3f3f3f3f3f3f3f);
        for (auto i = 0; i < _len; i++)
            father.push_back(i);

        for (auto i : E)
        {
            tie(f, t, w) = i;
            vec[f].push_back(make_pair(t, w));
            cev[t].push_back(make_pair(f, w));
            degree[t]++;
        }
        infoPrint("dfs started...");
        dfs(0);
        puts("");
        infoPrint("DFS (recursive NG) started...");
        vis.clear();
        DFS(0);
        puts("");

        infoPrint("MST demonstration started...");
        infoPrint("Kruskal started...");
        auto startTime = clock();
        sort(E.begin(), E.end(), cmp);
        LL ans = 0;
        for (auto i : E)
        {
            tie(f, t, w) = i;
            LL tf = find(f);
            LL tt = find(t);
            if (tf != tt)
            {
                father[tf] = father[tt];
                ans += w;
                printf("[Algo] Selected edge:%lld<-(%lld)->%lld\n", _eman[f], w, _eman[t]);
            }
        }
        infoPrint("Total cost:", ans);
        debugPrint("CPU Time used:", clock() - startTime);
        infoPrint("Prim started...");
        startTime = clock();
        ans = 0;
        S.insert(0);
        for (auto i : vec[0])
            P.push(i);
        for (auto i : cev[0])
            P.push(i);
        while (P.size() && S.size() < _len)
        {
            auto tmp = P.top();
            P.pop();
            if (S.find(tmp.first) == S.end())
            {
                S.insert(tmp.first);
                ans += tmp.second;
                printf("[Algo] Added node:%lld,cost:%lld\n", _eman[tmp.first], tmp.second);
                for (auto i : vec[tmp.first])
                    P.push(i);
                for (auto i : cev[tmp.first])
                    P.push(i);
            }
        }
        infoPrint("Total cost:", ans);
        debugPrint("CPU Time used:", clock() - startTime);
        infoPrint("DAG DP started..."); // 这个版本的还不能处理环
        ans = 0;
        startTime = clock();
        for (LL t = 0; t < _len; t++)
            if (degree[t] == 0)
                Q.push(t);
        LL longestBegin;
        while (Q.size())
        {
            auto tmp = Q.front();
            Q.pop();
            for (auto i : vec[tmp])
            {
                if (--degree[i.first] == 0)
                    Q.push(i.first);
                if (longest[i.first] < longest[tmp] + i.second)
                {
                    longest[i.first] = longest[tmp] + i.second;
                    ans = longest[i.first];
                    longestBegin = i.first;
                    route[i.first] = tmp;
                }
            }
        }
        infoPrint("Longest path cost:", ans);
        for (auto i = longestBegin; ~i; i = route[i])
            cout << _eman[i] << "<==";
        puts("Start");
        debugPrint("CPU Time used:", clock() - startTime);
        infoPrint("Dijkstra started...");
        cout << "Input the starting point and the distination>>>";
        cin >> f >> t;
        f = _name[f];
        t = _name[t];

        //infoPrint("Assumed begins at first node and ends at final node");
        startTime = clock();
        S.clear();

        shortest[f] = 0;

        DP.push(make_pair(f, 0));
        while (DP.size() && S.find(t) == S.end())
        {
            auto tmp = DP.top();
            DP.pop();
            if (S.find(tmp.first) == S.end())
            {
                S.insert(tmp.first);
                for (auto i : vec[tmp.first])
                    if (shortest[tmp.first] + i.second < shortest[i.first])
                    {
                        shortest[i.first] = shortest[tmp.first] + i.second;
                        DP.push(make_pair(i.first, shortest[i.first]));
                    }
            }
        }
        infoPrint("Shortest path cost:", shortest[t]);
        debugPrint("CPU Time used:", clock() - startTime);
        infoPrint("Demonstration ended...");
    }
    catch (const exception &e)
    {
        fatalPrint(e.what());
    }
    return 0;
}