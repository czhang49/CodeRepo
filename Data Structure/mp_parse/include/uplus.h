/**
 * @file uplus.h
 * @author Chen Zhang
 * @date summer 2014
 */

#ifndef CS225_UPLUS_H
#define CS225_UPLUS_H
#include"unary_op.h"
#include<iostream>
namespace cs225
{

class uplus : public unary_op
{
public:
		using unary_op::unary_op;
		double compute(double arg) const override;

};

std::unique_ptr<node> make_unary_op(const std::string& op,std::unique_ptr<node> arg);
}


#endif
