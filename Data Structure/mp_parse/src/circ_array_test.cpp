/**
 * @file circ_array_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <iostream>
#include "circ_array.h"

using namespace cs225;

int main()
{
    circ_array<int> arr{6};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i + 1;
    arr.push_front(0);
    arr.push_back(7);
	std::cout<<arr.size()<<std::endl;	
	std::cout<<arr.size()<<std::endl;	
    for (uint64_t i = 0; i < arr.size(); ++i)
    {
	    assert(arr.at(i) == i);
    }
	std::cout<<__LINE__<<std::endl;
	assert(arr.size() == 8);
	std::cout<<__LINE__<<std::endl;
    arr.pop_front();
    assert(arr[0] == 1);
    arr.pop_front();
    assert(arr[0] == 2);

	std::cout<<__LINE__<<std::endl;
    arr.pop_back();
    std::cout<<arr.size()<<" "<<arr[arr.size()-1]<<std::endl;
	assert(arr[arr.size() - 1] == 6);
    arr.pop_back();
    assert(arr[arr.size() - 1] == 5);
    assert(arr.size() == 4);

    arr.erase(2);
	std::cout<<arr.size()<<arr[0]<<arr[1]<<arr[2]<<std::endl;
    assert(arr[0] == 2);
    assert(arr[1] == 3);
    assert(arr[2] == 5);
    assert(arr.size() == 3);

    return 0;
}
