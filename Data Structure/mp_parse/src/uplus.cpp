/**
 * @file uplus.cpp
 * @author Chen Zhang
 * @date summer 2014
 */
#include"uplus.h"
#include"uminus.h"
namespace cs225
{


double cs225::uplus::compute(double arg) const 
{
	return arg;
}

std::unique_ptr<node> make_unary_op(const std::string& op,std::unique_ptr<node> arg)
{	
	std::unique_ptr<node> temp=nullptr;
	if (op=="#")
	{
		temp.reset(new uplus(std::move(arg)));

	}
	if (op=="~")
	{
		temp.reset(new uminus(std::move(arg)));
	}

	return temp;
}







}






