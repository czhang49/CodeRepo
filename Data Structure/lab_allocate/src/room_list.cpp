/**
 * @file room_list.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "fileio.h"
#include "room_list.h"

namespace fileio
{

namespace
{

std::vector<std::string> tokenize(const std::string& str, char delim)
{
    // credit: Jack Toole
    std::vector<std::string> args;

    size_t start = 0;
    size_t end;
    for (end = str.find(delim); end != str.npos; end = str.find(delim, start))
    {
        args.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    args.push_back(str.substr(start, str.size() - start));

    return args;
}

Room parse_room(const std::string& str)
{
    auto split = tokenize(str, ',');
    auto name = split[0];
    int capacity = std::stol(split[1]) / 2;
    Room r(name, capacity);
    return r;
}
}

room_list::room_list(const std::string& filename) : idx_{0}
{
    rooms_ = fileio::read_lines(filename);
}

bool room_list::has_next() const
{
    return idx_ < rooms_.size();
}

Room room_list::next()
{
    return parse_room(rooms_[idx_++]);
}

size_t room_list::size() const
{
    return rooms_.size();
}
}
