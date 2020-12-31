#include <bits/stdc++.h>
#include <windows.h>
namespace Logger
{
    struct info
    {
        template <typename FIRST, typename... PACK>
        static void print(FIRST first, PACK... params)
        {
            std::cout << first;
            print(params...);
        }

        //重载函数版本，递归结束条件
        template <typename T>
        static void print(T end)
        {
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
    void notePrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //Ao
        std::cout << "[NOTE] ";
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
    void debugPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        std::cout << "[Debug] ";
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
    void fatalPrint(Motto... a)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); //Murasaki
        std::cout << "[FATAL] ";
        info::print(a...);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
} // namespace colorPrint
