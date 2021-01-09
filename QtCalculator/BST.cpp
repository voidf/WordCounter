#define IMPORT_MODULE
#ifndef BST_IMPORTED
#define BST_IMPORTED
#include <memory>
#include <new.h>
// #include <vector>
// #include <bits/stdc++.h>
namespace BST
{
    class IndexErrorException : public std::exception
    {
    public:
        IndexErrorException(const char *what, void *where) : m_what(what), m_where(where) {}
        IndexErrorException(const char *what) : m_what(what) {}

        virtual const char *what() const throw() { return m_what; }

        template <class Ch>
        Ch *where() const
        {
            return reinterpret_cast<Ch *>(m_where);
        }

    private:
        const char *m_what;
        void *m_where;
    };

    template <typename T>
    struct BST
    {
        struct Content
        {
            typedef std::shared_ptr<Content> P;
            P father, lchild, rchild;
            T value;

            Content(){};
            Content(T &v) : value(v) {}
            template <typename... Args>
            Content(Args &&... args) : value(std::forward<Args>(args)...) {}
        };
        typedef std::shared_ptr<Content> P;
        P _l, _header, _r, _root;
        size_t _len;

        P begin() { return _l; }
        P end() { return _header; }
        P postotbegin()
        {
            P ptr = this->_l;
            while (true)
            {
                while (ptr->lchild)
                    ptr = ptr->lchild;
                if (ptr->rchild)
                    ptr = ptr->rchild;
                if (!ptr->lchild and !ptr->rchild)
                    break;
            }
            return ptr;
        }
        void postotmove(P &ptr)
        {
            // bool flg = true;
            if (ptr->father == this->_header)
                ptr = this->_header;
            else if (ptr->father->rchild == ptr)
                ptr = ptr->father;
            else if (ptr->father->lchild == ptr)
            {
                ptr = ptr->father;
                if (ptr->rchild)
                {
                    ptr = ptr->rchild;
                    while (true)
                    {
                        while (ptr->lchild)
                            ptr = ptr->lchild;
                        if (ptr->rchild)
                            ptr = ptr->rchild;
                        if (!ptr->lchild and !ptr->rchild)
                            break;
                    }
                }
            }
        }
        P preotbegin() { return _root; } // 先序遍历起点在根
        void preotmove(P &ptr)
        {
            if (ptr->lchild)
                ptr = ptr->lchild;
            else if (ptr->rchild)
                ptr = ptr->rchild;
            else
            {
                bool flg = true;
                while (flg)
                {
                    while (ptr->father and ptr->father->rchild == ptr)
                        ptr = ptr->father;
                    ptr = ptr->father;
                    while (ptr->father and ptr == ptr->father->lchild)
                    {
                        if (ptr->rchild)
                        {
                            ptr = ptr->rchild;
                            flg = false;
                            break;
                        }
                        ptr = ptr->father;
                    }
                    if (ptr == _header) // 走到end，终点退出
                        break;
                }
            }
        }
        T &front() { return _l->value; }
        T &back() { return _header->prev->value; }

        size_t size() { return this->_len; }
        bool empty() { return this->_len == 0; }
        BST() : _len(0)
        {
            _l = static_cast<P>(new Content());
            _root = _r = _header = _l;
            // _l->lchild = _l;
            // _l->rchild = _l;
        }
        // ~BST()
        // {
        //     std::vector<P> remove_list;
        //     remove_list.clear();
        //     for (auto cur = this->_l; cur != this->_header; cur++)
        //         remove_list.emplace_back(cur);
        //     for (auto i : remove_list)
        //         i.reset();
        //     this->_header.reset();
        //     delete this;
        // }

        friend P operator++(P &ptr, int)
        {
            P ret = ptr;
            if (ptr->rchild)
            {
                ptr = ptr->rchild;
                while (ptr->lchild)
                    ptr = ptr->lchild;
            }
            else
            {
                P y = ptr->father;
                while (ptr == y->rchild)
                {
                    ptr = y;
                    y = ptr->father;
                }
                if (ptr->rchild != y)
                    ptr = y;
            }
            return ret;
        }

