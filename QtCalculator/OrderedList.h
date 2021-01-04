// #include<>
// #include <stl_vector.h>
#include <memory>
#include <new.h>
// #include <bits/stdc++.h>
// vector<int>v;
namespace OrderedList
{
    const int _block_size = 0x1; // 搬家阈值
    template <typename T, typename A = std::allocator<T>>
    struct OrderedList
    {
        // typedef std::shared_ptr<T> Tp; //这里不能用智能指针，没有++操作符
        typedef T *Tp;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        // typedef typename std::allocator_traits<A>::template rebind<T>::other AT; // std的AT没有rebind
        typedef typename __gnu_cxx::__alloc_traits<A>::template rebind<T>::other AT;
        // typedef std::allocator_traits<AT> ACT;
        typedef __gnu_cxx::__alloc_traits<AT> ACT;
        typedef typename ACT::reference reference;

        struct Allocator : public AT // 没有用ASan的需求，不写了
        {
            Tp _start;
            Tp _finish;
            Tp _end_of_storage;
            Allocator() : AT(), _start(), _finish(), _end_of_storage(){};
            // Allocator(AT const &arg) : AT(arg), _start(), _finish(), _end_of_storage(){};
        };

        Allocator _allocator;
        Allocator &get_allocator() { return *static_cast<Allocator *>(&this->_allocator); }

        OrderedList() : _allocator(){};
        ~OrderedList() { std::_Destroy(this->_allocator._start, this->_allocator._finish, get_allocator()); }
        Tp begin() { return this->_allocator._start; }
        Tp end() { return this->_allocator._finish; }
        T front() { return *(this->_allocator._start); }
        T back() { return *(this->_allocator._finish - 1); }
        size_type size() { return size_type(this->_allocator._finish - this->_allocator._start); }
        bool empty() { return this->_allocator._finish == this->_allocator._start; }

        // reference operator[](size_type n) { return *(begin() + n); }
        reference operator[](size_type _pos)
        {
            return *(this->_allocator._start + _pos);
        }
        void append(const T &x)
        {
            if (this->_allocator._finish != this->_allocator._end_of_storage)
                house_move();

            ACT::construct(this->_allocator, this->_allocator._finish, x);
            ++this->_allocator._finish;
        }
        void append(T &&x) { direct_append(std::move(x)); }
        T pop()
        {
            T tmp = *(--this->_allocator._finish);
            ACT::destroy(this->_allocator, this->_allocator._finish);
            return tmp;
        }

        template <typename... Args>
        void direct_append(Args &&... args)
        {
            if (this->_allocator._finish == this->_allocator._end_of_storage)
                house_move();

            construct(this->_allocator._finish, std::forward<Args>(args)...);
            ++this->_allocator._finish;
        }

        void deallocate(Tp _obj_pointer, size_t _count)
        {
            if (_allocator, _obj_pointer)
                ACT::deallocate(_allocator, _obj_pointer, _count);
        }
        template <typename T1, typename... Args>
        void construct(T1 *allocated_memory_block, Args &&... args) { ::new (allocated_memory_block) T1(std::forward<Args>(args)...); }
        // placement new写法。在已分配的内存块allocated_memory_block上构建T1对象
        // 双冒号new：忽略class-specific replacements
        Tp allocate(size_t n) { return n == 0 ? Tp() : ACT::allocate(_allocator, n); }

        void house_move() // 搬家（
        {
            size_t new_size = size() + _block_size;
            Tp now_start = allocate(new_size);
            Tp now_finish = now_start;
            for (auto &elements_before : *(this))
            {
                construct(now_finish++, elements_before);
            }
            std::_Destroy(this->_allocator._start, this->_allocator._finish, get_allocator());
            deallocate(this->_allocator._start, this->_allocator._end_of_storage - this->_allocator._start);
            this->_allocator._start = now_start;
            this->_allocator._finish = now_finish;
            this->_allocator._end_of_storage = now_start + new_size;
        }
    };

} // namespace OrderedList

// #include <iostream>

// struct SB
// {
//     long long ii;
//     int sbc;
//     SB(long long a, int b) : ii(a), sbc(b) {}
// };

// signed main()
// {
//     OrderedList::OrderedList<SB> ol;
//     ol.direct_append(1919810LL, 1);
//     ol.direct_append(1919810LL, 14);
//     ol.direct_append(1919810LL, 5);
//     ol.direct_append(1919810LL, 14);
//     // for (auto i : ol)
//     // std::cout << i << std::endl;
//     while (!ol.empty())
//         std::cout << ol.pop().sbc << std::endl;
//     ol.direct_append(114514LL, 198);
//     ol.direct_append(114514LL, 198);
//     ol.direct_append(114514LL, 198);
//     ol.direct_append(114514LL, 198);
//     ol[0].sbc = 485964;
//     std::cout << ol[0].sbc << std::endl;
//     for (auto &[a, b] : ol)
//         b = 1;
//     for (auto &[a, b] : ol)
//         std::cout << a << '\t' << b << std::endl;
//     return 0;
// }