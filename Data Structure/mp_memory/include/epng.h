/**
 * @file png.h
 * Definition of the png class for the EasyPNG library.
 * @see http://zarb.org/~gc/html/libpng.html
 *
 * @author Chase Geigle
 * @date Created: Spring 2012
 * @date Modified: Summer 2012
 * @date Modified by Sean Massung in Summer 2013, s/int/size_t
 * @date Modified: Summer 2014
 */
#ifndef EPNG_PNG_H_
#define EPNG_PNG_H_

#include <string>
#include "rgba_pixel.h"

namespace epng
{

/**
 * Represents an entire png formatted image.
 */
class png
{
  public:
    /**
     * Creates a default png image (that is, a 1x1 opaque white image).
     */
    png();

    /**
     * Creates a default png image of the desired dimensions (that is,
     * a width x height opaque white image).
     * @param width Width of the new image.
     * @param height Height of the new image.
     */
    png(size_t width, size_t height);

    /**
     * Creates a png image by reading a file in from disk.
     * @param file_name Name of the file to be read in to the image.
     */
    png(const std::string& file_name);

    /**
     * Copy constructor: creates a new png image that is a copy of
     * another.
     * @param other png to be copied.
     */
    png(const png& other);

    /**
     * Move constructor.
     * @param other the png to move into this one
     */
    png(png&& other);

    /**
     * Destructor: frees all memory associated with a given png object.
     * Invoked by the system.
     */
    ~png();

    /**
     * Assignment operator for setting two pngs equal to one another.
     * @param other Image to copy into the current image.
     * @return The current image for assignment chaining.
     */
    png& operator=(png other);

    /**
     * Equality operator: checks if two images are the same.
     * @param other Image to be checked.
     * @return Whether the current image is equal to the other image.
     */
    bool operator==(const png& other) const;

    /**
     * Inequality operator: checks if two images are different.
     * @param other Image to be checked.
     * @return Whether the current image differs from the other image.
     */
    bool operator!=(const png& other) const;

    /**
     * Non-const pixel access operator. Gets a pointer to the pixel at
     * the given coordinates in the image. (0,0) is the upper left
     * corner. This pointer allows the image to be changed.
     * @param x X-coordinate for the pixel pointer to be grabbed from.
     * @param y Y-coordinate for the pixel pointer to be grabbed from.
     * @return A pointer to the pixel at the given coordinates.
     */
    rgba_pixel* operator()(size_t x, size_t y);

    /**
     * Const pixel access operator. Const version of the previous
     * operator(). Does not allow the image to be changed via the
     * pointer.
     * @param x X-coordinate for the pixel pointer to be grabbed from.
     * @param y Y-cooridnate for the pixel pointer to be grabbed from.
     * @return A pointer to the pixel at the given coordinates (can't
     * change the pixel through this pointer).
     */
    const rgba_pixel* operator()(size_t x, size_t y) const;

    /**
     * Reads in a png image from a file.
     * Overwrites any current image content in the png. In the event of
     * failure, the image's contents are unmodified and an exception is
     * thrown.
     * @param file_name Name of the file to be read from.
     */
    void load(const std::string& file_name);

    /**
     * Writes a png image to a file. If an error occurs, an exception will
     * be thrown.
     * @param file_name Name of the file to write to.
     */
    void save(const std::string& file_name);

    /**
     * Gets the width of this image.
     * @return Width of the image.
     */
    size_t width() const;

    /**
     * Gets the height of this image.
     * @return Height of the image.
     */
    size_t height() const;

    /**
     * Resizes the image to the given coordinates. Attempts to preserve
     * existing pixel data in the image when doing so, but will crop if
     * necessary. No pixel interpolation is done.
     * @param width New width of the image.
     * @param height New height of the image.
     */
    void resize(size_t width, size_t height);

    /**
     * Swaps the image with the given one.
     *
     * @param other The image to swap with
     */
    void swap(png& other);

  private:
    // storage
    size_t width_;
    size_t height_;
    rgba_pixel* pixels_;

    // private helper functions
    bool read_file(const std::string& file_name);
    void clear();
    void blank();
    void init();
    void check_xy(size_t x, size_t y) const;
    bool pixels_same(const rgba_pixel& first, const rgba_pixel& second) const;
    rgba_pixel& pixel(size_t x, size_t y) const;
};

}
#endif
