/**
 * @file parser.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_PARSER_H_
#define CS225_PARSER_H_

#include <memory>
#include "node.h"
#include "queue.h"
#include "stack.h"
#include "token.h"

namespace cs225
{

/**
 * Converts an equation that has been lexed/tokenized (in the form of a
 * queue of tokens) to a parse tree representing the expression. This
 * should use the "private class" parser that you will see declared in
 * parser.cpp.
 *
 * @param tokens The tokenized equation
 * @return the root of the parse tree
 */
std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens);
}
#endif
