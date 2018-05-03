//
// Created by Denis on 2018-03-29.
//

#ifndef PROJECT2_PARTICLE_H
#define PROJECT2_PARTICLE_H

#include <ostream>
#include <tuple>

struct Particle {
 public:
  typedef std::tuple<double, double, double, double, char> particle_t;

  Particle(double radius,
             double mass,
             double x_pos,
             double y_pos,
             bool is_small);

  explicit Particle(particle_t t)
      : radius_(std::get<0>(t)), mass_(std::get<1>(t)),
        x_(std::get<2>(t)), y_(std::get<3>(t)),
        is_small_(static_cast<bool>(std::get<4>(t))) {

  }

  particle_t get_tuple() {
    return Particle::particle_t(radius_, mass_, x_, y_, is_small_);
  }


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

 public:
  double radius_, mass_, x_, y_;
  bool is_small_;

};

#endif //PROJECT2_PARTICLE_H
