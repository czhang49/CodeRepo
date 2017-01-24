/**
 * @file room_list.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <string>
#include <vector>

#include "room.h"

namespace fileio
{

/**
 * Encapsulates the file operations for reading in the students file.
 */
class room_list
{
  public:
    /**
     * Constructs a new room list reading from the given file.
     *
     * @param filename the file to read from
     */
    room_list(const std::string& filename);

    /**
     * @return whether or not there are more rooms to read
     */
    bool has_next() const;

    /**
     * @return the next room in the list
     */
    Room next();

    /**
     * @return the total number of rooms in the list
     */
    size_t size() const;

  private:
    /// The storage for the room list
    std::vector<std::string> rooms_;
    /// The current position in the list
    size_t idx_;
};
}
