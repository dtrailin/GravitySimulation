//
// Created by Denis on 2018-03-30.
//

#ifndef PROJECT2_SIMULATION_H
#define PROJECT2_SIMULATION_H

#include <vector>
#include "Particle.h"
#include "ForceVector.h"
#include "Configuration.h"

class Simulation {
 public:

  Simulation(const Configuration &configuration);

  static ForceVector gravitationalForce(const Particle &p1, const Particle &p2);

  void nextStep();

  std::vector<Particle> run();
 private:
  Configuration configuration_;
  std::vector<Particle> particles_;
  std::vector<Particle> last_state_;
  static const int kGravitationalConstant = 5000;

};

#endif //PROJECT2_SIMULATION_H
