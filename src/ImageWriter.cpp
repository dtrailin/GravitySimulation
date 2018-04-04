//
// Created by Denis on 2018-04-03.
//

#include <iostream>
#include "ImageWriter.h"
#include "ppm-io/ppm.hpp"
#include <algorithm>

void ImageWriter::writeToImage(const std::vector<Particle> &input,
                               const std::string &filename,
                               const Configuration &configuration) {

  auto pixel_data = std::vector<uint8_t>(static_cast<size_t >(pow(configuration.gridsize(), 2) * 3), 0);
  for (const auto &particle : input) {
    if (particle.x_pos() >= 0 && particle.x_pos() <= configuration.gridsize() - 1 && particle.x_pos() >= 0
        && particle.y_pos() <= configuration.gridsize() - 1) {
      if (particle.radius() > configuration.small_particle_radius()) {
        int max_rad = static_cast<int>(ceil(particle.radius()));
        int x_i = static_cast<int >(round(particle.x_pos()));
        int y_i = static_cast<int >(round(particle.y_pos()));
        for (int i = x_i - max_rad; i <= x_i + max_rad; i++) {
          for (int j = y_i - max_rad; j <= y_i + max_rad; j++) {
            if ((pow(i - x_i, 2) + pow(j - y_i, 2) <= pow(particle.radius(), 2))
                && ((i >= 0 && i <= configuration.gridsize() - 1 && j >= 0 && j <= configuration.gridsize() - 1))) {
              pixel_data[gridCoordinateToImageIndex(configuration.gridsize(), i, j, blue)] = 255;
            }
          }
        }
      } else {
        int x_i = static_cast<int>(round(particle.x_pos()));
        int y_i = static_cast<int>(round(particle.y_pos()));
        if (pixel_data[
            gridCoordinateToImageIndex(configuration.gridsize(),
                                       x_i,
                                       y_i,
                                       blue)] == 0) {
          uint8_t current_red_value = pixel_data[gridCoordinateToImageIndex(configuration.gridsize(),
                                                                            x_i,
                                                                            y_i,
                                                                            red)];
          if (current_red_value < 255) {
            uint8_t new_value = current_red_value + static_cast<uint8_t>(1);
            pixel_data[gridCoordinateToImageIndex(configuration.gridsize(),
                                                  x_i,
                                                  y_i,
                                                  red)] = new_value;
          }
        }
      }
    }
  }

  thinks::ppm::writeRgbImage(filename, configuration.gridsize(), configuration.gridsize(), pixel_data);
}
int ImageWriter::gridCoordinateToImageIndex(int gridsize, int x, int y, ImageWriter::color color) {
  return (y * gridsize + x) * 3 + color;
}
