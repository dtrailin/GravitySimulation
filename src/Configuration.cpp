//
// Created by Denis on 2018-04-02.
//

#include <iostream>
#include "Configuration.h"

bool Configuration::addValue(const std::string &key, const std::string &value) {
  const auto &iterator = conditions.find(key);
  if (iterator != conditions.end()) {
    iterator->second(stof(value));
    conditions.erase(key);
    return true;
  }
  std::cerr << key << " has either already been added or is an invalid option" << std::endl;

  return false;
}

bool Configuration::addLargeParticle(const std::string &radius, const std::string &mass, const std::string &x_pos,
                                     const std::string &y_pos) {
  if (conditions.size() > 0) {
    std::cout << " Large particles must be defined last" << std::endl;
    return false;
  }
  double radius_f = stof(radius);
  double mass_f = stof(mass);
  double x_pos_f = stof(x_pos);
  double y_pos_f = stof(y_pos);
  if (mass_f < 0) {
    std::cerr << "Mass must be greater than zero" << std::endl;
    return false;
  }
  if (radius_f < 0) {
    std::cerr << "Radius must be greater than zero" << std::endl;
    return false;
  }
  if (x_pos_f < 0 || x_pos_f > gridsize_ || y_pos_f < 0 || y_pos_f > gridsize_) {
    std::cerr << "Position must be within grid bounds" << std::endl;
    return false;
  }

  large_particles_.push_back(Particle(radius_f, mass_f, x_pos_f, y_pos_f, large_particles_.size(), false));

  return true;
}

std::ostream &operator<<(std::ostream &os, const Configuration &configuration) {
  os << "timeslots_: " << configuration.timeslots_ << " horizon_: " << configuration.horizon_ << " gridsize_: "
     << configuration.gridsize_ << " number_small_particles_: " << configuration.number_small_particles_
     << " number_large_particles_: " << configuration.number_large_particles_ << " small_particle_mass_: "
     << configuration.small_particle_mass_ << " timestep_: " << configuration.timestep_ << " large_particles_: "
     << std::endl;
  for (const auto &i:  configuration.large_particles_)
    os << i << std::endl;

  return os;
}
int Configuration::timeslots() const {
  return timeslots_;
}
int Configuration::horizon() const {
  return horizon_;
}
int Configuration::gridsize() const {
  return gridsize_;
}
int Configuration::number_small_particles() const {
  return number_small_particles_;
}
int Configuration::number_large_particles() const {
  return number_large_particles_;
}
double Configuration::small_particle_mass() const {
  return small_particle_mass_;
}
double Configuration::timestep() const {
  return timestep_;
}
const std::vector<Particle> &Configuration::large_particles() const {
  return large_particles_;
}
double Configuration::small_particle_radius() const {
  return small_particle_radius_;
}
