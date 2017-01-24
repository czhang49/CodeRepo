/**
 * @file main.cpp
 * Contains code to test your recursion, stack, and queue problems.
 */

#include <unistd.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

#include "quackfun.h"
#include "exercises.h"

template <typename T>
inline std::string to_string(const T& value);
template <typename T>
inline std::string colorize(const T& actual, const T& expected);
std::string make_red(const std::string& output);
std::string make_green(const std::string& output);

int main()
{
    std::cout << std::boolalpha
              << std::endl; // make true and false print for bools, not 0 and 1

    // Run sum_digits:
    std::cout << "==== sum_digits ====" << std::endl;
    std::cout << "sum_digits(243) = "
              << colorize(recursion_exercises::sum_digits(243), 9) << std::endl;
    std::cout << "expected       = " << 9 << std::endl;
    std::cout << "sum_digits(49)  = "
              << colorize(recursion_exercises::sum_digits(49), 13) << std::endl;
    std::cout << "expected       = " << 13 << std::endl;
    std::cout << "sum_digits(1)   = "
              << colorize(recursion_exercises::sum_digits(1), 1) << std::endl;
    std::cout << "expected       = " << 1 << std::endl;
    std::cout << "sum_digits(0)   = "
              << colorize(recursion_exercises::sum_digits(0), 0) << std::endl;
    std::cout << "expected       = " << 0 << std::endl << std::endl;

    // Run triangle:
    std::cout << "==== triangle ====" << std::endl;
    std::cout << "triangle(0) = " << colorize(recursion_exercises::triangle(0),
                                              0) << std::endl;
    std::cout << "expected    = " << 0 << std::endl;
    std::cout << "triangle(3) = " << colorize(recursion_exercises::triangle(3),
                                              6) << std::endl;
    std::cout << "expected    = " << 6 << std::endl;
    std::cout << "triangle(6) = " << colorize(recursion_exercises::triangle(6),
                                              21) << std::endl;
    std::cout << "expected    = " << 21 << std::endl << std::endl;

    // Run sum:
    std::cout << "==== sum ====" << std::endl;
    std::stack<int> s;

    const int n = 16;
    for (int i = 0; i <= n; i++)
        s.push(i);

    std::stack<int> orig = s;
    std::cout << "Sum:      " << colorize(quackfun::sum<int>(s), 136)
              << std::endl;
    std::cout << "Expected: " << 136 << std::endl;
    if (s == orig)
        std::cout << "Stack " + make_green("unmodified: :)") << std::endl;
    else
        std::cout << "Stack " + make_red("CHANGED: :(") << std::endl;
    std::cout << std::endl;

    // Run scramble:
    std::cout << "==== scramble ====" << std::endl;
    std::queue<int> q;
    for (int i = 0; i <= 16; i++)
        q.push(i);

    quackfun::scramble<int>(q);

    int expected[] = {0, 2, 1, 3, 4, 5, 9, 8, 7, 6, 10, 11, 12, 13, 14, 16, 15};
    std::cout << "Scrambled queue: ";
    for (int i = 0; i <= 16; i++)
    {
        std::cout << colorize(q.front(), expected[i]) << ' ';
        q.pop();
    }
    std::cout << std::endl;
    std::cout << "Expected:        0 2 1 3 4 5 9 8 7 6 10 11 12 13 14 16 15 "
              << std::endl << std::endl;

    // Run verify_same:
    std::cout << "==== verify_same ====" << std::endl;
    std::stack<int> s1;
    std::queue<int> q1;
    for (int i = 0; i < 5; i++)
    {
        s1.push(i);
        q1.push(i);
    }
    q = q1;
    s = s1;
    std::cout << "verify_same(true): " << colorize(quackfun::verify_same(s, q),
                                                   true) << std::endl;
    if (q == q1 && s == s1)
        std::cout << "Stack and queue " + make_green("unmodified: :)")
                  << std::endl;
    else
        std::cout << "Stack or queue " + make_red("CHANGED: :(") << std::endl;

    std::stack<int> s2;
    std::queue<int> q2;
    for (int i = 0; i < 4; i++)
    {
        s2.push(i + 1);
        q2.push(i);
    }
    s2.push(5);
    q2.push(5);

    q = q2;
    s = s2;
    std::cout << "verify_same(false): " << colorize(quackfun::verify_same(s, q),
                                                    false) << std::endl;
    if (q == q2 && s == s2)
        std::cout << "Stack and queue " + make_green("unmodified: :)")
                  << std::endl;
    else
        std::cout << "Stack or queue " + make_red("CHANGED: :(") << std::endl;
    std::cout << std::endl;
}

template <typename T>
inline std::string to_string(const T& value)
{
    std::stringstream ss;
    ss << std::boolalpha << value;
    return ss.str();
}

template <typename T>
inline std::string colorize(const T& actual, const T& expected)
{
    if (isatty(STDOUT_FILENO))
    {
        if (actual == expected)
            return "\033[32m" + to_string(actual) + "\033[0m";
        else
            return "\033[31m" + to_string(actual) + "\033[0m";
    }
    else
        return to_string(actual);
}

std::string make_red(const std::string& output)
{
    if (isatty(STDOUT_FILENO))
        return "\033[31m" + output + "\033[0m";
    else
        return output;
}

std::string make_green(const std::string& output)
{
    if (isatty(STDOUT_FILENO))
        return "\033[32m" + output + "\033[0m";
    else
        return output;
}
