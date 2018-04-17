//
// Created by Denis on 2018-04-17.
//

#ifndef PROJECT2_COMMUNICATION_H
#define PROJECT2_COMMUNICATION_H

#include <mxx/comm.hpp>
#include <mxx/env.hpp>
#include <set>
#include "Particle.h"

class Communication {
 public:
  Communication();

  void send_to_neighbors(const std::vector<Particle> &vector);

 private:

  mxx::env e;
  mxx::comm comm;

  std::set<std::pair<int, int>> get_neighbors(const std::pair<int, int> &my_pos, int horizon) const;
};

#endif //PROJECT2_COMMUNICATION_H
