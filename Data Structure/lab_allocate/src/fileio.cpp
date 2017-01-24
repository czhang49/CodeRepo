/**
 * @file fileio.cpp
 */

#include <fstream>
#include "fileio.h"

namespace fileio
{

std::vector<std::string> read_lines(const std::string& file)
{
    std::vector<std::string> lines;

    std::ifstream input{file};
    std::string line;
    while (std::getline(input, line))
        lines.push_back(std::move(line));

    return lines;
}
}
