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
  static void writeToImage(const std::vector<Particle> &input,
                           const std::string &filename,
                           const Configuration &configuration);
 private:
  enum color { red = 0, green = 1, blue = 2 };
  static int gridCoordinateToImageIndex(int gridsize, int x, int y, ImageWriter::color color);

};

#endif //PROJECT2_IMAGEWRITER_H
