/**
 * @file operation.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_OPERATION_H_
#define CS225_OPERATION_H_

#include "token.h"

namespace cs225
{

/**
 * Denotes the associativity of an operation (either left or right
 * associative).
 *
 * @see https://en.wikipedia.org/wiki/Operator_associativity
 */
enum class associativity
{
    LEFT,
    RIGHT
};

/**
 * Represents an operation token in the input equation.
 */
class operation : public token
{
  public:
    /// The token type
    const static token_type type;

    /// Inherits constructors from token
    using token::token;

    /**
     * @return the precedence of this operation, as a number
     */
    int precedence() const;

    /**
     * @return the associativity of this operation
     */
    associativity associativity() const;

    /**
     * @return the number of arguments required for this operation
     */
    uint32_t args() const;
};
}
#endif
