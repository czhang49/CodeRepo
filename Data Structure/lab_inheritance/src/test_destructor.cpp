/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 */

#include <iostream>

#include "png.h"
#include "color.h"
#include "shape.h"
#include "triangle.h"
#include "vector2.h"

using namespace std;

int main()
{
    const int canvas_width = 128;
    const int canvas_height = 128;

    epng::png canvas{canvas_width, canvas_height};

    const epng::rgba_pixel triangle_color = color::ORANGE;
    Shape* triangle = new Triangle{triangle_color,  Vector2{32, 32},
                                   Vector2{64, 64}, Vector2{32, 64}};

    triangle->draw(canvas);

    canvas.save("test_destructor.png");

    /* TODO: Why is this leaking memory?  Triangle does have a valid
     * destructor!?
     * Can you stop it from leaking WITHOUT changing triangle's type from a
     * Shape pointer to a Triangle pointer type? */
    delete triangle;
    triangle = nullptr;

    return 0;
}
