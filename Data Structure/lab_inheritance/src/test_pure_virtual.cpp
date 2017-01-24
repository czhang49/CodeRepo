/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 */

#include <iostream>

#include "truck.h"

using namespace std;

int main()
{
	epng::png canvas{128, 128};

    const Vector2 truck_center{64, 64};

    /* TODO: Why can't I construct a new Truck?  Is should be a valid Drawable.
     * Could it be missing something that would prevent it from being
     * constructed?
     */
    Drawable* truck = new Truck{truck_center};

    truck->draw(canvas);

    canvas.save("test_pure_virtual.png");

    delete truck;
    return 0;
}
