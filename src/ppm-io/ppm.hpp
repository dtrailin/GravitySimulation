#ifndef THINKS_PPM_PPM_HPP_INCLUDED
#define THINKS_PPM_PPM_HPP_INCLUDED

#include <cassert>
#include <cstdint>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace thinks {
namespace ppm {

namespace detail {

inline
void writeRgbImage(
    std::ostream &os,
    std::size_t const width,
    std::size_t const height,
    std::vector<std::uint8_t> const &pixel_data) {
  using namespace std;

  if (width == 0) {
    throw runtime_error("width must be non-zero");
  }

  if (height == 0) {
    throw runtime_error("height must be non-zero");
  }

  if (pixel_data.size() != width * height * 3) {
    throw runtime_error("pixel data must match width and height");
  }

  // Write header.
  auto const magic_number = string("P6");
  auto const max_value = string("255");
  os << magic_number << "\n"
     << width << " " << height << "\n"
     << max_value
     << "\n"; // Marks beginning of pixel data.

  // Write pixel data.
  os.write(reinterpret_cast<char const *>(pixel_data.data()), pixel_data.size());
}

//! See std::ostream overload version above.
//!
//! Throws an std::runtime_error if file cannot be opened.
inline
void writeRgbImage(
    std::string const &filename,
    std::size_t const width,
    std::size_t const height,
    std::vector<std::uint8_t> const &pixel_data) {

  std::ofstream ofs (filename,  std::ios::binary);
  if (ofs.fail()) {
    std::stringstream ss;
    ss << "cannot open file '" << filename << "'";
    throw std::runtime_error(ss.str());
  }


  writeRgbImage(ofs, width, height, pixel_data);
  ofs.close();
}

} // namespace ppm
} // namespace thinks

#endif // THINKS_PPM_PPM_HPP_INCLUDED
