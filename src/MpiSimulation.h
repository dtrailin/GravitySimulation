//
// Created by Denis on 2018-04-18.
//

#ifndef PROJECT2_MPISIMULATION_H
#define PROJECT2_MPISIMULATION_H

#include "Simulation.h"
#include "Communicator.h"
class MpiSimulation : public Simulation {
 public:
  MpiSimulation(const Configuration &configuration, Communicator &communicator);
  void nextStep() override;
  std::vector<Particle> run() override;
 private:
  std::vector<Particle> aggregate_state_;
  Communicator &communicator_;
};

#endif //PROJECT2_MPISIMULATION_H
