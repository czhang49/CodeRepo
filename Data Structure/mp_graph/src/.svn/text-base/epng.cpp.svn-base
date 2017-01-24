/**
 * @file epng.cpp
 * Implementation of the png class for the EasyPNG library.
 * @see http://zarb.org/~gc/html/libpng.html
 *
 * @author Chase Geigle
 * @date Created: Spring 2012
 * @date Modified: Summer 2012
 * @date Modified: Summer 2014
 */

#include <sstream>
#include <stdexcept>
#include <png.h>

#include "epng.h"

namespace epng
{

rgba_pixel& png::pixel(size_t x, size_t y) const
{
    return pixels_[width_ * y + x];
}

void png::clear()
{
    delete[] pixels_;
    pixels_ = nullptr;
}

void png::blank()
{
    for (size_t y = 0; y < height_; y++)
    {
        for (size_t x = 0; x < width_; x++)
        {
            rgba_pixel& curr = pixel(x, y);
            curr.red = 255;
            curr.green = 255;
            curr.blue = 255;
            curr.alpha = 255;
        }
    }
}

void png::init()
{
    if (pixels_ != nullptr)
        clear();
    width_ = 1;
    height_ = 1;
    pixels_ = new rgba_pixel[1];
    blank();
}

png::png()
{
    pixels_ = nullptr;
    init();
}

png::png(size_t width_arg, size_t height_arg)
{
    width_ = width_arg;
    height_ = height_arg;
    pixels_ = new rgba_pixel[height_ * width_];
    blank();
}

png::png(const std::string& file_name)
{
    pixels_ = nullptr;
    load(file_name);
}

png::png(const png& other)
    : width_{other.width_},
      height_{other.height_},
      pixels_{new rgba_pixel[width_ * height_]}
{
    std::copy(other.pixels_, other.pixels_ + width_ * height_, pixels_);
}

png::png(png&& other)
{
    width_ = other.width_;
    height_ = other.height_;
    pixels_ = other.pixels_;
    other.width_ = 0;
    other.height_ = 0;
    other.pixels_ = nullptr;
}

png::~png()
{
    clear();
}

png& png::operator=(png other)
{
    swap(other);
    return *this;
}

void png::swap(png& other)
{
    std::swap(other.width_, width_);
    std::swap(other.height_, height_);
    std::swap(other.pixels_, pixels_);
}

bool png::pixels_same(const rgba_pixel& first, const rgba_pixel& second) const
{
    return first.red == second.red && first.green == second.green
           && first.blue == second.blue && first.alpha == second.alpha;
}

bool png::operator==(png const& other) const
{
    if (width_ != other.width_ || height_ != other.height_)
        return false;
    for (size_t y = 0; y < height_; y++)
    {
        for (size_t x = 0; x < width_; x++)
        {
            if (!pixels_same(pixel(x, y), other.pixel(x, y)))
                return false;
        }
    }
    return true;
}

bool png::operator!=(png const& other) const
{
    return !(*this == other);
}

void png::check_xy(size_t x, size_t y) const
{
    if (x >= width_ || y >= height_)
    {
        std::stringstream ss;
        ss << "coordinates (" << x << "," << y
           << ") outside valid range of [0, " << width_ - 1 << "] X [0, "
           << height_ - 1 << "]";
        throw std::out_of_range{ss.str()};
    }
}

rgba_pixel* png::operator()(size_t x, size_t y)
{
    check_xy(x, y);
    return &(pixel(x, y));
}

rgba_pixel const* png::operator()(size_t x, size_t y) const
{
    check_xy(x, y);
    return &(pixel(x, y));
}

void png::load(const std::string& file_name)
{
    // unfortunately, we need to break down to the C-code level here, since
    // libpng is written in C itself

    // we need to open the file in binary mode
    FILE* fp = fopen(file_name.c_str(), "rb");
    if (!fp)
    {
        throw std::runtime_error{"failed to open " + file_name};
    }

    // read in the header (max size of 8), use it to validate this as a png file
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        fclose(fp);
        throw std::runtime_error{file_name + " is not a valid png file"};
    }

