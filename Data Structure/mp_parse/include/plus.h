/**
 * @file plus.h
 * @author chen zhang
 * @date summer 2014
 */
#ifndef CS225_PLUS_H
#define CS225_PLUS_H
#include"binary_op.h"

namespace cs225
{

class plus : public binary_op
{
public:
		using binary_op::binary_op;
		double combine(double left, double right) const override;

};


}


#endif
