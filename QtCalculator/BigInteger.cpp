#ifndef BST_IMPORTED
#define BST_IMPORTED
#include <bitset>
#include <string>
// #include<bits/stdc++.h>
// bitset<10>s;
namespace BigInteger
{
    template <size_t siz>
    struct BigInteger : public std::bitset<siz>
    {
        template <typename... Args>
        BigInteger(Args &&... args) : std::bitset<siz>(std::forward<Args>(args)...) {}
        // BigInteger(int i) : std::bitset<siz>(i) {}
        // BigInteger(long long i) : std::bitset<siz>(i) {}
        // BigInteger(std::string &s) : std::bitset<siz>(s) {}
        // BigInteger(std::string &&s) : std::bitset<siz>(s) {}
        // BigInteger(const char s[]) : std::bitset<siz>(s) {}
        bool operator<(const BigInteger &b)
        {
            for (auto i = this->size() - 1; i >= 0; i--)
                if (this->test(i) != b[i])
                    return this->test(i) < b[i];
            return 0;
        }
        bool operator>(const BigInteger &b)
        {
            for (int i = this->size() - 1; i >= 0; --i)
                if (this->test(i) != b[i])
                    return this->test(i) > b[i];
            return 0;
        }
        bool operator<=(const BigInteger &b) { return !(*this > b); }
        bool operator>=(const BigInteger &b) { return !(*this < b); }
        BigInteger operator+(BigInteger b)
        {
            b.reset();
            if (b.none())
                return *this;

            bool c = 0, t;
            for (auto i = 0; i < this->size(); i++)
            {
                t = c ^ this->test(i)
            }
            return b.any() ? ((*this) ^ b) ^ (((*this) & b) << 1) : *this;
        }
        BigInteger &operator+=(const BigInteger &b) { return (*this) = (*this) + b; }
        BigInteger operator-() { return BigInteger(1) + ~(*this); }
        BigInteger operator-(const BigInteger &b) { return b.any() ? (*this ^ b) - ((~*this & b) << 1) : *this; }
        BigInteger &operator-=(const BigInteger &b) { return (*this) = (*this) - b; }
    };
} // namespace BigInteger
#endif

#ifndef IMPORT_MODULE
#include <iostream>

signed main()
try
{
    BigInteger::BigInteger<11> a("1100"), b("1000");
    a += b;
    std::cout << b;
    for (auto i = a.size() - 1; i >= 0; i--)
        std::cout << a[i];
    std::cout << std::endl;
    return 0;
}
catch (const std::string &e)
{
    std::cerr << e << '\n';
    return 1;
}
#endif