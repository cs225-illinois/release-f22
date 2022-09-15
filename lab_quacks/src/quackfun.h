/**
 * @file quackfun.h
 * Contains the QuackFun namespace definition.
 */

#pragma once

#include <stack>
#include <queue>

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace QuackFun
{
    using std::stack;
    using std::queue;

    template <typename T>
    T sum(stack<T>& s);

    bool isBalanced(queue<char> input);

    template <typename T>
    void scramble(queue<T>& q);

};

#include "quackfun.hpp"
