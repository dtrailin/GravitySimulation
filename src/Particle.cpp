//
// Created by Denis on 2018-03-29.
//

#include "Particle.h"

Particle::Particle(double radius_,
                   double mass_,
                   double x_pos,
                   double y_pos,
                   bool is_small)
    : radius_(radius_), mass_(mass_),
      x_(x_pos), y_(y_pos),
       is_small_(is_small) {}

std::ostream &operator<<(std::ostream &os, const Particle &particle) {
  os << " radius: " << particle.radius_ << " mass: " << particle.mass_ << " x: "
     << particle.x_ << " y: "
     << particle.y_;
  return os;
}



