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

  virtual void nextStep();

  virtual std::vector<Particle> run();
 protected:
  Configuration configuration_;
  static const int kGravitationalConstant = 5000;
  void calculateForcesOnParticle(const Particle &particle1, Particle *out, const std::vector<Particle> &last_state) const;
  std::vector<Particle> particles_;

 private:
  std::vector<Particle> last_state_;
};

#endif //PROJECT2_SIMULATION_H
