/**
 * @file exponent.h
 * @author chen zhang
 * @date summer 2014
 */
#ifndef CS225_EXPONENT_H
#define CS225_EXPONENT_H
#include"binary_op.h"

namespace cs225
{

class exponent : public binary_op
{
public:
		using binary_op::binary_op;
		double combine(double left, double right) const override;

};


}


#endif
