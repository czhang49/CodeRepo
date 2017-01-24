/**
 * @file ast_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <cmath>
#include <limits>
#include <string>

#include "divide.h"
#include "exponent.h"
#include "minus.h"
#include "plus.h"
#include "terminal.h"
#include "times.h"
#include "uminus.h"
#include "uplus.h"

using namespace cs225;

bool relequal(double first, double second)
{
    auto max = std::max(1.0, std::max(std::abs(first), std::abs(second)));
    return std::abs(first - second) <=
           std::numeric_limits<double>::epsilon() * max;
}

void test_binary_ops()
{
    auto times = make_binary_op("*", make_term(3), make_term(2));
    auto plus = make_binary_op("+", std::move(times), make_term(6));
    auto minus = make_binary_op("-", make_term(9), make_term(4));
    auto exp = make_binary_op("^", std::move(plus), std::move(minus));
    auto div = make_binary_op("/", std::move(exp), make_term(2));

    assert(relequal(div->value(), std::pow(3.0 * 2 + 6, 9.0 - 4) / 2.0));
}

void test_unary_ops()
{
    auto neg = make_unary_op("~", make_term(2));
    auto pos = make_unary_op("#", make_term(2));

    assert(relequal(neg->value(), -2.0));
    assert(relequal(pos->value(), 2.0));

    auto div = make_binary_op("/", std::move(neg), std::move(pos));
    assert(relequal(div->value(), -1.0));
}

int main()
{
    test_binary_ops();
    test_unary_ops();
}
