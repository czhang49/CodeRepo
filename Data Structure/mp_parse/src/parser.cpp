/**
 * @file parser.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include "parser.h"
#include "operation.h"
#include "number.h"
#include "terminal.h"
#include "binary_op.h"
#include "unary_op.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "exponent.h"
#include "uplus.h"
#include "uminus.h"

namespace cs225
{

/**
 * A "private class" for helping us parse expressions. Maintains all of the
 * state necessary to perform Dijkstra's shunting-yard algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
class parser
{
  public:
    /**
     * @param tokens The tokens to parse
     * @return the root of the parse tree for that expression
     */
    std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens);

  private:
    // add lots of other helper methods here!

    /**
     * The stack to hold the operator tokens encountered. This is the "side
     * rail" in the shunting yard algorithm.
     */
    stack<std::unique_ptr<token>> ops_;

    /**
     * What is this for? It is a mystery (and a hint)!
     */
    stack<std::unique_ptr<node>> nodes_;
};

std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens)
{
    parser p;
    return p.parse(tokens);
}

std::unique_ptr<node> parser::parse(queue<std::unique_ptr<token>>& tokens)
{
	queue<std::unique_ptr<token>> output;
	std::unique_ptr<node> temp;    
	std::unique_ptr<node> temp2;

	while (!tokens.empty())
    {
        auto& tok = tokens.front();
        /// @todo handle the token
		if(tok->text()=="(")
		{
			ops_.push(std::move(tok));
		}
		else if (tok->text()==")")
		{	
			while(ops_.top()->text()!="(")
			{
				output.push(std::move(ops_.top()));
				ops_.pop();
				
				if(ops_.empty())
				{
					throw std::runtime_error ("The right parathesis does not have a corresponding left one in the ops stack to match");
				}
			}
			ops_.pop();	
		}
        else if (tok->type()==token_type::NUMBER)
		{	
			output.push(std::move(tok));
		}
		else if(tok->type()==token_type::OPERATION)
		{	
			while(!ops_.empty() && ops_.top()->type()==token_type::OPERATION)
			{
				if (( tok->as_operation()->associativity()==associativity::LEFT && tok->as_operation()->precedence()<=ops_.top()->as_operation()->precedence() ) || tok->as_operation()->precedence()<ops_.top()->as_operation()->precedence()  )
				{
					output.push(std::move(ops_.top()));
					ops_.pop();
				}
				else
					break;
			}
			ops_.push(std::move(tok));
		}
		tokens.pop();
    }

	while(!ops_.empty())
	{
		if (ops_.top()->text()=="(" || ops_.top()->text()==")")
		{
			throw std::runtime_error ("Still parethesis left in the operator stack, mismatched parethesis");
		}
		
		output.push(std::move(ops_.top()));
		ops_.pop();
	}

	while(!output.empty())
	{
		if(output.front()->type()==token_type::NUMBER)
		{
			nodes_.push(cs225::make_term(output.front()->as_number()->value()));
			output.pop();
		}
		if(output.front()->type()==token_type::OPERATION)
		{
			if (output.front()->as_operation()->args()>nodes_.size())
				throw std::runtime_error ("The value in the stack is less than what is required by the operator in the output queue");
			if (output.front()->as_operation()->args()==1)
			{
				temp=std::move(nodes_.top());
				nodes_.pop();
				nodes_.push(cs225::make_unary_op(output.front()->text(),std::move(temp)));				
				output.pop();
			}
			else if(output.front()->as_operation()->args()==2)
			{
				temp=std::move(nodes_.top());
				nodes_.pop();
				temp2=std::move(nodes_.top());
				nodes_.pop();
				nodes_.push(cs225::make_binary_op(output.front()->text(),std::move(temp2),std::move(temp)));
				output.pop();
			}
		}

	}
	if (nodes_.size()!=1)
		throw std::runtime_error("The number of values are too much, does not match the number of the operator");
	return std::move(nodes_.top());
    /// @todo clean up remaining operators
    /// @todo return the root of your tree
}
}








