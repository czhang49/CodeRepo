/**
 * @file number.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <string>
#include "number.h"

namespace cs225
{

const token_type number::type = token_type::NUMBER;

double number::value() const
{
    return std::stod(text());
}
}
