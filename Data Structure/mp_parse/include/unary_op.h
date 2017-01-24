/**
 * @file unary_op.h
 * @author Chen Zhang
 * @date summer 2014
 */

#ifndef CS225_UNARY_OP_H
#define CS225_UNARY_OP_H
#include<iostream>
#include"node.h"

namespace cs225
{

class unary_op	:	public node
{
public:
		unary_op(std::unique_ptr<node> arg);
		double value() const override;
		virtual double compute(double val) const=0;

private:
		std::unique_ptr<node> arg_;

};

}


#endif
