#include <bits/stdc++.h>
#include <windows.h>
#define LOGGER_LR_TEST
namespace Logger
{
    struct info
    {
        const static char separator = ' ';
        template <typename FIRST, typename... PACK>
        static void print(FIRST &first, PACK &... params) // 左值引用
        {
#ifdef LOGGER_LR_TEST
            std::cout << "[L]";
#endif
            std::cout << first << separator;
            print(params...);
        }
        template <typename FIRST, typename... PACK>
        static void print(FIRST &&first, PACK &&... params) // 右值引用
        {
#ifdef LOGGER_LR_TEST
            std::cout << "[R]";
#endif
            std::cout << first << separator;
            print(std::forward<PACK>(params)...);
        }

        //重载函数版本，递归结束条件
        template <typename T>
        static void print(T &end) // 上面用左值引用这里就写&
        {
#ifdef LOGGER_LR_TEST
            std::cout << "[L]";
#endif
            std::cout << end << std::endl;
        }
        template <typename T>
        static void print(T &&end) // 上面用右值引用这里就写&&
        {
#ifdef LOGGER_LR_TEST
            std::cout << "[R]";
#endif
            std::cout << end << std::endl;
        }
    };

    template <typename... Motto>
    void infoPrint(Motto... a) //RGB format
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //Midori
        std::cout << "[Info] ";
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //Shiro
    }
    template <typename... Motto>
    void greenPrint(Motto... a) //RGB format
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //Midori
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //Shiro
    }
    template <typename... Motto>
    void notePrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //Ao
        std::cout << "[NOTE] ";
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void cyanPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //Ao
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void warnPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //Ki
        std::cout << "[WARN] ";
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void yellowPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //Ki
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void debugPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        std::cout << "[Debug] ";
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void bluePrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void errorPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //Aka
        std::cout << "[ERROR] ";
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void redPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //Aka
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void fatalPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); //Murasaki
        std::cout << "[FATAL] ";
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    template <typename... Motto>
    void purplePrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); //Murasaki
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
} // namespace Logger
