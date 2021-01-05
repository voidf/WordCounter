#include <memory>
#include <new.h>
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

} // namespace BST

// #include <iostream>

// struct SB
// {
//     long long ii;
//     int sbc;
//     SB() {}
//     SB(long long a, int b) : ii(a), sbc(b) {}
// };

// signed main()
// {
//     try
//     {
//         LinkedList::LinkedList<SB> ol;
//         ol.direct_append(1919810LL, 1);
//         ol.direct_append(1919810LL, 14);
//         ol.direct_append(1919810LL, 5);
//         ol.direct_append(1919810LL, 14);
//         // for (auto i : ol)
//         // std::cout << i << std::endl;
//         while (!ol.empty())
//             std::cout << ol.pop().sbc << std::endl;
//         // ol.pop();
//         ol.direct_append(1145141LL, 1981);
//         ol.direct_append(1145142LL, 1982);
//         ol.direct_append(1145143LL, 1983);
//         ol.direct_append(1145144LL, 1984);
//         ol.direct_append_left(1564LL, 1565);
//         // std::cout << ol[0].sbc << std::endl;
//         // for (auto &[a, b] : ol)
//         //     b = 1;
//         for (auto a : ol)
//             std::cout << a.ii << '\t' << a.sbc << std::endl;
//         while (!ol.empty())
//             std::cout << ol.pop_left().sbc << std::endl;
//     }
//     catch (const std::string &e)
//     {
//         std::cerr << e << '\n';
//         // std::cerr << e.where() << '\n';
//     }

//     return 0;
// }