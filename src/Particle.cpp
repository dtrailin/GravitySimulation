//
// Created by Denis on 2018-03-29.
//

#include "Particle.h"

Particle::Particle(double radius_,
                   double mass_,
                   double x_pos,
                   double y_pos,
                   unsigned long id,
                   bool is_small)
    : radius_(radius_), mass_(mass_),
      x_(x_pos), y_(y_pos),
      id_(id), is_small_(is_small) {}

std::ostream &operator<<(std::ostream &os, const Particle &particle) {
  os << "id_: " << particle.id_ << " radius_: " << particle.radius_ << " mass_: " << particle.mass_ << " x_: "
     << particle.x_ << " y_: "
     << particle.y_;
  return os;
}
Particle::Particle(particle_t t)
    : radius_(std::get<0>(t)), mass_(std::get<1>(t)),
      x_(std::get<2>(t)), y_(std::get<3>(t)),
      id_(std::get<4>(t)), is_small_(static_cast<bool>(std::get<5>(t))) {

}
Particle::particle_t Particle::get_tuple() {
  return Particle::particle_t(radius_, mass_, x_, y_, id_, is_small_);
}


