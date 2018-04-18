//
// Created by Denis on 2018-03-30.
//

#include <cmath>
#include "Simulation.h"
#include <random>
#include <iostream>

Simulation::Simulation(const Configuration &configuration)
    : configuration_(configuration), last_state_(configuration_.large_particles()) {
  std::random_device rd;
  std::default_random_engine generator(rd()); // rd() provides a random seed
  std::uniform_real_distribution<double> distribution(0, configuration.gridsize() - 1);
  last_state_.reserve(static_cast<unsigned long>(configuration.number_small_particles()));

  for (int i = 0; i < configuration.number_small_particles(); ++i) {
    last_state_.push_back(Particle(configuration_.small_particle_radius(),
                                   configuration_.small_particle_mass(),
                                   distribution(generator),
                                   distribution(generator),
                                   last_state_.size(),
                                   true));

  }

  particles_ = last_state_;
}

void Simulation::nextStep() {
  for (const auto &particle1 : last_state_) {
    calculateForcesOnParticle(particle1, &particles_[particle1.id()], last_state_);
  }

  last_state_.swap(particles_);
}
void Simulation::calculateForcesOnParticle(const Particle &particle1, Particle *out, const std::vector<Particle> &last_state) const {
  ForceVector total(0, 0);
  for (const auto &particle2 : last_state) {
      if (particle1.id() != particle2.id()) {
        total += gravitationalForce(particle1, particle2);
      }
    }
  double timestep = configuration_.timestep();
  double y_dist = 0.5f * (total.getY() / particle1.mass()) * timestep * timestep;
  double x_dist = 0.5f * (total.getX() / particle1.mass()) * timestep * timestep;
  out->set_x(particle1.x_pos() + x_dist);
  out->set_y(particle1.y_pos() + y_dist);
}

ForceVector Simulation::gravitationalForce(const Particle &p1, const Particle &p2) {
  auto distance = sqrt(pow(p1.x_pos() - p2.x_pos(), 2) + pow(p1.y_pos() - p2.y_pos(), 2));
  if (distance != 0) {
    double gravitational_force = (kGravitationalConstant * p1.mass() * p2.mass()) / pow(distance, 2);
    double f_x = gravitational_force * ((p2.x_pos() - p1.x_pos()) / distance);
    double f_y = gravitational_force * ((p2.y_pos() - p1.y_pos()) / distance);
    return {f_x, f_y};
  } else {
    return {0, 0};
  }

}
std::vector<Particle> Simulation::run() {
  for (int i = 0; i < configuration_.timeslots(); ++i) {
    nextStep();
    std::cout << "running iteration " << i + 1 << std::endl;
    for (int j = 0; j < configuration_.number_large_particles(); ++j) {
      std::cout << last_state_[j] << std::endl;
    }
  }
  return last_state_;
}

