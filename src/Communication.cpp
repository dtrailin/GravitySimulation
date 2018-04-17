//
// Created by Denis on 2018-04-17.
//

#include <algorithm>
#include "Communication.h"
Communication::Communication() : comm(true) {}
void Communication::send_to_neighbors(const std::vector<Particle> &vector) {
  auto my_pos = comm.get_current_coordinates();
  int horizon = 1;

  std::vector<std::pair<std::pair<int, int>, mxx::future<size_t>>> length_futures;
  std::set<std::pair<int, int>> neighbors = get_neighbors(my_pos, horizon);

  for (const auto &neighbor : neighbors) {
    length_futures.push_back(std::make_pair(neighbor, comm.irecv<size_t>(comm.get_rank(neighbor.first, neighbor.second), 1)));
  }

  comm.barrier();

  for (const auto &neighbor : neighbors) {
    comm.send(vector.size(),
              comm.get_rank(neighbor.first, neighbor.second),
              1);
  }

  std::vector<mxx::future<std::vector<Particle::particle_t, std::allocator<Particle::particle_t>>>> futures;
  std::vector<Particle::particle_t> tuples;

  for (auto &neighbor_future : length_futures) {
    auto neighbor = neighbor_future.first;
    neighbor_future.second.wait();

    size_t size = neighbor_future.second.get();

    futures.push_back(comm.irecv_vec<Particle::particle_t>(size,
                                                           comm.get_rank(neighbor.first, neighbor.second),
                                                           0));
  }

  comm.barrier();

  std::transform(vector.begin(), vector.end(), std::back_inserter(tuples),
                 [](Particle c) { return c.get_tuple(); });
  for (const auto &neighbor : neighbors) {
    comm.send(tuples,
              comm.get_rank(neighbor.first, neighbor.second),
              0);
  }

  for (auto &future : futures) {
    future.wait();
    std::stringstream ss;
    std::vector<Particle> particles;
    auto result = future.get();
    std::transform(result.begin(), result.end(), std::back_inserter(particles),
                   [](Particle::particle_t c) { return Particle(c); });


  }

}
std::set<std::pair<int, int>> Communication::get_neighbors(const std::pair<int, int> &my_pos, int horizon) const {
  std::set<std::pair<int, int>> neighbors;

  for (int i = my_pos.first - horizon; i <= my_pos.first + horizon; i++) {
    for (int j = my_pos.second - horizon; j <= my_pos.second + horizon; j++) {

      if (i != my_pos.first || j != my_pos.second) {
        int x = i;
        int y = j;
        if (x < 0) {
          x = comm.x_size() + x;
        }
        if (y < 0) {
          y = comm.y_size() + y;
        }
        x = x % comm.x_size();
        y = y % comm.y_size();
        neighbors.insert(std::make_pair(x, y));
      }
    }
  }
  return neighbors;
}
