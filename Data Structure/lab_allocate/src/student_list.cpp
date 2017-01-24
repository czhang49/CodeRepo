/**
 * @file student_list.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <algorithm>

#include "fileio.h"
#include "student_list.h"

namespace fileio
{

student_list::student_list(const std::string& file)
    : idx_{0}
{
    students_ = fileio::read_lines(file);
    std::stable_sort(students_.begin(), students_.end());
}

bool student_list::has_next() const
{
    return idx_ < students_.size();
}

std::string student_list::next()
{
    return students_[idx_++];
}

size_t student_list::size() const
{
    return students_.size();
}

}
