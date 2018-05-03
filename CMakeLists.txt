# cmake_minimum_required(VERSION <specify CMake version here>)
project(project2)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")

SET(SRCS
        src/Particle.cpp
        src/Particle.h
        src/Simulation.cpp
        src/Simulation.h
        src/ForceVector.h
        src/Configuration.cpp
        src/Configuration.h
        lib/ppm-io/include/ppm.hpp
        src/ImageWriter.cpp
        src/ImageWriter.h
        )


SET(SRCS_MULTI
        src/Communicator.cpp
        src/Communicator.h
        src/MpiSimulation.cpp src/MpiSimulation.h)

add_subdirectory(lib/mxx)
add_subdirectory(lib/ppm-io)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Output directory for applications" )

add_executable(pool_single src/pool_single.cpp ${SRCS})
add_executable(pool src/pool.cpp ${SRCS} ${SRCS_MULTI})

target_link_libraries(pool_single ppm-io)
target_link_libraries(pool ppm-io)

target_link_libraries(pool mxx)



