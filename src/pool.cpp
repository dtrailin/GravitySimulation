#include <iostream>
#include <vector>
#include <regex>
#include <fstream>

#include <mxx/env.hpp>

#include "Particle.h"
#include "Simulation.h"
#include "ImageWriter.h"
#include "Communicator.h"
#include "MpiSimulation.h"

std::vector<Particle> particles;

int main(int argc, char **argv) {
  mxx::env e(argc, argv);

  if (argc != 3) {
    std::cerr << "Spec file and output required" << std::endl;
    return 0;
  }

  std::ifstream config(argv[1]);
  if (!config) {
    std::cerr << "File not found" << std::endl;
    return 1;
  }
  Configuration configuration;

  try {
    Configuration::parseConfig(config, &configuration);

  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    config.close();
    return 0;
  }
  config.close();

  Communicator communicator(configuration);
  MpiSimulation sim(configuration, communicator);
  const std::vector<Particle> &collected = communicator.collectAll(sim.run());
  if (collected.size() > 0) {
    std::cout << "final # of particles: " << collected.size() <<std::endl;
    const std::pair<int, int> &dimensions = communicator.getDimensions();
    ImageWriter::writeToImage(collected,
                              argv[2],
                              dimensions.first * configuration.gridsize(),
                              dimensions.second * configuration.gridsize());

  }

  return 0;
}
