import random


def create_spec(gridsize, particle_count, horizon):
    filename = "spec_" + str(gridsize) + "_" + str(particle_count) + "_" + str(horizon) + ".txt"
    f = open("./" + filename, "w+")
    f.write("TimeSlots: 6  # Number of iterations to compute\n")
    f.write("TimeStep: 0.0001  # Unit time step for each iteration\n")
    f.write("Horizon: " + str(
        horizon) + " # 0 => no process communication, # 1 => adjacent process communication (and so on)\n")
    f.write("GridSize: " + str(gridsize) + "  # for a 100x100 cell grid\n")
    f.write("NumberOfSmallParticles: " + str(particle_count) + " # Number of small (gas) particles\n")
    f.write("SmallParticleMass: 0.0021  # in mass units\n")
    f.write("SmallParticleRadius: 0.00001  # in cell-size units\n")
    f.write("NumberOfLargeParticles: 0  # Number of large (planet) particles following\n")
    return filename


def create_pbs(spec, gridsize, particle_count, horizon, cores, count):
    filename = "submit_" + str(gridsize) + "_" + str(particle_count) + "_" + str(horizon) + "_" + str(cores) + ".pbs"
    f = open("./" + filename, "w+")
    # !/bin/bash
    f.write("module load gcc/4.9.3\n")
    f.write("module load openmpi/gcc493/1.10.2\n")
    f.write("cd $PBS_O_WORKDIR\n")
    f.write("mpirun pool " + spec + " out" + str(count) + ".ppm\n")
    return filename


def create_pbs_single(spec, gridsize, particle_count, horizon, count):
    filename = "submit_" + str(gridsize) + "_" + str(particle_count) + "_" + str(horizon) + "_single" + ".pbs"
    f = open("./" + filename, "w+")
    # !/bin/bash
    f.write("module load gcc/4.9.3\n")
    f.write("cd $PBS_O_WORKDIR\n")
    f.write("./pool_single " + spec + " out" + str(count) + ".ppm\n")
    return filename


count = 0
f = open("./" + "submit.sh", "w+")


def create_submission(f,core, pbs):
    f.write("qsub -l select=1:ncpus=" + str(core) + ":mpiprocs=" + str(core) + ",walltime=10:00:00 -N " + pbs[
                                                                                                          :-4] + " " + pbs + "\n")


total_particles = 50000
total_gridsize  = 200
for core,horizon in [(1, 1), (4,1), (9,1), (16,2)]:
    particle_count = int(total_particles/core)
    gridsize = int(total_gridsize/core)
    spec = create_spec(gridsize,particle_count,horizon)
    pbs = create_pbs(spec, 20, particle_count, horizon, core, count)
    count += 1
    create_submission(f,core,pbs)
    count += 1
    # pbs = create_pbs_single(spec, 20, particle_count, 0, count)
    # f.write("qsub -l select=1:ncpus=1,walltime=08:00:00 -N " + pbs[
    #                                                            :-4] + " " + pbs + "\n")

