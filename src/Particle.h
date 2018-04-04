//
// Created by Denis on 2018-03-29.
//

#ifndef PROJECT2_PARTICLE_H
#define PROJECT2_PARTICLE_H

#include <ostream>

class Particle {
 public:
  Particle(double radius, double mass, double x_pos, double y_pos, unsigned long id);

  double radius() const {
    return radius_;
  }

  double mass() const {
    return mass_;
  }

  double y_pos() const {
    return y_;
  }
  double x_pos() const {
    return x_;
  }

  unsigned long id() const {
    return id_;
  }

  void set_x(double x) {
    x_ = x;
  }

  void set_y(double y) {
    y_ = y;
  }

  friend std::ostream &operator<<(std::ostream &os, const Particle &particle);

 private:
  double radius_, mass_, x_, y_;
  unsigned long id_;
};

#endif //PROJECT2_PARTICLE_H
