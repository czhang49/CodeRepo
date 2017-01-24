/**
 * @file operation.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "operation.h"

namespace cs225
{

const token_type operation::type = token_type::OPERATION;

int operation::precedence() const
{
    switch (text()[0])
    {
        case '~': // unary minus
        case '#': // unary plus
            return 4;
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '-':
        case '+':
            return 1;
        default:
            throw std::runtime_error{"unexpected operator: " + text()};
    }
}

associativity operation::associativity() const
{
    switch (text()[0])
    {
        case '^':
        case '~': // unary minus
        case '#': // unary plus
            return associativity::RIGHT;
        case '*':
        case '/':
        case '-':
        case '+':
            return associativity::LEFT;
        default:
            throw std::runtime_error{"unexpected operator: " + text()};
    }
}

uint32_t operation::args() const
{
    switch (text()[0])
    {
        case '~':
        case '#':
            return 1; // unary ops
        case '^':
        case '*':
        case '/':
        case '-':
        case '+':
            return 2; // all are binary ops
        default:
            throw std::runtime_error{"unexpected operator: " + text()};
    }
}

}
