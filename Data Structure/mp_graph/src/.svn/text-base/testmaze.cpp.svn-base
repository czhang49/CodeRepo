/**
 * @file testmaze.cpp
 * Performs basic tests of maze.
 *
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "epng.h"

int main()
{
    cs225::maze m{10, 10};
    std::cout << "constructor complete" << std::endl;

    auto unsolved = m.draw();
    unsolved.save("images/unsolved.png");
    std::cout << "draw complete" << std::endl;

	auto sol = m.solve();
    std::cout << "solve complete" << std::endl;




    auto solved = m.draw_with_solution();
    solved.save("images/solved.png");
    std::cout << "draw_with_solution complete" << std::endl;

    return 0;
}

