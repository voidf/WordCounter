#include <bits/stdc++.h>
using namespace std;
#define elif else if
#define M 1919810
#define endl '\n'
typedef long long LL;
typedef unsigned long long ULL;

constexpr ULL bh(const char *str, ULL h = 0)
{
    return !str[h] ? 5381 : (bh(str, h + 1) * 33) ^ str[h];
}

class node
{
public:
    LL val;
    node *nxt, *prv;
    node()
    {
        cout << "[Info] New node at " << this << '\n';
        nxt = NULL;
        prv = NULL;
    }
    ~node()
    {
        cout << "[Info] Deleted value:" << val << '\n';
    }
};

class MutableList //由于单向链表就是双向的阉割版，这里直接写双向了
{
public:
    LL __len__;
    node *__first__, *__last__;

    MutableList()
    {
        cout << "[Info] MutableList initializing...\n";
        __len__ = 0;
        __first__ = new node;
        __last__ = __first__;
    }
    void append(LL v)
    {
        __last__->nxt = new node;
        __last__->nxt->prv = __last__;
        __last__ = __last__->nxt;
        __last__->val = v;
        __len__++;
    }
    void pushHead(LL v)
    {
        __first__->prv = new node;
        __first__->prv->nxt = __first__;
        __first__->val = v;
        __first__ = __first__->prv; // first存入的节点本身无效
        __len__++;
    }
    void insert(LL p, LL v)
    {
        if (p == __len__)
            append(v); //懒得特判了走append吧
        elif (p > __len__ || -p > __len__)
                cerr
            << "[ERROR] List index out of range\n";
        else
        {
            node *cur;
            if (p >= 0)
            {
                p++;
                cur = __first__;
                while (p--)
                    cur = cur->nxt;
            }
            else
            {
                p++;
                cur = __last__;
                while (p++)
                    cur = cur->prv;
            }
            node *tmp = cur->prv;
            tmp->nxt = new node;
            tmp->nxt->prv = tmp;
            tmp = tmp->nxt;
            tmp->val = v;
            tmp->nxt = cur;
            cur->prv = tmp;
            __len__++;
        }
    }
    void discard(LL p)
    {
        if (p >= __len__ || -p > __len__)
            cerr << "[ERROR] List index out of range\n";
        else
        {
            node *cur;
            if (p >= 0)
            {
                p++;
                cur = __first__;
                while (p--)
                    cur = cur->nxt;
            }
            else
            {
                p++;
                cur = __last__;
                while (p++)
                    cur = cur->prv;
            }
            cur->prv->nxt = cur->nxt;
            if (cur == __last__)
                __last__ = __last__->prv;
            else
                cur->nxt->prv = cur->prv;
            delete cur;
            __len__--;
        }
    }
    void show()
    {
        cout << "[";
        node *cur = __first__->nxt;

        for (LL tmp = 0; tmp < __len__; tmp += 1, cur = cur->nxt)
        {
            if (tmp)
            {
                cout << ", " << cur->val;
            }
            else
            {
                cout << cur->val;
            }
        }
        cout << "]\n";
    }
    void concate(MutableList &a)
    {
        node *cur = a.__first__->nxt;
        for (LL tmp = 0; tmp < a.__len__; tmp += 1, cur = cur->nxt)
            this->append(cur->val);
    }
    friend MutableList operator+(MutableList &a, MutableList &b)
    {
        MutableList c;
        node *cur = a.__first__->nxt;

        for (LL tmp = 0; tmp < a.__len__; tmp += 1, cur = cur->nxt)
            c.append(cur->val);
        cur = b.__first__->nxt;
        for (LL tmp = 0; tmp < b.__len__; tmp += 1, cur = cur->nxt)
            c.append(cur->val);
        return c;
    }
};
char s[M];
int main()
{
    LL p, v;
    try
    {
        unordered_set<LL> S;
        //线性表操作
        cout << "[Info] Linear list demonstrate started...\n";
        cout << "Input the length you need>>>";
        LL le;
        cin >> le;
        LL *ll = new LL[le];
        cout << "[Info] Linear list allocate done...\n";
        bool Tag = true;
        while (Tag)
        {
            cin >> s;
            switch (bh(s))
            {
            case bh("quit"):
                Tag = false;
                delete ll;
                break;
            case bh("insert"):

                cout << "insert>>>";
                cin >> p >> v;
                if (p >= le)
                {
                    cout << "[ERROR] List index out of range\n";
                    break;
                }
                ll[p] = v;
                S.insert(p);
                break;
            case bh("discard"):
                cout << "discard>>>";
                cin >> p;
                if (p >= le)
                {
                    cout << "[ERROR] List index out of range\n";
                    break;
                }
                S.erase(p);
                break;
            case bh("show"):
                cout << '[';
                for (auto i : S)
                {
                    cout << ll[i] << ", ";
                }
                cout << "]\n";
                break;
            case bh("get"):
                cout << "get>>>";
                cin >> p;
                if (p >= le)
                {
                    cout << "[ERROR] List index out of range\n";
                    break;
                }
                if (S.find(p) != S.end())
                    cout << ll[p] << '\n';
                else
                    cout << "[ERROR] Key error:" << p << "\n";
                break;
            default:
                cout << "[WARN] Unknown command, current length:" << S.size() << '\n';
                cout << "Available Commands:\n";
                cout << "\tinsert\n";
                cout << "\tget\n";
                cout << "\tdiscard\n";
                cout << "\tshow\n";
                cout << "Type 'quit' to go to next test.\n";
            }
        }
        //链表操作
        MutableList l;
        Tag = true;
        cout << "[Info] MutableList demonstrate started...\n";
        while (Tag)
        {
            cin>>s;
            switch (bh(s))
            {
            case bh("quit"):
                Tag = false;
                break;
            case bh("insert"):
                cout << "insert>>>";
                cin >> p >> v;
                l.insert(p, v);
                break;
            case bh("pushHead"):
                cout << "pushHead>>>";
                cin >> v;
                l.pushHead(v);
                break;
            case bh("append"):
                cout << "append>>>";
                cin >> v;
                l.append(v);
                break;
            case bh("discard"):
                cout << "discard>>>";
                cin >> p;
                l.discard(p);
                break;
            case bh("show"):
                l.show();
                break;
            default:
                cout << "[WARN] Unknown command, current length:" << l.__len__ << '\n';
                cout << "Available Commands:\n";
                cout << "\tinsert\n";
                cout << "\tpushHead\n";
                cout << "\tappend\n";
                cout << "\tdiscard\n";
                cout << "\tshow\n";
                cout << "Type 'quit' to go to next test.\n";
            }
        }
        MutableList L;
        Tag = true;
        cout << "[Info] MutableList merge demonstrate started...\n";
        cout << "Use command to modify current list\n";
        cout << "Type quit then you can see the merged one in two ways\n";
        while (Tag)
        {
            cin>>s;
            switch (bh(s))
            {
            case bh("quit"):
                Tag = false;
                break;
            case bh("insert"):
                cout << "insert>>>";
                cin >> p >> v;
                L.insert(p, v);
                break;
            case bh("pushHead"):
                cout << "pushHead>>>";
                cin >> v;
                L.pushHead(v);
                break;
            case bh("append"):
                cout << "append>>>";
                cin >> v;
                L.append(v);
                break;
            case bh("discard"):
                cout << "discard>>>";
                cin >> p;
                L.discard(p);
                break;
            case bh("show"):
                L.show();
                break;
            default:
                cout << "[WARN] Unknown command, current length:" << L.__len__ << '\n';
                cout << "Available Commands:\n";
                cout << "\tinsert\n";
                cout << "\tpushHead\n";
                cout << "\tappend\n";
                cout << "\tdiscard\n";
                cout << "\tshow\n";
                cout << "Type 'quit' to go to next test.\n";
            }
        }
        MutableList m = l+L;
        cout << "[Info] MutableList merge by creating a new one\n";
        m.show();
        cout << "[Info] MutableList merge by modify the first one\n";
        l.concate(L);
        l.show();
    }
    catch (const exception &e)
    {
        cerr << "[FATAL] " << e.what() << '\n';
        cerr << "很难修的\n";
    }

    return 0;
}