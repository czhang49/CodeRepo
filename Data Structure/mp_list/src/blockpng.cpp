/**
 * @file blockpng.cpp
 * @author Chase Geigle
 * @date Fall 2011
 * @date (Modified) Summer 2014
 */

#include <sstream>
#include "blockpng.h"

namespace blockpng
{

epng::png generate(const epng::png& src, const std::vector<int>& vect, int d)
{
    // error checking: we need to evenly divide the image into d by d blocks
    if (src.width() % d != 0 || src.height() % d != 0)
    {
        std::stringstream ss;
        ss << d << " does not divide either width " << src.width()
           << " or height " << src.height();
        throw std::domain_error{ss.str()};
    }

    // error checking: vector must be of the correct length
    if (static_cast<size_t>((src.width() / d) * (src.height() / d)) !=
        vect.size())
    {
        std::stringstream ss;
        ss << "Vector not of correct length (" << vect.size() << " vs expected "
           << (src.width() / d) * (src.height() / d) << ")";
        throw std::invalid_argument{ss.str()};
    }

    epng::png ret{src.width(), src.height()};

    int numWidth = src.width() / d;

    for (unsigned int i = 0; i < vect.size(); i++)
    {
        int idx = vect[i] % ((src.width() / d) * (src.height() / d) + 1);
        if (idx <= 0)
        {
            std::stringstream ss;
            ss << "Block number " << vect[i] << " is not valid";
            throw std::invalid_argument{ss.str()};
        }

        int x = ((idx - 1) % numWidth) * d;
        int oy = ((idx - 1) / numWidth) * d;

        int y = oy;

        int sy = y + d;

        int nx = (i % numWidth) * d;
        int ny = (i / numWidth) * d;

        for (int j = nx; j < nx + d; j++)
        {
            for (int k = ny; k < ny + d; k++)
            {
                *ret(j, k) = *src(x, y);
                y++;
                if (y == sy)
                {
                    y = oy;
                    x++;
                }
            }
        }
    }

    return ret;
}
}
