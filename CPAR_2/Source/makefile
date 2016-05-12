CC=g++
CFLAGS=-std=c++11

all:
	$(CC) $(CFLAGS) Profiler.cpp sieve_cpp.cpp -fopenmp -o sieve
	$(CC) tester.cpp -o tester
	mpiCC openmpi_sieve.cpp -o sieve_mpi
clean:
	rm *o sieve tester sieve_mpi
test:
	make all
	./tester 1 32 0 8 | ./sieve