    // set up libpng structs for reading info
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr,
                                                 nullptr, nullptr);
    if (!png_ptr)
    {
        fclose(fp);
        throw std::runtime_error{"Failed to create libpng read struct"};
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        fclose(fp);
        throw std::runtime_error{"Failed to create libpng info struct"};
    }

    // set error handling to not abort the entire program
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        throw std::runtime_error{"Error reading png metadata"};
    }

    // initialize png reading
    png_init_io(png_ptr, fp);
    // let it know we've already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read in the basic image info
    png_read_info(png_ptr, info_ptr);

    // convert to 8 bits
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    if (bit_depth == 16)
        png_set_strip_16(png_ptr);

    // verify this is in RGBA format, and if not, convert it to RGBA
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    if (color_type != PNG_COLOR_TYPE_RGBA && color_type != PNG_COLOR_TYPE_RGB)
    {
        if (color_type == PNG_COLOR_TYPE_GRAY || color_type
                                                 == PNG_COLOR_TYPE_GRAY_ALPHA)
        {
            if (bit_depth < 8)
                png_set_expand(png_ptr);
            png_set_gray_to_rgb(png_ptr);
        }
        if (color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(png_ptr);
    }
    // convert tRNS to alpha channel
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);

    size_t width = png_get_image_width(png_ptr, info_ptr);
    size_t height = png_get_image_height(png_ptr, info_ptr);
    rgba_pixel* newpix = nullptr;
    png_byte* row = nullptr;

    png_read_update_info(png_ptr, info_ptr);

    // begin reading in the image
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        delete[] newpix;
        delete[] row;
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        throw std::runtime_error{"Error reading image with libpng"};
    }

    int bpr = png_get_rowbytes(png_ptr, info_ptr); // number of bytes in a row

    // initialize our image storage
    newpix = new rgba_pixel[height * width];
    row = new png_byte[bpr];

    int numchannels = png_get_channels(png_ptr, info_ptr);
    for (size_t y = 0; y < height; y++)
    {
        png_read_row(png_ptr, row, nullptr);
        png_byte* pix = row;
        for (size_t x = 0; x < width; x++)
        {
            rgba_pixel& px = newpix[width * y + x];
            if (numchannels == 1 || numchannels == 2)
            {
                // monochrome
                unsigned char color = (unsigned char)*pix++;
                px.red = color;
                px.green = color;
                px.blue = color;
                if (numchannels == 2)
                    px.alpha = (unsigned char)*pix++;
                else
                    px.alpha = 255;
            }
            else if (numchannels == 3 || numchannels == 4)
            {
                px.red = (unsigned char)*pix++;
                px.green = (unsigned char)*pix++;
                px.blue = (unsigned char)*pix++;
                if (numchannels == 4)
                    px.alpha = (unsigned char)*pix++;
                else
                    px.alpha = 255;
            }
        }
    }

    // replace image
    delete[] pixels_;
    pixels_ = newpix;
    width_ = width;
    height_ = height;

    // cleanup
    delete[] row;
    png_read_end(png_ptr, nullptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);
}

void png::save(const std::string& file_name)
{
    FILE* fp = fopen(file_name.c_str(), "wb");
    if (!fp)
    {
        throw std::runtime_error{"Failed to open file " + file_name};
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                                  nullptr, nullptr, nullptr);
    if (!png_ptr)
    {
        fclose(fp);
        throw std::runtime_error{"Failed to create libpng struct"};
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_write_struct(&png_ptr, nullptr);
        fclose(fp);
        throw std::runtime_error{"Failed to create libpng info struct"};
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        throw std::runtime_error{"Error initializing libpng io"};
    }

    png_init_io(png_ptr, fp);

    // write header
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        throw std::runtime_error{"Error writing image header"};
    }
    png_set_IHDR(png_ptr, info_ptr, width_, height_, 8,
                 PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    // write image
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        throw std::runtime_error{"Failed to write image"};
    }

    int bpr = png_get_rowbytes(png_ptr, info_ptr);
    png_byte* row = new png_byte[bpr];
    for (size_t y = 0; y < height_; y++)
    {
        for (size_t x = 0; x < width_; x++)
        {
            png_byte* pix = &(row[x * 4]);
            pix[0] = pixel(x, y).red;
            pix[1] = pixel(x, y).green;
            pix[2] = pixel(x, y).blue;
            pix[3] = pixel(x, y).alpha;
        }
        png_write_row(png_ptr, row);
    }
    delete[] row;
    png_write_end(png_ptr, nullptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
}

size_t png::width() const
{
    return width_;
}

size_t png::height() const
{
    return height_;
}

void png::resize(size_t width_arg, size_t height_arg)
{
    if (width_arg == width_ && height_arg == height_)
        return;

    // any new pixels will be initialized to be white by default pixel
    // constructor
    rgba_pixel* arr = new rgba_pixel[width_arg * height_arg];

    // copy over the pixels from the old image
    for (size_t x = 0; x < std::min(width_arg, width_); x++)
        for (size_t y = 0; y < std::min(height_arg, height_); y++)
            arr[x + y * width_arg] = pixel(x, y);

    delete[] pixels_;
    pixels_ = arr;
    width_ = width_arg;
    height_ = height_arg;
}
}
