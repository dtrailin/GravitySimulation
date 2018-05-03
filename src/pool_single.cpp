#include <iostream>
#include <vector>
#include <regex>
#include <fstream>

#include "Particle.h"
#include "Simulation.h"
#include "ImageWriter.h"


int main(int argc, char **argv) {

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

  }catch (std::exception &e){
    std::cerr << e.what() << std::endl;
    config.close();
    return 0;
  }
  config.close();

  Simulation sim(configuration);
  ImageWriter::writeToImage(sim.run(), argv[2], configuration.gridsize());
  return 0;
}
