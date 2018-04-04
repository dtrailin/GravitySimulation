//
// Created by Denis on 2018-03-29.
//

#include "Particle.h"

Particle::Particle(double radius_, double mass_, double x_pos, double y_pos, unsigned long id)
    : radius_(radius_), mass_(mass_),
      x_(x_pos), y_(y_pos),
      id_(id) {}

std::ostream &operator<<(std::ostream &os, const Particle &particle) {
  os << "id_: " << particle.id_ << " radius_: " << particle.radius_ << " mass_: " << particle.mass_ << " x_: "
     << particle.x_ << " y_: "
     << particle.y_;
  return os;
}

