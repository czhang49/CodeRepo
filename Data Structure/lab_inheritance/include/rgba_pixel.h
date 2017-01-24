/**
 * @file rgba_pixel.h
 * Definition of the rgba_pixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */

#ifndef EPNG_RGBA_PIXEL_H_
#define EPNG_RGBA_PIXEL_H_

#include <cstdint>
#include <ostream>

namespace epng
{

/**
 * Represents a single pixel in an image.
 */
struct rgba_pixel
{
    uint8_t red;   /**< Byte for the red component of the pixel. */
    uint8_t green; /**< Byte for the green component of the pixel. */
    uint8_t blue;  /**< Byte for the blue component of the pixel. */
    uint8_t alpha; /**< Byte for the alpha component of the pixel. */

    /**
     * Constructs a default rgba_pixel. A default pixel is completely
     * opaque (non-transparent) and white. Opaque implies that the
     * alpha component of the pixel is 255. Lower values are
     * transparent.
     */
    rgba_pixel();

    /**
     * Constructs an opaque rgba_pixel with the given red, green, blue
     * color values. The alpha component of the pixel constructed
     * should be 255.
     * @param red Red component for the new pixel.
     * @param green Green component for the new pixel.
     * @param blue Blue component for the new pixel.
     */
    rgba_pixel(uint8_t red, uint8_t green, uint8_t blue);

    /** @cond POST_MP1 */

    /**
     * Constructs an rgba_pixel with the given red, green, blue, and
     * alpha components.
     * @param red Red component for the new pixel.
     * @param green Green component for the new pixel.
     * @param blue Blue component for the new pixel.
     * @param alpha Alpha component for the new pixel (controls
     * transparency).
     */
    rgba_pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    /** @endcond */
};
}

/** @cond POST_MP1 */

/**
 * Stream operator that allows pixels to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param pixel Pixel to write to the stream.
 */
std::ostream& operator<<(std::ostream& out, const epng::rgba_pixel& pixel);

/**
 * Equality operator.
 * @param other Other pixel to check equality with.
 */
bool operator==(const epng::rgba_pixel& lhs, const epng::rgba_pixel& rhs);

/**
 * Inequality operator.
 * @param other Other pixel to check inequality with.
 */
bool operator!=(const epng::rgba_pixel& lhs, const epng::rgba_pixel& rhs);

/**
 * Less than operator. Provided to give some ordering notion to
 * rgba_pixels.
 * @param other Other pixel to compare with.
 */
bool operator<(const epng::rgba_pixel& lhs, const epng::rgba_pixel& rhs);

/** @endcond */
#endif
