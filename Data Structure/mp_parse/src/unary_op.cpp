/**
 * @file unary_op.cpp
 * @author Chen Zhang
 * @date  summer 2014
 */


#include"unary_op.h"

namespace cs225
{



cs225::unary_op::unary_op(std::unique_ptr<node> arg)
{
	arg_=std::move(arg);
}	

double cs225::unary_op::value() const 
{
	return compute(arg_->value());	
}




}




