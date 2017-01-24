/**
 * @file quackfun.h
 * Contains the quackfun namespace definition.
 */

#ifndef QUACKFUN_H_
#define QUACKFUN_H_

#include <stack>
#include <queue>

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace quackfun
{
template <typename T>
T sum(std::stack<T>& s);

template <typename T>
void scramble(std::queue<T>& q);

template <typename T>
bool verify_same(std::stack<T>& s, std::queue<T>& q);
}
#include "quackfun.tcc"
#endif
