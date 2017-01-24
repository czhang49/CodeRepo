/**
 * @file fileio.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <string>
#include <vector>

/**
 * Utility functions for reading students/rooms from files.
 * @note There are NO bugs in fileio or its nested classes
 */
namespace fileio
{

/**
 * Reads a given file into a vector of lines.
 * @param file the file to read
 * @return a vector containing every line of the file
 */
std::vector<std::string> read_lines(const std::string& file);
}
