#ifndef BST_IMPORTED
#define BST_IMPORTED

// #define ENABLE_FFT // 有点危的FFT乘法

#include <bitset>
#include <string>
#include <complex>
#include <math.h>
#include <iostream>
#include <cstring>
#if __cplusplus >= 201907L
#include <numbers>
constexpr double pi = std::numbers::pi;
#else
constexpr double pi = acos(-1);
#endif
using LL = long long;
namespace BigIntegerDomain
{
    template <size_t siz>
    struct BigInteger : std::bitset<siz>
    {
        // std::bitset<siz> _bits;
        template <typename... Args>
        BigInteger(Args &&... args) : std::bitset<siz>(std::forward<Args>(args)...) {}

        template <typename Args>
        BigInteger operator<<(Args args) { return (BigInteger)((std::bitset<siz>)*this << args); }
        template <typename Args>
        BigInteger operator>>(Args args) { return (BigInteger)((std::bitset<siz>)*this >> args); }
        bool operator<(BigInteger &b)
        {
            for (auto i = this->size() - 1; i >= 0; i--)
                if (this->test(i) != b[i])
                    return this->test(i) < b[i];
            return 0;
        }
        bool operator>(BigInteger &b)
        {
            for (int i = this->size() - 1; i >= 0; --i)
                if (this->test(i) != b[i])
                    return this->test(i) > b[i];
            return 0;
        }
        // template <typename T>
        // BigInteger operator<<(T x) { return static_cast<BigInteger>((*this) << x); }
        bool operator<=(BigInteger &b)
        {
            return !(*this > b);
        }
        bool operator<=(BigInteger &&b) { return !(*this > b); }
        bool operator>=(BigInteger &b) { return !(*this < b); }
        bool operator>=(BigInteger &&b) { return !(*this < b); }
        BigInteger operator+(BigInteger b)
        {
            if (b.none())
                return *this;
            if (this->none())
                return b;
            bool c = 0, t;
            for (auto i = 0; i < this->size(); i++)
            {
                t = c ^ this->test(i) ^ b.test(i);
                c = (this->test(i) & c) | (c & b.test(i)) | (this->test(i) & b.test(i));
                b[i] = t;
            }
            return b;
        }
        BigInteger &operator+=(BigInteger &b) { return (*this) = (*this) + b; }
        BigInteger operator-() { return BigInteger<siz>(1) + ~(*this); }
        BigInteger operator-(BigInteger &b) { return b.any() ? (*this + (-b)) : *this; }
        BigInteger &operator-=(BigInteger &b) { return (*this) = (*this) - b; }
        BigInteger &operator-=(BigInteger &&b) { return (*this) = (*this) - b; }
        BigInteger operator*(BigInteger b)
        {
#ifndef ENABLE_FFT
            BigInteger a(*this);
            BigInteger c(0);
            while (b.any())
            {
                if (b[0])
                    c += a;
                b >>= 1, a <<= 1;
            }
            return c;
#else
            return FFTBigNumMul(*this, b);
#endif
        }
        BigInteger &operator*=(const BigInteger &b) { return (*this) = (*this) * b; }
        std::pair<BigInteger, BigInteger> divide(BigInteger a, BigInteger &b)
        {
            BigInteger c(0);
            int i = 0;
            while ((BigInteger)(b << (i + 1)) <= a)
                ++i;
            while (i >= 0)
            {
                if (a >= (BigInteger)(b << i))
                    a -= (BigInteger)(b << i), c.set(i, 1);
                i--;
            }
            return std::make_pair(c, a);
        }
        BigInteger operator/(BigInteger &b) { return divide(*this, b).first; }
        BigInteger &operator/=(BigInteger &b) { return (*this) = (*this) / b; }
        BigInteger operator%(BigInteger &b) { return divide(*this, b).second; }
        BigInteger &operator%=(BigInteger &b) { return (*this) = (*this) / b; }
        BigInteger &fromString(std::string &s)
        {
            this->reset();
            bool minus_tag = false;
            for (auto c : s)
            {
                if (c == '-')
                    minus_tag = true;
                else if (isdigit(c))
                    (*this) = (BigInteger)((*this) << 3) + (BigInteger)((*this) << 1) + (c ^ 0x30);
            }
            if (minus_tag)
                *this = -(*this);
            return *this;
        }
        BigInteger &fromString(std::string &&s)
        {
            this->reset();
            bool minus_tag = false;
            for (auto c : s)
            {
                if (c == '-')
                    minus_tag = true;
                else if (isdigit(c))
                    (*this) = (BigInteger)((*this) << 3) + (BigInteger)((*this) << 1) + (c ^ 0x30);
            }
            if (minus_tag)
                *this = -(*this);
            return *this;
        }

