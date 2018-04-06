# cmake_minimum_required(VERSION <specify CMake version here>)
project(project2)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")

find_package( MPI REQUIRED )
SET(CMAKE_CXX_COMPILER mpicxx )
SET(CMAKE_C_COMPILER mpicc )
SET(SRCS
        src/Particle.cpp
        src/Particle.h
        src/Simulation.cpp
        src/Simulation.h
        src/ForceVector.h
        src/Configuration.cpp
        src/Configuration.h
        src/ppm-io/ppm.hpp src/ImageWriter.cpp src/ImageWriter.h)

add_executable(project2 main.cpp ${SRCS})

