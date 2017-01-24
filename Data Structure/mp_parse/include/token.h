/**
 * @file token.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_TOKEN_H_
#define CS225_TOKEN_H_

#include <memory>
#include <string>

namespace cs225
{

// forward declarations
class token;
class number;
class operation;

/**
 * Represents the type of a token (either an operation or a number).
 */
enum class token_type
{
    TEXT,
    OPERATION,
    NUMBER
};

/**
 * Represents a token of the input equation. This is a base class which may
 * be converted down to one of the derived class types if it is a number or
 * an operator token. Text tokens do not have a derived type (e.g.,
 * parentheses).
 */
class token
{
  public:
    /**
     * @param value The text for this token
     * @param type The type of the token
     */
    token(std::string value, token_type type);

    /**
     * @return this token as a number token, if possible.
     */
    number* as_number();

    /**
     * @return this token as a number token, if possible
     */
    operation* as_operation();

    /**
     * @return the text for this token
     */
    const std::string& text() const;

    /**
     * @return the type of this token
     */
    token_type type() const;

  private:
    std::string text_; /// The raw text of this token
    token_type type_;  /// The type of this token
};

/**
 * Helper function for making tokens. Usage:
 *
 * ~~~cpp
 * auto num = std::make_token<number>("1");
 * auto op  = std::make_token<operation>("+");
 * ~~~
 *
 * @return a unique_ptr to the base class token
 */
template <class Token>
std::unique_ptr<token> make_token(std::string text)
{
    return std::make_unique<Token>(text, Token::type);
}
}
#endif
