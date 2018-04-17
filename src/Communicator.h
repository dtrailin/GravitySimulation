//
// Created by Denis on 2018-04-17.
//

#ifndef PROJECT2_COMMUNICATION_H
#define PROJECT2_COMMUNICATION_H

#include <mxx/comm.hpp>
#include <mxx/env.hpp>
#include <set>
#include "Particle.h"

class Communicator {
 public:
  Communicator();

  void synchronizeWithNeighbors(const std::vector<Particle> &input);

 private:

  mxx::env e;
  mxx::comm comm;

  std::set<std::pair<int, int>> getNeighbors(const std::pair<int, int> &my_pos, int horizon) const;
};

#endif //PROJECT2_COMMUNICATION_H
