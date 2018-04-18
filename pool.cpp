#include <iostream>
#include <vector>
#include <regex>
#include <fstream>

#include <mxx/env.hpp>

#include "src/Particle.h"
#include "src/Simulation.h"
#include "src/ImageWriter.h"
#include "src/Communicator.h"
#include "src/MpiSimulation.h"

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
  Configuration configuration;

  try {
    Configuration::parseConfig(config, &configuration);

  }catch (std::exception &e){
    std::cerr << e.what() << std::endl;
    config.close();
    return 0;
  }
  config.close();

  Communicator comm(Configuration());


  MpiSimulation sim(configuration);
  ImageWriter::writeToImage(sim.run(),
                            argv[2],
                            configuration);



  return 0;
}
