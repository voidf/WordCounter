#define IMPORT_MODULE
#ifndef LINKLIST_IMPORTED
#define LINKLIST_IMPORTED
#include <memory>
#include <new.h>
// #include <bits/stdc++.h>
// vector<int>v;
namespace LinkedList
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
    struct LinkedList
    {
        struct Content
        {
            typedef std::shared_ptr<Content> P;
            P prev, next;
            T value;
            Content(){};
            Content(T &v) : value(v) {}
            template <typename... Args>
            Content(Args &&... args) : value(std::forward<Args>(args)...) {}
        };
        typedef std::shared_ptr<Content> P;
        P _start, _finish;
        size_t _len;

        P begin() { return _start; }
        P end() { return _finish; }
        T &front() { return _start->value; }
        T &back() { return _finish->prev->value; }
        size_t size() { return this->_len; }
        bool empty() { return this->_len == 0; }
        LinkedList() : _len(0)
        {
            _start = static_cast<P>(new Content());
            _finish = _start;
        }
        ~LinkedList()
        {
            for (auto cur = this->_start; cur != this->_finish; cur++)
                cur.reset();
            this->_finish.reset();
            delete this;
        }

        friend P operator++(P &ptr, int)
        {
            if (!(ptr->next))
                throw IndexErrorException("IndexError: list index out of range");
            ptr = ptr->next;
            return ptr->prev;
        }
        friend P operator--(P &ptr, int)
        {
            if (!(ptr->prev))
                throw IndexErrorException("IndexError: list index out of range");
            ptr = ptr->prev;
            return ptr->next;
        }
        friend P &operator++(P &ptr)
        {
            if (!(ptr->next))
                throw IndexErrorException("IndexError: list index out of range");
            return ptr = ptr->next;
        } // foreach用到这个
        friend P &operator--(P &ptr)
        {
            if (!(ptr->prev))
                throw IndexErrorException("IndexError: list index out of range");
            return ptr = ptr->prev;
        }
        friend P operator+(P ptr, int offset)
        {
            // static P tmp = ptr;
            while (offset > 0)
            {
                if (!(ptr->next))
                    throw IndexErrorException("IndexError: list index out of range");
                ++ptr;
                offset--;
            }
            while (offset < 0)
            {
                if (!(ptr->prev))
                    throw IndexErrorException("IndexError: list index out of range");
                --ptr;
                offset++;
            }
            return ptr;
        }
        friend P operator-(P &ptr, int offset) { return ptr + (-offset); }
        friend T &operator*(P &ptr) { return ptr->value; }
        void append(const T &x)
        {
            P tmp(new Content(x));
            tmp->next = this->_finish;
            if (this->_finish->prev)
            {
                this->_finish->prev->next = tmp;
                tmp->prev = this->_finish->prev;
            }
            else
                this->_start = tmp;
            this->_finish->prev = tmp;
            this->_len++;
        }
        void append_left(const T &x)
        {
            P tmp(new Content(x));
            tmp->next = this->_start;
            this->_start->prev = tmp;
            this->_start--;
            this->_len++;
        }

        void append(T &&x) { direct_append(std::move(x)); }
        void append_left(T &&x) { direct_append_left(std::move(x)); }

        template <typename... Args>
        void direct_append(Args &&... args)
        {
            P tmp(new Content(std::forward<Args>(args)...));
            tmp->next = this->_finish;
            if (this->_finish->prev)
            {
                this->_finish->prev->next = tmp;
                tmp->prev = this->_finish->prev;
            }
            else
                this->_start = tmp;
            this->_finish->prev = tmp;
            this->_len++;
        }
        template <typename... Args>
        void direct_append_left(Args &&... args)
        {
            P tmp(new Content(std::forward<Args>(args)...));
            tmp->next = this->_start;
            this->_start->prev = tmp;
            this->_start--;
            this->_len++;
        }
        T pop()
        {
            if (this->empty())
                throw IndexErrorException("IndexError: pop from empty list", this);
            T tmp = this->back();
            this->_finish--;
            (_finish + 1).reset();
            this->_len--;
            return tmp;
        }
        T pop_left()
        {
            if (this->empty())
                throw IndexErrorException("IndexError: pop from empty list", this);
            T tmp = this->front();
            this->_start++;
            (_start - 1).reset();
            this->_len--;
            return tmp;
        }
    };

} // namespace LinkedList
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

signed main()
try
{
    LinkedList::LinkedList<SB> queue; // 手写双向链表，可以用来实现队列和栈
    queue.direct_append(1919810LL, 1);
    queue.direct_append(1919810LL, 14);
    queue.direct_append(1919810LL, 5);
    queue.direct_append(1919810LL, 14);
    // for (auto i : queue)
    // std::cout << i << std::endl;
    while (!queue.empty())
        std::cout << queue.pop().sbc << std::endl;
    // queue.pop();
    queue.direct_append(1145141LL, 1981);
    queue.direct_append(1145142LL, 1982);
    queue.direct_append(1145143LL, 1983);
    queue.direct_append(1145144LL, 1984);
    queue.direct_append_left(1564LL, 1565);
    // std::cout << queue[0].sbc << std::endl;
    // for (auto &[a, b] : queue)
    //     b = 1;
    for (auto a : queue)
        std::cout << a.ii << '\t' << a.sbc << std::endl;
    while (!queue.empty())
        std::cout << queue.pop_left().sbc << std::endl;
    LinkedList::LinkedList<int> stack;
    stack.direct_append(1);
    stack.direct_append(9);
    stack.direct_append(1);
    stack.direct_append(9);
    stack.direct_append(8);
    stack.direct_append(1);
    stack.direct_append(0);
    while (!stack.empty())
        std::cout << stack.pop() << std::endl;

    return 0;
}
catch (const std::string &e)
{
    std::cerr << e << '\n';
    return 1;
}
#endif