        friend P &operator++(P &ptr)
        {
            if (ptr->rchild)
            {
                ptr = ptr->rchild;
                while (ptr->lchild)
                    ptr = ptr->lchild;
            }
            else
            {
                P y = ptr->father;
                while (ptr == y->rchild)
                {
                    ptr = y;
                    y = ptr->father;
                }
                if (ptr->rchild != y)
                    ptr = y;
            }
            return ptr;
        } // foreach用到这个
        friend P &operator++(P &&ptr)
        {
            if (ptr->rchild)
            {
                ptr = ptr->rchild;
                while (ptr->lchild)
                    ptr = ptr->lchild;
            }
            else
            {
                P y = ptr->father;
                while (ptr == y->rchild)
                {
                    ptr = y;
                    y = ptr->father;
                }
                if (ptr->rchild != y)
                    ptr = y;
            }
            return ptr;
        }

        friend P operator+(P ptr, size_t offset)
        {
            // static P tmp = ptr;
            while (offset > 0)
            {
                if (!(ptr))
                    throw IndexErrorException("IndexError: list index out of range");
                ++ptr;
                offset--;
            }
            return ptr;
        }
        friend T &operator*(P &ptr) { return ptr->value; }

        P insert_left(P &ptr, const T &x)
        {
            P tmp(new Content(x));
            tmp->lchild = ptr->lchild;
            if (ptr->lchild)
                ptr->lchild->father = tmp;
            ptr->lchild = tmp;
            tmp->father = ptr;
            if (ptr == this->_l)
            {
                this->_l = tmp;
            }
            if (this->_header == ptr)
            {
                // _header->father = tmp;
                _root = tmp;
            }
            this->_len++;
            return tmp;
        }
        P insert_right(P &ptr, const T &x)
        {
            P tmp(new Content(x));
            tmp->rchild = ptr->rchild;
            if (ptr->rchild)
                ptr->rchild->father = tmp;
            ptr->rchild = tmp;
            tmp->father = ptr;
            if (ptr == this->_r)
                this->_r = tmp;
            if (this->_header == ptr)
            {
                // _header->father = tmp;
                _root = tmp;
            }
            this->_len++;
            return tmp;
        }

        P insert_left(P &&ptr, T &&x) { return direct_insert_left(ptr, std::move(x)); }
        P insert_right(P &&ptr, T &&x) { return direct_insert_right(ptr, std::move(x)); }

        template <typename... Args>
        P direct_insert_left(P &&ptr, Args &&... args)
        {
            P tmp(new Content(std::forward<Args>(args)...));
            tmp->lchild = ptr->lchild;
            if (ptr->lchild)
                ptr->lchild->father = tmp;
            ptr->lchild = tmp;
            tmp->father = ptr;
            if (ptr == this->_l)
                this->_l = tmp;
            if (this->_header == ptr)
            {
                // _header->father = tmp;
                _root = tmp;
            }
            this->_len++;
            return tmp;
        }
        template <typename... Args>
        P direct_insert_right(P &&ptr, Args &&... args)
        {
            P tmp(new Content(std::forward<Args>(args)...));
            tmp->rchild = ptr->rchild;
            if (ptr->rchild)
                ptr->rchild->father = tmp;
            ptr->rchild = tmp;
            tmp->father = ptr;
            if (ptr == this->_r)
                this->_r = tmp;
            if (this->_header == ptr)
            {
                // _header->father = tmp;
                _root = tmp;
            }
            this->_len++;
            return tmp;
        }
        template <typename... Args>
        P direct_insert_left(P &ptr, Args &&... args)
        {
            P tmp(new Content(std::forward<Args>(args)...));
            tmp->lchild = ptr->lchild;
            if (ptr->lchild)
                ptr->lchild->father = tmp;
            ptr->lchild = tmp;
            tmp->father = ptr;
            if (ptr == this->_l)
                this->_l = tmp;
            if (this->_header == ptr)
            {
                // _header->father = tmp;
                _root = tmp;
            }
            this->_len++;
            return tmp;
        }
        template <typename... Args>
        P direct_insert_right(P &ptr, Args &&... args)
        {
            P tmp(new Content(std::forward<Args>(args)...));
            tmp->rchild = ptr->rchild;
            if (ptr->rchild)
                ptr->rchild->father = tmp;
            ptr->rchild = tmp;
            tmp->father = ptr;
            if (ptr == this->_r)
                this->_r = tmp;
            if (this->_header == ptr)
            {
                // _header->father = tmp;
                _root = tmp;
            }
            this->_len++;
            return tmp;
        }
    };

} // namespace BST
#endif
#ifndef IMPORT_MODULE
#include <iostream>

