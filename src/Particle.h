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

static Particle create_particle(double radius_,
                                double mass_,
                                double x_pos,
                                double y_pos,
                                bool is_small);
#endif //PROJECT2_PARTICLE_H
