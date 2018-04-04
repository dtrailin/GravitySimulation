//
// Created by Denis on 2018-04-02.
//

#ifndef PROJECT2_CONFIGURATION_H
#define PROJECT2_CONFIGURATION_H

#include <string>
#include <functional>
#include <unordered_map>
#include <ostream>
#include <vector>
#include "Particle.h"

class Configuration {
 public:
  int timeslots() const;
  int horizon() const;
  int gridsize() const;
  int number_small_particles() const;
  int number_large_particles() const;
  double small_particle_mass() const;
  double timestep() const;
  double small_particle_radius() const;
  const std::vector<Particle> &large_particles() const;
  bool addValue(const std::string &key, const std::string &value);

  bool addLargeParticle(const std::string &radius, const std::string &mass,
                        const std::string &x_pos, const std::string &y_pos);

  friend std::ostream &operator<<(std::ostream &os, const Configuration &configuration);

 private:
  int timeslots_, horizon_, gridsize_, number_small_particles_, number_large_particles_;
  double small_particle_mass_, small_particle_radius_, timestep_;
  std::vector<Particle> large_particles_;
  std::unordered_map<std::string, std::function<void(double)>> conditions{
      {"TimeSlots", [=](double x) { timeslots_ = static_cast<int>(x); }},
      {"TimeStep", [=](double x) { timestep_ = x; }},
      {"Horizon", [=](double x) { horizon_ = static_cast<int>(x); }},
      {"GridSize", [=](double x) { gridsize_ = static_cast<int>(x); }},
      {"NumberOfSmallParticles", [=](
          double x) { number_small_particles_ = static_cast<int>(x); }},
      {"SmallParticleMass", [=](double x) { small_particle_mass_ = x; }},
      {"SmallParticleRadius", [=](double x) { small_particle_radius_ = x; }},

      {"NumberOfLargeParticles", [=](
          double x) { number_large_particles_ = static_cast<int>(x); }}};

};

#endif //PROJECT2_CONFIGURATION_H