struct SB
{
    long long ii;
    int sbc;
    SB() {}
    SB(long long a, int b) : ii(a), sbc(b) {}
};

void dfspre(auto ptr) // 递归先序打印节点值
{
    auto [A, B] = *ptr;
    std::cout << A << '\t' << B << std::endl;
    if (ptr->lchild)
        dfspre(ptr->lchild);
    if (ptr->rchild)
        dfspre(ptr->rchild);
}
void dfsin(auto ptr) // 递归中序打印节点值
{
    auto [A, B] = *ptr;
    if (ptr->lchild)
        dfsin(ptr->lchild);
    std::cout << A << '\t' << B << std::endl;
    if (ptr->rchild)
        dfsin(ptr->rchild);
}
void dfspost(auto ptr) // 递归后序打印节点值
{
    auto [A, B] = *ptr;
    if (ptr->lchild)
        dfspost(ptr->lchild);
    if (ptr->rchild)
        dfspost(ptr->rchild);
    std::cout << A << '\t' << B << std::endl;
}

signed main()
try
{

    BST::BST<SB> ol;
    ol.direct_insert_left(ol.begin(), 11, 1);
    ol.direct_insert_left(ol.begin(), 22, 14);
    ol.direct_insert_left(ol.begin(), 33, 5);
    ol.direct_insert_left(ol.begin(), 44, 14);
    for (auto [i, j] : ol)
        std::cout << i << '\t' << j << std::endl;
    // while (!ol.empty())
    //     std::cout << ol.pop().sbc << std::endl;
    // ol.pop();
    //字符串前缀：R->所见即所得
    // U UTF-32
    // u utf-16
    // u8 utf-8
    // L 宽字节
    ol.direct_insert_right(ol.begin(), 55, 1981);
    ol.direct_insert_right(ol.begin(), 66, 1982);
    ol.direct_insert_right(ol.begin(), 77, 1983);
    ol.direct_insert_right(ol.begin(), 88, 1984);
    ol.direct_insert_right(ol.begin(), 99, 1565);
    auto c = ol.direct_insert_left(ol.direct_insert_right(ol._root, 10LL, 1565), 12, 44);
    auto c2 = ol.direct_insert_right(c, 114, 514);
    auto c3 = ol.direct_insert_left(c, 514, 114);
    // std::cout << ol[0].sbc << std::endl;
    // for (auto &[a, b] : ol)
    //     b = 1;
    std::cout << R"(In Order Traversal)" << std::endl;
    for (auto a : ol)
        std::cout << a.ii << '\t' << a.sbc << std::endl; // 非递归中序遍历，采用迭代器写法，甚至没用堆栈
    std::cout << R"(======)" << std::endl;
    dfsin(ol._root);
    std::cout << R"(Pre Order Traversal)" << std::endl;
    for (auto a = ol.preotbegin(); a != ol.end(); ol.preotmove(a))
        std::cout << (*a).ii << '\t' << (*a).sbc << std::endl; // 非递归先序遍历，采用迭代器写法，甚至没用堆栈
    std::cout << R"(======)" << std::endl;
    dfspre(ol._root);
    std::cout << R"(Post Order Traversal)" << std::endl;
    for (auto a = ol.postotbegin(); a != ol.end(); ol.postotmove(a))
        std::cout << (*a).ii << '\t' << (*a).sbc << std::endl; // 非递归后序遍历，采用迭代器写法，甚至没用堆栈
    std::cout << R"(======)" << std::endl;
    dfspost(ol._root);
    // ol.~BST();
    return 0;
}
catch (const std::string &e)
{
    std::cerr << e << '\n';
    return 1;
    // std::cerr << e.where() << '\n';
}
#endif
