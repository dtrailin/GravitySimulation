//
// Created by Denis on 2018-04-17.
//

#include <algorithm>
#include "Communicator.h"
Communicator::Communicator(Configuration configuration_) : comm(true), configuration_(configuration_) {}

void Communicator::synchronizeWithNeighbors(std::vector<Particle> &input) {
  auto my_pos = comm.get_current_coordinates();

  std::vector<std::pair<xyPair, mxx::future<size_t>>> length_futures;
  std::map<xyPair, std::vector<std::pair<int, int>>>
      neighbors = getNeighbors(my_pos, configuration_.horizon(), comm.x_size(), comm.y_size());

  for (const auto &neighbor : neighbors) {
    const xyPair &abs_pos = neighbor.first;
    length_futures.push_back(std::make_pair(abs_pos,
                                            comm.irecv<size_t>(comm.get_rank(abs_pos.first, abs_pos.second), 1)));
  }

  comm.barrier();

  for (const auto &neighbor : neighbors) {
    const xyPair &abs_pos = neighbor.first;

    comm.send(input.size(),
              comm.get_rank(abs_pos.first, abs_pos.second),
              1);
  }

  std::vector<std::pair<xyPair, mxx::future<std::vector<Particle::particle_t>>>> futures;
  std::vector<Particle::particle_t> tuples;

  for (auto &neighbor_future : length_futures) {
    auto neighbor = neighbor_future.first;
    neighbor_future.second.wait();

    size_t size = neighbor_future.second.get();

    futures.push_back(std::make_pair(neighbor,
                                     comm.irecv_vec<Particle::particle_t>(size, comm.get_rank(neighbor.first,
                                                                                              neighbor.second), 0)));
  }

  comm.barrier();

  std::transform(input.begin(), input.end(), std::back_inserter(tuples),
                 [](Particle c) { return c.get_tuple(); });
  for (const auto &neighbor : neighbors) {
    const xyPair &abs_pos = neighbor.first;

    comm.send(tuples,
              comm.get_rank(abs_pos.first, abs_pos.second),
              0);
  }

  for (auto &future : futures) {
    future.second.wait();
    auto result = future.second.get();
    for (const auto relative_position : neighbors[future.first]) {
      std::transform(result.begin(), result.end(), std::back_inserter(input),
                     [&](Particle::particle_t c) {
                       return mapToFrameOfReference(c,
                                                    relative_position,
                                                    configuration_.gridsize());
                     });
    }

  }

}
std::map<Communicator::xyPair,
         std::vector<Communicator::xyPair>> Communicator::getNeighbors(const Communicator::xyPair &my_pos,
                                                                       int horizon,
                                                                       int x_size,
                                                                       int y_size) {
  std::map<xyPair, std::vector<std::pair<int, int>>> neighbors;

  for (int i = my_pos.first - horizon; i <= my_pos.first + horizon; i++) {
    for (int j = my_pos.second - horizon; j <= my_pos.second + horizon; j++) {

      if (i != my_pos.first || j != my_pos.second) {
        int x = i;
        int y = j;
        if (x < 0) {
          x = x_size + x;
        }
        if (y < 0) {
          y = y_size + y;
        }
        x = x % x_size;
        y = y % y_size;
        neighbors[std::make_pair(x, y)].push_back(std::make_pair(i - my_pos.first, j - my_pos.second));
      }
    }
  }
  return neighbors;
}
Particle Communicator::mapToFrameOfReference(const Particle::particle_t &p,
                                             const Communicator::xyPair &xy,
                                             int gridsize) {
  Particle particle(p);
  particle.set_x(particle.x_pos() - xy.first * gridsize);
  particle.set_y(particle.y_pos() - xy.second * gridsize);
  return particle;

}

