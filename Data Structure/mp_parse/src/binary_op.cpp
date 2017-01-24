/**
 * @file binary_op.h
 * @author chen zhang
 * @date summer 2014
 */

#include"binary_op.h"
#include"plus.h"
#include"minus.h"
#include"times.h"
#include"divide.h"
#include"exponent.h"

namespace cs225
{



cs225::binary_op::binary_op(std::unique_ptr<node> left, std::unique_ptr<node> right)
{
	left_=std::move(left);
	right_=std::move(right);	

}

double cs225::binary_op::value() const 
{
	return combine(left_->value(), right_->value());
}


std::unique_ptr<node> make_binary_op(const std::string& op, std::unique_ptr<node> left, std::unique_ptr<node> right)
{
	std::unique_ptr<node> temp=nullptr;
	if (op=="+")
	{
		temp.reset(new plus(std::move(left),std::move(right)));

	}
	if (op=="-")
	{
		temp.reset(new minus(std::move(left),std::move(right)));
	}
	if (op=="*")
	{
		temp.reset(new times(std::move(left),std::move(right)));
	}
	if (op=="/")
	{
		temp.reset(new divide(std::move(left),std::move(right)));
	}
	if (op=="^")
	{
		temp.reset(new exponent(std::move(left),std::move(right)));
	}
	return temp;

}


}

