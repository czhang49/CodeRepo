/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
    dsets s;

    s.add_elements(50);

    s.merge(2, 3);
    s.merge(3, 5);

    s.merge(5, 7);
    s.merge(7, 2);

    s.merge(4, 6);

    cout << s.find(7) << endl;
    cout << s.find(5) << endl;
    cout << s.find(6) << endl;

    s.add_elements(1);

    cout << s.find(50) << endl;

    s.merge(50, 3);

    cout << s.find(50) << endl;
    cout << "Disjoint Sets test complete" << endl;

    return 0;
}