        static BigInteger FFTBigNumMul(const BigInteger &A, const BigInteger &B)
        {
            auto max_length = std::max(A.size(), B.size());

            LL limit = 1;
            LL bit = 0;

            while (limit < max_length << 1)
                bit++, limit <<= 1;

            // LL rev[limit + 5] = {0};
            LL *rev = new LL[limit + 1];
            memset(rev, 0, sizeof(rev));

            for (auto i = 0; i <= limit; i++)
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

            auto a = new std::complex<double>[limit + 1];
            auto b = new std::complex<double>[limit + 1];
            // std::complex<double> a[limit + 1], b[limit + 1];

            for (auto i = 0; i < limit; i++)
            {
                a[i] = i >= A.size() ? 0 : A[A.size() - i - 1];
                b[i] = i >= B.size() ? 0 : B[B.size() - i - 1];
            }

            BigInteger c(0);

            FFT(a, limit, 1, rev);
            FFT(b, limit, 1, rev);
            for (auto i = 0; i <= limit; i++)
                a[i] *= b[i];
            FFT(a, limit, -1, rev); // 1是FFT变化，-1是逆变换
            // for (auto i = limit; i >= 0; i--)
            // {
            //     if (c[i] == 0 and zerofliter == 0) // 去前导零
            //         continue;
            //     zerofliter = true;
            //     output[outputPtr++] = c[i] ^ 0x30;
            // }
            for (LL i = limit; i > 0; i--)
            {
                a[i] = static_cast<int>(a[i].real() / limit + 0.5);
                a[i - 1] += (static_cast<int>(a[i].real()) >> 1) * limit;
                a[i] = static_cast<int>(a[i].real()) & 1;
            }

            for (LL i = 0; i <= std::min(static_cast<size_t>(limit), c.size() - 1); i++)
            {
                // std::cout << static_cast<int>(a[A.size()+B.size()-1-i].real()) << std::endl;
                c[i] = static_cast<int>(a[A.size() + B.size() - 2 - i].real()); // +0.5即四舍五入
            }
            delete[] a;
            delete[] b;
            delete[] rev;
            return c;
        }

        static void FFT(std::complex<double> a[], LL n, LL inv, LL rev[]) // FFT系列没有外部依赖数组，不用打ifdef
        {
            for (auto i = 0; i < n; i++)
                if (i < rev[i])
                    std::swap(a[i], a[rev[i]]);
            for (auto mid = 1; mid < n; mid <<= 1)
            {
                std::complex<double> tmp(cos(pi / mid), inv * sin(pi / mid));
                for (auto i = 0; i < n; i += mid << 1)
                {
                    std::complex<double> omega(1, 0);
                    for (auto j = 0; j < mid; j++, omega *= tmp)
                    {
                        auto x = a[i + j], y = omega * a[i + j + mid];
                        a[i + j] = x + y, a[i + j + mid] = x - y;
                    }
                }
            }
        }
    };
} // namespace BigIntegerDomain
#endif

#ifndef IMPORT_MODULE
#include <iostream>
signed main()
try
{
    using namespace BigIntegerDomain;
    using B = BigInteger<100>;
    B a(114514), b(1919810);
    B c = a << 2;
    c <<= 2;
    c += b;
    // a += b;
    // bool tm = (c <= b);
    // std::cout << tm;
    std::cout << a.fromString(std::string("-345125354263")) << std::endl;
    // for (int i = a.size() - 1; i >= 0; i--) // auto 给推成无符号了草
    // std::cout << a[i];
    std::cout << std::endl;
    return 0;
}
catch (const std::string &e)
{
    std::cerr << e << '\n';
    return 1;
}
#endif