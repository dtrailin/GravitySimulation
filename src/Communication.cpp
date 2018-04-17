//
// Created by Denis on 2018-04-17.
//

#include "Communication.h"
Communication::Communication() : comm(true) {}
void Communication::send_to_neighbors() {

  auto my_pos = comm.get_current_coordinates();
  int horizon = 1;



  std::vector<mxx::future<std::basic_string<char, std::char_traits<char>, std::allocator<char>>>> futures;
  std::set<std::pair<int, int>> neighbors = get_neighbors(my_pos, horizon);

  std::stringstream ss;
  ss <<"node: " << my_pos.first << ", " << my_pos.second << " is waiting for ";
  for (const auto &neighbor : neighbors) {
    futures.push_back(comm.irecv_str(100, comm.get_rank(neighbor.first, neighbor.second), 0));
    ss << neighbor.first << "," << neighbor.second <<" ";
  }
  ss << std::endl;

  std::cout << ss.str() ;
  comm.barrier();
  for (const auto &neighbor : neighbors) {
    comm.send("Message from " + std::to_string(my_pos.first) + "," + std::to_string(my_pos.second),
              comm.get_rank(neighbor.first, neighbor.second),
              0);
  }


  for (auto &future : futures) {
    future.wait();
    std::cout<<"node: " << my_pos.first << ", " << my_pos.second << " got: \n" << future.get() << std::endl;
  }

}
std::set<std::pair<int, int>> Communication::get_neighbors(const std::pair<int, int> &my_pos, int horizon) const {
  std::set<std::pair<int, int>> neighbors;

  for (int i = my_pos.first - horizon; i <= my_pos.first + horizon; i++) {
    for (int j = my_pos.second - horizon; j <= my_pos.second + horizon; j++) {

      if (i != my_pos.first || j != my_pos.second) {
        int x = i;
        int y = j;
        if(x < 0){
          x = comm.x_size() + x;
        }
        if(y < 0){
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
