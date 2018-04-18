//
// Created by Denis on 2018-04-03.
//

#ifndef PROJECT2_IMAGEWRITER_H
#define PROJECT2_IMAGEWRITER_H

#include <vector>
#include "Particle.h"
#include "Configuration.h"
class ImageWriter {

 public:
  static void writeToImage(const std::vector<Particle> &input, const std::string &filename, int x_size, int y_size);
  static void writeToImage(const std::vector<Particle> &input, const std::string &filename, int total_size);

 private:
  enum color { red = 0, green = 1, blue = 2 };
  static int gridCoordinateToImageIndex(int y_size, int x, int y, ImageWriter::color color);

};

#endif //PROJECT2_IMAGEWRITER_H
