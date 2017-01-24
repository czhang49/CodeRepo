/**
 * @file rgbapixel.cpp
 * Implementation of the rgba_pixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */

#include "rgba_pixel.h"

namespace epng
{

rgba_pixel::rgba_pixel() : red(255), green(255), blue(255), alpha(255)
{
    /* nothing */
}

rgba_pixel::rgba_pixel(uint8_t r, uint8_t g, uint8_t b)
    : red(r), green(g), blue(b), alpha(255)
{
    /* nothing */
}

rgba_pixel::rgba_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : red(r), green(g), blue(b), alpha(a)
{
    /* nothing */
}
}

std::ostream& operator<<(std::ostream& out, const epng::rgba_pixel& pixel)
{
    out << "(" << static_cast<int>(pixel.red) << "," << static_cast
        <int>(pixel.green) << "," << static_cast<int>(pixel.blue) << ")";
    if (pixel.alpha != 255)
        out << " a:" << static_cast<int>(pixel.alpha);
    return out;
}

bool operator!=(const epng::rgba_pixel& lhs, const epng::rgba_pixel& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const epng::rgba_pixel& lhs, const epng::rgba_pixel& rhs)
{
    if (lhs.red != rhs.red)
        return lhs.red < rhs.red;
    if (lhs.green != rhs.green)
        return lhs.green < rhs.green;
    return lhs.blue < rhs.blue;
}
bool operator==(const epng::rgba_pixel& lhs, const epng::rgba_pixel& rhs)
{
    return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue
           && lhs.alpha == rhs.alpha;
}
