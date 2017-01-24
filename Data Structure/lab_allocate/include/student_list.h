/**
 * @file student_list.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <string>
#include <vector>

namespace fileio
{

/**
 * Encapsulates the file operations for reading in the students file.
 */
class student_list
{
  public:
    /**
     * Constructs a new student_list over the given file.
     *
     * @param file the file to read
     */
    student_list(const std::string& file);

    /**
     * @return whether there are more students to read
     */
    bool has_next() const;

    /**
     * @return the next student in the list
     */
    std::string next();

    /**
     * @return the total number of students in the list
     */
    size_t size() const;

  private:
    /// The storage for the student list
    std::vector<std::string> students_;
    /// The current position in the list
    size_t idx_;
};
}
