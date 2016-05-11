CC=g++
CFLAGS=-std=c++11

all:
	$(CC) $(CFLAGS) Profiler.cpp sieve_cpp.cpp  -o program
	mpiCC openmpi_sieve.cpp -o program_openmpi
clean:
	rm *o program
