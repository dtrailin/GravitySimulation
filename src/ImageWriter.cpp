//
// Created by Denis on 2018-04-03.
//

#include "ImageWriter.h"

#include <iostream>
#include <algorithm>

#include <ppm.hpp>

void ImageWriter::writeToImage(const std::vector<Particle> &input, const std::string &filename, int x_size, int y_size) {

  auto pixel_data = std::vector<uint8_t>(static_cast<size_t >(x_size * y_size * 3), 0);
  for (const auto &particle : input) {

    int x_i = static_cast<int>(floor(particle.x_pos()));
    int y_i = static_cast<int>(floor(particle.y_pos()));
    if (x_i >= 0 && x_i <= x_size && y_i >= 0 && y_i <= y_size) {
      if (!particle.is_small()) {
        int max_rad = static_cast<int>(ceil(particle.radius()));
        for (int i = x_i - max_rad; i <= x_i + max_rad; i++) {
          for (int j = y_i - max_rad; j <= y_i + max_rad; j++) {
            if ((pow(i - x_i, 2) + pow(j - y_i, 2) <= pow(particle.radius(), 2))
                && (i >= 0 && i <= x_size  && j >= 0 && j <= y_size)) {
              pixel_data[gridCoordinateToImageIndex(y_size, i, j, blue)] = 255;
            }
          }
        }
      } else {
        if (pixel_data[gridCoordinateToImageIndex(y_size, x_i, y_i, blue)] == 0) {
          uint8_t current_red_value = pixel_data[gridCoordinateToImageIndex(y_size,
                                                                            x_i,
                                                                            y_i,
                                                                            red)];
          if (current_red_value < 255) {
            uint8_t new_value = current_red_value + static_cast<uint8_t>(1);
            pixel_data[gridCoordinateToImageIndex(y_size,
                                                  x_i,
                                                  y_i,
                                                  red)] = new_value;
          }
        }
      }
    }
  }

  thinks::ppm::writeRgbImage(filename, static_cast<const size_t>(x_size), static_cast<const size_t>(y_size), pixel_data);
}
int ImageWriter::gridCoordinateToImageIndex(int y_size, int x, int y, ImageWriter::color color) {
  return (y * y_size + x) * 3 + color;
}
void ImageWriter::writeToImage(const std::vector<Particle> &input, const std::string &filename, int total_size) {
  writeToImage(input,filename, total_size,total_size);
}
