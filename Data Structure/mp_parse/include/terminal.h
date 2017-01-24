/**
 * @file terminal.h
 * @author Chen Zhang
 * @data summer 2014
 */

#ifndef CS225_TERMINAL_H
#define CS225_TERMINAL_H
#include<iostream>
#include"node.h"

namespace cs225
{
class terminal	: public node
{
public:
		terminal(double value);
		double value() const override;

private:
		double nodevalue;
};

std::unique_ptr<terminal> make_term(double value);

}


#endif
