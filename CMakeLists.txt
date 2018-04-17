# cmake_minimum_required(VERSION <specify CMake version here>)
project(project2)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")

SET(SRCS
        src/Particle.cpp
        src/Particle.h
        src/Simulation.cpp
        src/Simulation.h
        src/ForceVector.h
        src/Configuration.cpp
        src/Configuration.h
        src/ppm-io/ppm.hpp
        src/ImageWriter.cpp
        src/ImageWriter.h
        #src/Communicator.cpp
        #src/Communicator.h
        )

add_subdirectory(lib/mxx)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Output directory for applications" )

add_executable(pool_single pool_single.cpp ${SRCS})
add_executable(pool pool.cpp ${SRCS})

target_link_libraries(pool mxx)


