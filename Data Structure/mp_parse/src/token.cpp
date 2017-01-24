/**
 * @file token.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "token.h"
#include "number.h"
#include "operation.h"

namespace cs225
{

token::token(std::string value, token_type type)
    : text_{std::move(value)}, type_{type}
{
    // nothing
}

number* token::as_number()
{
    if (type() != token_type::NUMBER)
        throw std::runtime_error{"invalid token cast"};
    return static_cast<number*>(this);
}

operation* token::as_operation()
{
    if (type() != token_type::OPERATION)
        throw std::runtime_error{"invalid token cast"};
    return static_cast<operation*>(this);
}

const std::string& token::text() const
{
    return text_;
}

token_type token::type() const
{
    return type_;
}
}
