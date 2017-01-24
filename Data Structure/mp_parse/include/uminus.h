/**
 * @file uminus.h
 * @author Chen Zhang
 * @date summer 2014
 */

#ifndef CS225_UMINUS_H
#define CS225_UMINUS_H
#include"unary_op.h"

namespace cs225
{

class uminus	: public unary_op
{
public:
	using unary_op::unary_op;	
	double compute(double arg) const override;


};


}


#endif
