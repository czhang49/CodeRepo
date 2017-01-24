/**
 * @file times.h
 * @author chen zhang
 * @date summer 2014
 */
#ifndef CS225_TIMES_H
#define CS225_TIMES_H
#include"binary_op.h"

namespace cs225
{

class times : public binary_op
{
public:
		using binary_op::binary_op;
		double combine(double left, double right) const override;

};


}


#endif
