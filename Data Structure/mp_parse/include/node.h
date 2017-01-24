/**
 * @file node.h
 * @author Chen Zhang
 * @data summer 2014
 */

#ifndef CS225_NODE_H
#define CS225_NODE_H

namespace cs225
{

class node
{
public:
		virtual double value() const=0;
		virtual ~node()=default;
};

}




#endif

