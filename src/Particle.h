//
// Created by Denis on 2018-03-29.
//

#ifndef PROJECT2_PARTICLE_H
#define PROJECT2_PARTICLE_H

#include <ostream>
#include <tuple>

class Particle {
 public:
  typedef std::tuple<double, double, double, double, unsigned long, int> particle_t;

  Particle(double radius,
             double mass,
             double x_pos,
             double y_pos,
             unsigned long id,
             bool is_small);

  explicit Particle(particle_t t);

  particle_t get_tuple();

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

  bool is_small() const {
    return is_small_;
  }
  friend std::ostream &operator<<(std::ostream &os, const Particle &particle);

 private:
  double radius_, mass_, x_, y_;
  unsigned long id_;
  bool is_small_;

};

#endif //PROJECT2_PARTICLE_H
