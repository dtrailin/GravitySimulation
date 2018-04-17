#include <iostream>
#include <vector>

#include <regex>

#include <fstream>
#include <mxx/env.hpp>

#include "src/Particle.h"
#include "src/Simulation.h"
#include "src/ImageWriter.h"
#include "src/Communication.h"

std::vector<Particle> particles;

int main(int argc, char **argv) {
  mxx::env e(argc,argv);

  if (argc != 3) {
    std::cerr << "Spec file and output required" << std::endl;
    return 0;
  }

  std::ifstream config(argv[1]);
  if (!config) {
    std::cerr << "File not found" << std::endl;
    return 1;
  }
  std::regex options("([^\\s]+): ([^\\s]+).*");
  std::regex planets("([0-9,.]+) ([0-9,.]+) ([0-9,.]+) ([0-9,.]+)");

  Configuration configuration;

  std::string line;
  while (std::getline(config, line)) {
    std::istringstream is_line(line);
    std::smatch matches;

    if (std::regex_search(line, matches, options)) {
      if (!configuration.addValue(matches[1], matches[2])) {
        return 0;
      }
    } else if (std::regex_search(line, matches, planets)) {
      if (!configuration.addLargeParticle(matches[1], matches[2], matches[3], matches[4])) {
        return 0;
      }

    }
  }
  config.close();
  std::cout << configuration << std::endl;

  Communication comm;

  comm.send_to_neighbors(configuration.large_particles());

  Simulation sim(configuration);
  ImageWriter::writeToImage(sim.run(),
                            argv[2],
                            configuration);
  return 0;
}
