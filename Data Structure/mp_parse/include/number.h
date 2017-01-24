/**
 * @file number.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_NUMBER_H_
#define CS225_NUMBER_H_

#include "token.h"

namespace cs225
{

/**
 * Represents a number token in the input equation.
 */
class number : public token
{
  public:
    /// The token type
    const static token_type type;

    /// Inherits constructors from token
    using token::token;

    /**
     * @return the value of this token as an actual double
     */
    double value() const;
};
}
#endif
