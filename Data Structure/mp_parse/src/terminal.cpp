/**
 * @file terminal.cpp
 * @author Chen Zhang
 * @date summer 2014
 */

#include<iostream>
#include"terminal.h"

namespace cs225
{

cs225::terminal::terminal(double value)
{
	nodevalue=value;
}

double cs225::terminal::value() const 
{
	
	return nodevalue;
}



std::unique_ptr<terminal> make_term(double value)
{
	std::unique_ptr<terminal> temp{new terminal(value)};
	
	return temp;
}

}



