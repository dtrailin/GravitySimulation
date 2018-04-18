//
// Created by Denis on 2018-04-17.
//

#ifndef PROJECT2_COMMUNICATION_H
#define PROJECT2_COMMUNICATION_H

#include <mxx/comm.hpp>
#include <mxx/env.hpp>
#include <set>
#include "Particle.h"
#include "Configuration.h"

class Communicator {
 public:
  Communicator(Configuration configuration_);

  void synchronizeWithNeighbors(std::vector<Particle> &input);

 private:
  typedef std::pair<int, int> xyPair;

  mxx::env e;
  mxx::comm comm;
  Configuration configuration_;

  static std::map<xyPair, std::vector<xyPair>> getNeighbors(const xyPair &my_pos,
                                                             int horizon,
                                                             int x_size,
                                                             int y_size);

  static Particle mapToFrameOfReference(const Particle::particle_t &p, const xyPair &xy, int gridsize);
};

#endif //PROJECT2_COMMUNICATION_H
