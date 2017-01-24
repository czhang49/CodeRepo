/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "epng.h"

namespace color
{

using namespace epng;

const rgba_pixel WHITE{255, 255, 255};
const rgba_pixel BLACK{0, 0, 0};
const rgba_pixel GRAY{149, 145, 140};
const rgba_pixel RED{255, 0, 0};
const rgba_pixel ORANGE{255, 127, 0};
const rgba_pixel YELLOW{255, 255, 0};
const rgba_pixel GREEN{0, 255, 0};
const rgba_pixel TURQUOISE{0, 255, 255};
const rgba_pixel BLUE{0, 0, 255};
const rgba_pixel PURPLE{127, 0, 255};
const rgba_pixel PINK{251, 126, 253};

} // namespace color

#endif // COLOR_H_
