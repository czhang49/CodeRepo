/**
 * @file lex.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_LEX_H_
#define CS225_LEX_H_

#include <memory>
#include "queue.h"
#include "token.h"

namespace cs225
{

/**
 * Converts an equation in std::string form to a queue of tokens.
 *
 * @param line The equation to tokenize
 * @return a queue of (unique_ptr to) tokens that represents the equation
 * in grammatical form
 */
queue<std::unique_ptr<token>> lex(const std::string& line);
}
#endif
