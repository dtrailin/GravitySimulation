//
// Created by Denis on 2018-04-18.
//

#include "MpiSimulation.h"
MpiSimulation::MpiSimulation(const Configuration &configuration, Communicator &communicator) : Simulation(
    configuration), communicator_(communicator) {}

void MpiSimulation::nextStep() {
  for (const auto &particle1 : aggregate_state_) {
    if (particle1.x_pos() >= 0 && particle1.y_pos() >= 0 && particle1.x_pos() < configuration_.gridsize() - 1
        && particle1.y_pos() < configuration_.gridsize() - 1) {
      Particle p(particle1);
      calculateForcesOnParticle(particle1, &p, aggregate_state_);
      particles_.push_back(p);
    }
  }
}

std::vector<Particle> MpiSimulation::run() {

  for (int i = 0; i < configuration_.timeslots(); ++i) {
    communicator_.synchronizeWithNeighbors(particles_);
    aggregate_state_.swap(particles_);
    nextStep();
    aggregate_state_.clear();
    std::cout << "running iteration " << i + 1 << " with particles in instance: " << particles_.size() << std::endl;
  }
  return particles_;
}


